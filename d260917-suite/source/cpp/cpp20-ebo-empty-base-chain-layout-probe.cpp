// <original>

struct E1 {};
struct E2 : E1 {};
struct E3 : E2 {};

struct Derived : E3 {
	int v;
	int *p;
	int **pp;
};

int empty_probe(E1 *a, E2 *b, E3 *c, int **pp) {
	int r;
	r = 0;
	if (a != 0) {
		r = r + 1;
	}
	if (b != 0) {
		r = r + 2;
	}
	if (c != 0) {
		r = r + 3;
	}
	if (pp != 0) {
		r = r + **pp;
	}
	return r;
}

int derived_probe(Derived *d, int ***qq) {
	int r;
	r = d->v;
	if (d->p != 0) {
		r = r + *d->p;
	}
	if (d->pp != 0) {
		r = r + **d->pp;
	}
	if (qq != 0 && *qq != 0) {
		r = r + ***qq;
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
	int ***qqq;
	int total;
	Derived d;
	E1 *a;
	E2 *b;
	E3 *c;
	Derived *dp;

	x = 2;
	y = 9;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	qqq = &qq;

	d.v = 4;
	d.p = &x;
	d.pp = &q;

	a = &d;
	b = &d;
	c = &d;
	dp = &d;

	*pp = &d.v;
	*q = *dp->p + 1;
	**qq = **qq + 2;
	***qqq = ***qqq + 3;
	*dp->p = d.v;

	total = empty_probe(a, b, c, pp);
	total = total + derived_probe(dp, qqq);

	if (total > 10) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
