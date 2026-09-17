// <original>

int gtag;

struct A {
	int *ap;
	int **app;

	A(int *p, int **pp) {
		ap = p;
		app = pp;
	}

	virtual ~A() {}

	int a() {
		return *ap + **app;
	}
};

struct B {
	int *bp;
	int **bpp;

	B(int *p, int **pp) {
		bp = p;
		bpp = pp;
	}

	virtual ~B() {}

	int b() {
		return *bp + **bpp;
	}
};

struct C : A, B {
	int *cp;
	int **cpp;

	C(int *p, int **pp, int *q, int **qq, int *r, int **rr)
		: A(p, pp), B(q, qq) {
		cp = r;
		cpp = rr;
	}

	int c() {
		return *cp + **cpp;
	}
};

int mix(A **aa, B **bb, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*aa)->a();
		} else if (i == 1) {
			s = s + (*bb)->b();
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **rr;
	A *a;
	B *b;
	C *c;
	A **aa;
	B **bb;
	C **cc;
	int total;

	x = 1;
	y = 2;
	z = 3;
	p = &x;
	q = &y;
	r = &z;
	pp = &p;
	qq = &q;
	rr = &r;

	c = new C(p, pp, q, qq, r, rr);
	a = static_cast<A *>(c);
	b = static_cast<B *>(c);
	aa = &a;
	bb = &b;
	cc = &c;

	total = mix(aa, bb, rr, 3);

	B *badj = static_cast<B *>(c);
	total = total + *badj->bp;
	**badj->bpp = **badj->bpp + 1;

	A *aadj = static_cast<A *>(*cc);
	total = total + aadj->a();

	C *cback = static_cast<C *>(b);
	*cback->cp = *cback->cp + 4;
	total = total + **cback->cpp;

	if (total > 0) {
		total = total + *p + *q + *r;
	} else {
		total = 0;
	}

	gtag = total;

	delete c;

	return 0;
}
