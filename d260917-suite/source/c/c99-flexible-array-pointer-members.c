// <original>

#include <stdlib.h>

struct Item {
	int val;
	int *ref;
};

struct Bag {
	int n;
	struct Item *head;
	struct Item items[];
};

struct Bag *make_bag(int n, struct Item *head) {
	struct Bag *b;
	b = (struct Bag *)malloc(sizeof(struct Bag) + n * sizeof(struct Item));
	b->n = n;
	b->head = head;
	return b;
}

void init_items(struct Bag *b, int *base) {
	int i;
	for (i = 0; i < b->n; i = i + 1) {
		b->items[i].val = i;
		b->items[i].ref = base;
	}
}

int total(struct Bag *b, int **pp) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < b->n; i = i + 1) {
		if (b->items[i].ref != 0) {
			s = s + *b->items[i].ref;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int **pick(struct Bag **bp, int **a, int **c, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = c;
	} else {
		r = pick(bp, c, a, depth - 1);
	}
	return r;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int **via;
	struct Item seed;
	struct Item *sp;
	struct Bag *b;
	struct Bag *c;
	struct Bag **bp;
	int sum;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	seed.val = 9;
	seed.ref = p;
	sp = &seed;

	b = make_bag(4, sp);
	c = make_bag(2, sp);
	init_items(b, q);
	init_items(c, p);

	bp = &b;
	(*bp)->items[0].ref = p;
	(*bp)->items[1].val = **pp;
	b->head->val = **qq;
	*seed.ref = *seed.ref + 1;

	via = pick(bp, pp, qq, 2);
	**via = **via + 5;

	sum = total(b, pp) + total(c, qq);
	sum = sum + **via + *b->items[0].ref;

	if (sum > 0) {
		if (sum % 2 == 0) {
			sum = sum - x;
		} else {
			sum = sum + y;
		}
	} else {
		sum = 0;
	}

	free(b);
	free(c);
	return 0;
}
