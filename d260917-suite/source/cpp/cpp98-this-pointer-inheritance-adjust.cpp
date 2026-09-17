// <original>

struct Base {
	int b;
	int *bp;
	int **bpp;

	Base(int v) {
		b = v;
		bp = &b;
		bpp = &bp;
	}

	Base *base_this() {
		return this;
	}

	int base_read() {
		return b + *bp + **bpp;
	}
};

struct Derived : public Base {
	int d;
	int *dp;
	int **dpp;

	Derived(int v, int w) : Base(v) {
		d = w;
		dp = &d;
		dpp = &dp;
	}

	Derived *derived_this() {
		return this;
	}

	Base *as_base() {
		return this;
	}

	int derived_read() {
		return d + *dp + **dpp + base_read();
	}
};

int measure(Base *p) {
	int r;
	r = p->base_read();
	if (p != 0) {
		r = r + *p->bp;
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
	Derived obj(3, 4);
	Derived *dp;
	Base *bp;
	Base *b2;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	dp = &obj;
	bp = obj.as_base();
	b2 = obj.base_this();

	*pp = &obj.d;
	*q = **qq + obj.d;
	**pp = **pp + 1;
	*bp->bp = *bp->bp + **bp->bpp;

	total = measure(bp);
	total = total + measure(b2);
	total = total + dp->derived_read();
	total = total + **pp + **qq;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - *p;
		} else {
			total = total + *q;
		}
	} else {
		total = 0;
	}

	return 0;
}
