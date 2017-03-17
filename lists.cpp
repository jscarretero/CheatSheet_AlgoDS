#include <iostream>
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

/* ===============================================================================================*/
int main () {
	split_example();
	splitRecursive_example();
	mergeSortedLists_example();
	mergeSortedListsRecursive_example();
	reverse_example();
}

/* =======================================TODO====================================================*/