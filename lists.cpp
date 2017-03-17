#include <iostream>
#include <unordered_set> //c++11
using namespace std;

/* =========================Helper declarations and functions ====================================*/
struct Node {
    int data;
    Node* next;
};

Node* newNode (int data) {
    Node* n = new Node;
    n->data = data;
    n->next = NULL;
    return n;
}

Node* buildRandomList (int num) {
    srand(1216);
    Node* last = NULL;
    for (int i = 0; i < num; i++) {
        Node* n = newNode( rand() % (num + 100) );
        n->next = last;
        last = n;
    }
    return last;
}

Node* buildList (int num) {
    Node* last = NULL;
    for (int i = 0; i < num; i++) {
        Node* n = newNode( i );
        n->next = last;
        last = n;
    }
    return last;
}

void deleteList (Node* head) {
    Node* n = head;
    while (n) {
        Node* tmp = n->next;
        delete n;
        n = tmp;
    }
}

void printList (Node* head) {
    Node* n = head;
    while (n) {
        cout << n->data << " ";
        n = n->next;
    }
    cout << endl;
}

int size (Node* head) {
    Node* n = head;
    int res = 0;
    while (n) {
        n = n->next;
        res++;
    }
    return res;
}

Node* copyList (Node* head) {
    Node* iter  = head;
    Node* prev  = NULL;
    Node* start = NULL;

    while (iter) {
        Node* n = newNode(iter->data);
        if (!start)  start      = n;
        if (prev)    prev->next = n;
        prev = n;
        iter = iter->next;
    }
    return start;
}

/* =============================Split List in Two Halves==========================================*/
Node* split (Node* head) {
    // Last half elements go to l2, head contains at the end first half elements
    Node* a = head;
    Node* b = head;
    Node* prev = NULL;
    while (b) {
        prev = a;
        b = b->next;
        a = a->next;
        if (b) b = b->next;
    }
    if (prev) prev->next = NULL;
    return a;
}

void splitRecursive (Node* head, Node*& l1, Node*& l2) {
    // Elements in pair positions go to l1, rest to l2
    if (head == NULL) { l1 = l2 = NULL; return; }
    if (!head->next)  { l1 = head; l2 = NULL; return; }

    l1 = head;
    l2 = head->next;

    Node* tmp1 = NULL; Node* tmp2 = NULL;
    splitRecursive(head->next->next, tmp1, tmp2);
    l1->next = tmp1;
    l2->next = tmp2;
}

/* =========================Merge Two Sorted Lists================================================*/
Node* mergeSortedListsRecursive (Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->data > l2->data) {
        Node* res = mergeSortedListsRecursive(l1, l2->next);
        l2->next = res;
        return l2;
    } else {
        Node* res = mergeSortedListsRecursive(l1->next, l2);
        l1->next = res;
        return l1;
    }
}

Node* mergeSortedLists (Node* l1, Node* l2) {
    Node* head = NULL;
    Node* last = NULL;
    Node* ptr1 = l1;
    Node* ptr2 = l2;

    while (ptr1 && ptr2) {
        if (ptr1->data < ptr2->data) {
            if (last)  last->next = ptr1;
            if (!head) head = ptr1;
            last = ptr1;
            ptr1 = ptr1->next;
        } else {
            if (last)  last->next = ptr2;
            if (!head) head = ptr2;
            last = ptr2;
            ptr2 = ptr2->next;
        }
    }

    //Check remaining
    if (ptr1) {
        if (last)  last->next = ptr1;
        if (!head) head       = ptr1;
    } else if (ptr2) {
        if (last)  last->next = ptr2;
        if (!head) head       = ptr2;
    }

    return head;
}

