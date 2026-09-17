// <original>

#include <stdlib.h>

struct Inner {
	int *p;
	int n;
};

struct Outer {
	struct Inner *rows;
	int **table;
	int count;
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

int walk(struct Outer *o, int **pp, int **qq) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < o->count; i = i + 1) {
		if (i == 0) {
			s = s + *o->rows[i].p;
		} else if (i == 1) {
			s = s + **o->table;
		} else if (i == 2) {
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
	struct Outer *o;
	struct Inner *in;
	int **tab;

	o = aligned_alloc(16, 64);
	in = aligned_alloc(16, 64);
	tab = aligned_alloc(16, 64);
	if (o == 0 || in == 0 || tab == 0) {
		free(o);
		free(in);
		free(tab);
		return 1;
	}

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	o->rows = in;
	o->table = tab;
	o->count = 4;

	in[0].p = &x;
	in[0].n = 3;
	in[1].p = &y;
	in[1].n = 4;
	in[2].p = &x;
	in[2].n = 5;
	in[3].p = &y;
	in[3].n = 6;

	tab[0] = &x;
	tab[1] = &y;

	*o->rows[0].p = 10;
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;
	**o->table = **o->table + 3;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 4;

	total = walk(o, pp, qq);
	total = total + *o->rows[1].p + **via;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(o);
	free(in);
	free(tab);

	return 0;
}
