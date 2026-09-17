// <original>

#include <stdlib.h>

struct Node {
	int *p;
	int v;
};

int *pick(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = pick(a, b, depth - 1);
	}
	return r;
}

int **pick2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = pick2(b, a, depth - 1);
	}
	return r;
}

int sum_nodes(struct Node *nodes, int n, int **pp, int **qq) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *nodes[i].p;
		} else if (i == 1) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
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

	nodes = aligned_alloc(16, 64);
	if (nodes == 0) {
		return 1;
	}

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	nodes[0].p = &x;
	nodes[0].v = 3;
	nodes[1].p = &y;
	nodes[1].v = 4;
	nodes[2].p = &x;
	nodes[2].v = 5;
	nodes[3].p = &y;
	nodes[3].v = 6;

	*nodes[0].p = 10;
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;

	r = pick(p, q, 3);
	*r = *r + 1;

	via = pick2(pp, qq, 2);
	**via = **via + 3;

	total = sum_nodes(nodes, 4, pp, qq);
	total = total + *nodes[1].p + **via;

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