/* ===================================Reverse a list==============================================*/
Node* reverse (Node* head) {
    Node* curr = head;
    Node* prev = NULL;
    while (curr) {
        Node* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    return prev;
}

/* =======================================Merge Sort==============================================*/
Node* mergeSort (Node* head) {

    // COST: O(N*logN) [split requires O(N) time]

    if (!head || !head->next) return head; // base case is no element or 1 element, already sorted

    Node* list2      = split(head);
    Node* list1      = head;
    Node* sorted_l1  = mergeSort(head);
    Node* sorted_l2  = mergeSort(list2);
    return mergeSortedLists(sorted_l1, sorted_l2);
}

/* ==========================Remove duplicates from unsorted list================================ */
// http://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/
void removeDuplicates (Node* head) {
    // Time: O(N^2)
    Node* ptr1  = head;

    while (ptr1) {
        Node* ptr2  = ptr1->next;
        Node* prev  = ptr1;
        while (ptr2) {
            if (ptr2->data == ptr1->data) {
                Node* tmp = ptr2->next;
                prev->next = tmp;
                delete ptr2;
                ptr2 = tmp;
            } else {
                prev = ptr2;
                ptr2 = ptr2->next;
            }
        }
        ptr1 = ptr1->next;
    }
}

void removeDuplicatesWithHash (Node* head) {
    // Time: O(N), space O(N)
    // Unordered_set works as a hash table. Introduced in C++11. Also unordered_map.
    // http://en.cppreference.com/w/cpp/container/unordered_set
    unordered_set<int> hashTable;

    Node* ptr  = head;
    Node* prev = NULL;
    while (ptr) {
        if (hashTable.find(ptr->data) != hashTable.end()) {
            // Value found
            Node* tmp = ptr->next;
            prev->next = tmp; // No need to check prev is not NULL, because duplicate is at pos >=2
            delete ptr;
            ptr        = tmp;
        } else { //Not found
            hashTable.insert(ptr->data);
            prev = ptr;
            ptr  = ptr->next;
        }
    }
}

/* ===========================EXAMPLE FUNCTIONS TO DEMO FUNCTIONS ABOVE===========================*/
void split_example() {
    Node* head = buildList(20);
    Node* res = split(head);
    cout << "Split lists are: " << endl;
    cout << "\t"; printList(head);
    cout << "\t"; printList(res);
    deleteList(head);
    deleteList(res);
}
void splitRecursive_example() {
    Node* head = buildList(20);
    Node* l1; Node* l2;
    splitRecursive(head, l1, l2);
    cout << "Split lists are (recursive method): " << endl;
    cout << "\t"; printList(l1);
    cout << "\t"; printList(l2);
    deleteList(l1);
    deleteList(l2);
}
void mergeSortedLists_example() {
    Node* head = buildList(20);
    Node* l1; Node* l2;
    splitRecursive(head, l1, l2);
    l1 = reverse(l1);
    l2 = reverse(l2);

    Node* res = mergeSortedLists(l1, l2);
    cout << "Merged sorted lists results in: " << endl;
    cout << "\t"; printList(res);
    deleteList(res);
}

void mergeSortedListsRecursive_example() {
    Node* head = buildList(20);
    Node* l1; Node* l2;
    splitRecursive(head, l1, l2);
    l1 = reverse(l1);
    l2 = reverse(l2);

    Node* res = mergeSortedListsRecursive(l1, l2);
    cout << "Merged sorted lists results in (recursive method): " << endl;
    cout << "\t"; printList(res);
    deleteList(res);
}

void reverse_example() {
    Node* head = buildList(20);
          head = reverse(head);
    cout << "Reversed list is: " << endl;
    cout << "\t"; printList(head);
    deleteList(head);
}

void mergeSort_example() {
    Node* head = buildRandomList(20);
    cout << "Merge-Sorted list is: " << endl;
    head = mergeSort(head);
    cout << "\t"; printList(head);
    deleteList(head);
}

void removeDuplicates_example() {
    Node* head = buildRandomList(30);
    cout << "Removed duplicates: " << endl;
    cout << "\tBefore unsorted: "; printList(head);
    Node* copy = copyList(head);
          copy = mergeSort(copy);
    cout << "\tBefore sorted  : "; printList(copy);

    removeDuplicates(head);
    cout << "\tAfter unsorted : "; printList(head);
    Node* copy2 = copyList(head);
          copy2 = mergeSort(copy2);
    cout << "\tAfter sorted   : "; printList(copy2);
    deleteList(head);
    deleteList(copy);
    deleteList(copy2);
}

void removeDuplicatesWithHash_example() {
    Node* head = buildRandomList(30);
    cout << "Removed duplicates with Hash Table: " << endl;
    cout << "\tBefore unsorted: "; printList(head);
    Node* copy = copyList(head);
          copy = mergeSort(copy);
    cout << "\tBefore sorted  : "; printList(copy);

    removeDuplicatesWithHash(head);
    cout << "\tAfter unsorted : "; printList(head);
    Node* copy2 = copyList(head);
          copy2 = mergeSort(copy2);
    cout << "\tAfter sorted   : "; printList(copy2);
    deleteList(head);
    deleteList(copy);
    deleteList(copy2);
}


/* ===============================================================================================*/
int main () {
    split_example();
    splitRecursive_example();
    mergeSortedLists_example();
    mergeSortedListsRecursive_example();
    reverse_example();
    mergeSort_example();
    removeDuplicates_example();
    removeDuplicatesWithHash_example();
}

/* =======================================TODO====================================================*/