// <original>

int gcount;

struct Base {
	int *p;
	int **pp;

	Base(int *a, int **b) {
		p = a;
		pp = b;
		gcount = gcount + 1;
	}

	virtual ~Base() {
		if (p != 0) {
			*p = *p + 1;
		}
		if (pp != 0) {
			**pp = **pp + 2;
		}
		gcount = gcount - 1;
	}

	virtual int value() {
		return *p;
	}
};

struct Derived : Base {
	int *q;

	Derived(int *a, int **b, int *c) : Base(a, b) {
		q = c;
	}

	virtual ~Derived() {
		if (q != 0) {
			*q = *q + 3;
		}
	}

	virtual int value() {
		return *q + **pp;
	}
};

int accumulate(Base **bpp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*bpp)->value();
		} else {
			s = s + **qq;
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
	int **pp;
	int **qq;
	Base *bp;
	Base **bpp;
	int total;

	x = 1;
	y = 2;
	z = 3;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	bp = new Derived(p, pp, q);
	bpp = &bp;

	**pp = **pp + 4;
	*bp->p = *bp->p + z;

	total = accumulate(bpp, qq, 2);
	total = total + *bp->p;

	if (total > 0) {
		total = total + **qq;
	} else {
		total = total - *q;
	}

	delete *bpp;

	return 0;
}
