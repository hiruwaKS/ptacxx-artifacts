// <original>

int gsum;

struct Base {
	int *bp;
	int **bpp;

	Base(int *p, int **pp) {
		bp = p;
		bpp = pp;
	}

	virtual ~Base() {}

	int read() {
		return *bp + **bpp;
	}
};

struct Derived : Base {
	int *dp;
	int **dpp;

	Derived(int *p, int **pp, int *q, int **qq) : Base(p, pp) {
		dp = q;
		dpp = qq;
	}

	int extra() {
		return *dp + **dpp;
	}
};

int touch(Base **bb, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*bb)->read();
		} else if (i == 1) {
			s = s + **pp;
		} else {
			s = s + *(*bb)->bp;
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
	Base *b;
	Derived *d;
	Base **bb;
	Derived **dd;
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	d = new Derived(p, pp, q, qq);
	b = static_cast<Base *>(d);
	bb = &b;
	dd = &d;

	total = touch(bb, qq, 3);

	Derived *back = static_cast<Derived *>(b);
	*back->dp = *back->dp + 1;
	**back->dpp = **back->dpp + 2;
	total = total + back->extra();

	Base *up = static_cast<Base *>(*dd);
	total = total + *up->bp;

	if (total > 0) {
		total = total + *p;
	} else {
		total = total + *q;
	}

	gsum = total;

	delete d;

	return 0;
}
