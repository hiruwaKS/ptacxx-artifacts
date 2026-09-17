// <original>

#include <stdlib.h>

struct Entry {
	int **slot;
	int tag;
};

int *resolve(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = resolve(a, b, depth - 1);
	}
	return r;
}

int **resolve2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = resolve2(b, a, depth - 1);
	}
	return r;
}

int scan(struct Entry *tab, int n, int **pp, int **qq) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		switch (tab[i].tag) {
		case 0:
			s = s + **tab[i].slot;
			break;
		case 1:
			s = s + **pp;
			break;
		default:
			s = s + **qq;
			break;
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
	struct Entry *tab;

	tab = aligned_alloc(16, 64);
	if (tab == 0) {
		return 1;
	}

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	tab[0].slot = &p;
	tab[0].tag = 0;
	tab[1].slot = &q;
	tab[1].tag = 1;
	tab[2].slot = &p;
	tab[2].tag = 2;
	tab[3].slot = &q;
	tab[3].tag = 0;

	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;
	**tab[0].slot = **tab[0].slot + 3;

	r = resolve(p, q, 3);
	*r = *r + 1;

	via = resolve2(pp, qq, 2);
	**via = **via + 4;

	total = scan(tab, 4, pp, qq);
	total = total + **tab[1].slot + *r;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(tab);

	return 0;
}
