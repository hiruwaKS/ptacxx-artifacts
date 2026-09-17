// <original>

#include <typeinfo>

int gtag;

struct Root {
	int *id;
	int **idp;

	Root(int *a, int **b) {
		id = a;
		idp = b;
	}

	virtual ~Root() {
		if (id != 0) {
			*id = *id + 1;
		}
	}

	virtual int tag() {
		return *id;
	}
};

struct Mid : virtual Root {
	int *mid;

	Mid(int *a, int **b, int *c) : Root(a, b) {
		mid = c;
	}

	virtual int tag() {
		return *mid + *id;
	}
};

struct Leaf : Mid {
	int *leaf;

	Leaf(int *a, int **b, int *c, int *d) : Root(a, b), Mid(a, b, c) {
		leaf = d;
	}

	virtual int tag() {
		return *leaf + *mid;
	}
};

int collect(Root **rpp, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		Root *cur = rpp[i];
		void *whole = dynamic_cast<void *>(cur);
		Leaf *lf = dynamic_cast<Leaf *>(cur);
		if (lf != 0) {
			s = s + *lf->leaf;
		} else if (whole != 0) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int d;
	int *p;
	int *q;
	int *r;
	int *t;
	int **pp;
	int **qq;
	Leaf *lp;
	Leaf **lpp;
	Root *root;
	Root *roots[2];
	void *whole;
	Leaf *back;
	int total;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	p = &a;
	q = &b;
	r = &c;
	t = &d;
	pp = &p;
	qq = &q;

	lp = new Leaf(p, pp, q, r);
	lpp = &lp;
	root = lp;
	roots[0] = root;
	roots[1] = new Mid(p, pp, q);

	whole = dynamic_cast<void *>(root);
	back = dynamic_cast<Leaf *>(root);
	*t = *t + *lp->leaf;
	**pp = **pp + *back->mid;

	total = collect(roots, pp, qq, 2);

	try {
		Leaf &lr = dynamic_cast<Leaf &>(*root);
		total = total + *lr.leaf;
	} catch (const std::bad_cast &e) {
		total = total - **qq;
	}

	if (whole != 0) {
		total = total + *p + *q + *r;
	} else {
		total = total - *t;
	}

	delete *lpp;
	delete roots[1];

	return 0;
}
