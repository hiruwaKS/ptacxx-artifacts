// <original>

#include <stdarg.h>

struct Node {
	int value;
	struct Node *next;
};

struct Node gpool[2];

struct Node *chain(struct Node **head, int v) {
	struct Node *n;
	n = *head;
	if (n == 0) {
		n = &gpool[0];
	} else if (n->value < 0) {
		n = n->next;
	}
	n->value = v;
	*head = n;
	return n;
}

int walk_nodes(int n, ...) {
	va_list ap;
	int i;
	struct Node *node;
	struct Node **slot;
	int s;
	s = 0;
	va_start(ap, n);
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			node = va_arg(ap, struct Node *);
			if (node != 0 && node->next != 0) {
				s = s + node->value;
			}
		} else {
			slot = va_arg(ap, struct Node **);
			if (slot != 0 && *slot != 0) {
				s = s + (*slot)->value;
			}
		}
	}
	va_end(ap);
	return s;
}

int main(void) {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int total;
	struct Node a;
	struct Node b;
	struct Node *head;
	struct Node *tail;
	struct Node **hp;
	struct Node **tp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	a.value = 5;
	a.next = &b;
	b.value = 6;
	b.next = 0;

	head = &a;
	tail = &b;
	hp = &head;
	tp = &tail;

	chain(hp, 9);
	total = walk_nodes(4, head, hp, &b, tp);

	**pp = **pp + a.value;
	*pp = &y;
	*q = *p + b.value;
	total = total + **pp + **qq + head->value;

	if (total > 0 && head != 0) {
		total = total - head->next->value;
	} else {
		total = total + x;
	}

	return 0;
}
