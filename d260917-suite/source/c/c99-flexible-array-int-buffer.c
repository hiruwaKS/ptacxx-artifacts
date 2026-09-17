// <original>

#include <stdlib.h>

struct Buffer {
	int len;
	int *owner;
	int data[];
};

int *gptr;

struct Buffer *make_buffer(int n, int *owner) {
	struct Buffer *b;
	b = (struct Buffer *)malloc(sizeof(struct Buffer) + n * sizeof(int));
	b->len = n;
	b->owner = owner;
	return b;
}

void fill(struct Buffer *b, int base) {
	int i;
	for (i = 0; i < b->len; i = i + 1) {
		b->data[i] = base + i;
	}
}

int sum(struct Buffer *b) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < b->len; i = i + 1) {
		s = s + b->data[i];
	}
	return s;
}

int sum_via(struct Buffer **pp, int **qq, int n) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*pp)->data[0];
		} else if (i == 1) {
			s = s + **qq;
		} else {
			s = s + (*pp)->data[i % (*pp)->len];
		}
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
	int **via;
	struct Buffer *b;
	struct Buffer *c;
	struct Buffer **bp;
	int total;

	x = 5;
	y = 6;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	gptr = &x;

	b = make_buffer(4, p);
	c = make_buffer(3, q);
	fill(b, 10);
	fill(c, 20);

	bp = &b;
	(*bp)->data[1] = *p;
	(*bp)->owner = q;
	**pp = **pp + 1;
	**qq = **qq + 2;
	*b->owner = *b->owner + 3;

	via = &p;
	*via = q;
	**via = **via + 1;

	total = sum(b) + sum(c) + sum_via(bp, qq, 3);
	total = total + *(*bp)->owner + *gptr + **via;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(b);
	free(c);
	return 0;
}
