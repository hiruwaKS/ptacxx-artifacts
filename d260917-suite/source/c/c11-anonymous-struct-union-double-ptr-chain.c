// <original>

int gbase;

struct Cell {
	int tag;
	union {
		int *p;
		int **pp;
	};
};

int *gptr = &gbase;
struct Cell gcell = { 1, { &gbase } };
struct Cell gcell2 = { 2, { &gbase } };
struct Cell *gcells[2] = { &gcell, &gcell2 };

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

int chase(struct Cell **cells, int n, int **pp, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *cells[i]->p;
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
	int **chain;
	int total;
	struct Cell local;
	struct Cell other;
	struct Cell *cp;
	struct Cell *cq;
	struct Cell **cpp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	cp = &local;
	cq = &other;
	cpp = &cp;
	local.tag = 1;
	local.p = &x;
	other.tag = 2;
	other.pp = &p;

	*pp = &y;
	*q = 6;
	**qq = **qq + 1;
	*cp->p = 12;
	(*cpp)->tag = (*cpp)->tag + *(*cpp)->p;
	cq->tag = cq->tag + **cq->pp;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	chain = &p;
	**chain = **chain + 1;

	total = chase(gcells, 2, pp, qq);
	total = total + **via + *cp->p + gcell.tag;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	return 0;
}
