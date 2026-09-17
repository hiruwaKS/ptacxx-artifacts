// <original>

#include <typeinfo>

int gdepth;

struct Base {
	int *v;
	int **ref;

	Base(int *a, int **b) {
		v = a;
		ref = b;
	}

	virtual ~Base() {}

	virtual int get() {
		return *v;
	}
};

struct Left : virtual Base {
	int *l;

	Left(int *a, int **b, int *c) : Base(a, b) {
		l = c;
	}

	virtual int get() {
		return *l + *v;
	}
};

struct Right : virtual Base {
	int *r;

	Right(int *a, int **b, int *c) : Base(a, b) {
		r = c;
	}

	virtual int get() {
		return *r + *v;
	}
};

struct Both : Left, Right {
	int *extra;

	Both(int *a, int **b, int *c, int *d, int *e)
		: Base(a, b), Left(a, b, c), Right(a, b, d) {
		extra = e;
	}

	virtual int get() {
		return *extra + *l + *r;
	}
};

int probe(Base &b, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		try {
			Left &lr = dynamic_cast<Left &>(b);
			s = s + lr.get();
		} catch (const std::bad_cast &e) {
			if (i == 0) {
				s = s + **pp;
			} else {
				s = s + **qq;
			}
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int d;
	int e;
	int *p;
	int *q;
	int *r;
	int *s;
	int *t;
	int **pp;
	int **qq;
	Both *bp;
	Both **bpp;
	Right *rp;
	Base *base;
	int total;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	p = &a;
	q = &b;
	r = &c;
	s = &d;
	t = &e;
	pp = &p;
	qq = &q;

	bp = new Both(p, pp, r, s, t);
	bpp = &bp;
	rp = new Right(p, pp, q);
	base = bp;

	**pp = **pp + 1;
	*bp->extra = *bp->extra + 2;
	*base->v = *base->v + 3;

	total = probe(*base, pp, qq, 2);

	try {
		Both &br = dynamic_cast<Both &>(*base);
		total = total + *br.extra;
	} catch (const std::bad_cast &e2) {
		total = total - **qq;
	}

	try {
		Both &br2 = dynamic_cast<Both &>(*rp);
		total = total + *br2.extra;
	} catch (const std::bad_cast &e3) {
		total = total + **pp;
	}

	if (total > 0) {
		total = total + *p + *q;
	} else {
		total = total - *r;
	}

	delete *bpp;
	delete rp;

	return 0;
}
