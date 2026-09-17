// <original>

#include <stdlib.h>

struct Node {
	struct Node *next;
	int *val;
	int id;
};

int *find(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = find(a, b, depth - 1);
	}
	return r;
}

int **find2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = find2(b, a, depth - 1);
	}
	return r;
}

int walk(struct Node *head, int **pp, int **qq) {
	int s;
	int k;
	struct Node *cur;
	s = 0;
	k = 0;
	cur = head;
	while (cur != 0) {
		if (k == 0) {
			s = s + *cur->val;
		} else if (k == 1) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
		k = k + 1;
		cur = cur->next;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	struct Node *nodes;
	struct Node *head;
	struct Node **link;

	nodes = aligned_alloc(16, 128);
	if (nodes == 0) {
		return 1;
	}

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	nodes[0].next = &nodes[1];
	nodes[0].val = &x;
	nodes[0].id = 0;
	nodes[1].next = &nodes[2];
	nodes[1].val = &y;
	nodes[1].id = 1;
	nodes[2].next = &nodes[3];
	nodes[2].val = &x;
	nodes[2].id = 2;
	nodes[3].next = 0;
	nodes[3].val = &y;
	nodes[3].id = 3;

	head = &nodes[0];
	link = &head;
	*link = &nodes[0];

	*nodes[0].val = 10;
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;
	*link = &nodes[1];
	(*link)->id = (*link)->id + 1;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 4;

	total = walk(head, pp, qq);
	total = total + *nodes[1].val + **via;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(nodes);

	return 0;
}
