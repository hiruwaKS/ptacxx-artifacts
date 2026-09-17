// <original>

#include <stdlib.h>

struct Node {
	int *value;
	Node *link;
};

struct List {
	Node *head;
	Node **tail;
	int count;

	List() {
		head = 0;
		tail = &head;
		count = 0;
	}

	List(const List &o) {
		Node *cur;
		Node *node;
		head = 0;
		tail = &head;
		count = 0;
		cur = o.head;
		while (cur != 0) {
			node = (Node *)malloc(sizeof(Node));
			node->value = (int *)malloc(sizeof(int));
			*node->value = *cur->value;
			node->link = 0;
			*tail = node;
			tail = &node->link;
			count = count + 1;
			cur = cur->link;
		}
	}

	~List() {
		Node *cur;
		Node *next;
		cur = head;
		while (cur != 0) {
			next = cur->link;
			free(cur->value);
			free(cur);
			cur = next;
		}
	}

	void append(int v) {
		Node *node;
		node = (Node *)malloc(sizeof(Node));
		node->value = (int *)malloc(sizeof(int));
		*node->value = v;
		node->link = 0;
		*tail = node;
		tail = &node->link;
		count = count + 1;
	}
};

int sumList(List *l) {
	Node *cur;
	int s = 0;
	cur = l->head;
	while (cur != 0) {
		s = s + *cur->value;
		cur = cur->link;
	}
	return s;
}

int mutate(List *l, int **pp) {
	Node *cur;
	int s = 0;
	cur = l->head;
	while (cur != 0) {
		if (**pp > 0) {
			*cur->value = *cur->value + **pp;
		} else {
			*cur->value = *cur->value - 1;
		}
		s = s + *cur->value;
		cur = cur->link;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	List original;
	List empty(original);
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;

	original.append(10);
	original.append(20);
	original.append(30);

	List snapshot(original);

	total = sumList(&snapshot);
	total = total + mutate(&original, pp);
	total = total + **qq + *original.head->value;

	if (total > 0 && **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
