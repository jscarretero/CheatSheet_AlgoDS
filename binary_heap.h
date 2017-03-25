
void swap(int *x, int *y) { int temp = *x; *x = *y; *y = temp; }

/* ==================================MIN HEAP=====================================================*/

class MinHeap  {
    int *harr;     // pointer to array of elements in heap
    int capacity;  // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    MinHeap(int capacity);
    MinHeap(int a[], int size);

    void MinHeapify(int i); // to heapify a subtree with root at given index

    int parent(int i) { return (i-1)/2;   }
    int left(int i)   { return (2*i + 1); }
    int right(int i)  { return (2*i + 2); }

    int extractMin();
    int getMin()      { return harr[0];   }

    void replaceMin(int x) { harr[0] = x;  MinHeapify(0); }
    void decreaseKey(int i, int new_val);
    void deleteKey(int i);
    void insertKey(int k);
};

MinHeap::MinHeap(int cap) {
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];  //we should need a destructor method for this case, but whatever for now..
}
MinHeap::MinHeap(int a[], int size) {  // O(N) time!! IMPORTANT
    heap_size = size;
    capacity = size;
    harr = a;
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}
void MinHeap::insertKey(int k) {
    if (heap_size == capacity) { return; }

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;

    while (i != 0 && harr[parent(i)] > harr[i]) {  // Fix the min heap property if it is violated
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
void MinHeap::decreaseKey(int i, int new_val) {
    // It is assumed that new_val is smaller than harr[i].
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}
int MinHeap::extractMin() {
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }

    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}
void MinHeap::deleteKey(int i) {
// It first reduced value to minimum, then calls extractMin()
    decreaseKey(i, INT_MIN);
    extractMin();
}
void MinHeap::MinHeapify(int i) {
    // This method assumes that the subtrees are already heapified
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

/* ==================================MAX HEAP=====================================================*/

class MaxHeap {
    int *harr;     // pointer to array of elements in heap
    int capacity;  // maximum possible size of max heap
    int heap_size; // current number of elements in max heap
public:
    MaxHeap(int a[], int size);
    void maxHeapify(int i);                  //to maxHeapify subtree rooted with index i
    int parent(int i) { return (i-1)/2;  }
    int left(int i)   { return (2*i + 1); }
    int right(int i)  { return (2*i + 2); }

    int extractMax();
    int getMax() { return harr[0]; }

    void replaceMax(int x) { harr[0] = x;  maxHeapify(0); }
};
MaxHeap::MaxHeap(int a[], int size) {
    heap_size = size;
    harr = a;
    int i = (heap_size - 1)/2;
    while (i >= 0) {
        maxHeapify(i);
        i--;
    }
}
int MaxHeap::extractMax() {
    if (heap_size == 0)  return INT_MAX;

    int root = harr[0];
    if (heap_size > 1) { // If there are more than 1 items, move the last item to root and call heapify
        harr[0] = harr[heap_size-1];
        maxHeapify(0);
    }
    heap_size--;

    return root;
}
void MaxHeap::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l < heap_size && harr[l] > harr[i])
        largest = l;
    if (r < heap_size && harr[r] > harr[largest])
        largest = r;
    if (largest != i)
    {
        swap(&harr[i], &harr[largest]);
        maxHeapify(largest);
    }
}

