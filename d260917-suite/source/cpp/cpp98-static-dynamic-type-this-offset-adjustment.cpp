// <original>

struct A {
	int *pa;
	int **ppa;

	A(int *a, int **b) {
		pa = a;
		ppa = b;
	}

	virtual int f() {
		return *pa;
	}

	virtual int g() {
		return **ppa;
	}
};

struct B : A {
	int *pb;

	B(int *a, int **b, int *c) : A(a, b) {
		pb = c;
	}

	virtual int f() {
		return *pb + 100;
	}

	virtual int g() {
		return *pb + **ppa;
	}
};

struct C : B {
	int *pc;

	C(int *a, int **b, int *c, int *d) : B(a, b, c) {
		pc = d;
	}

	virtual int f() {
		return *pc + 200;
	}

	virtual int g() {
		return *pc + *pb + **ppa;
	}
};

int apply(A *a, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + a->f();
		} else if (i == 1) {
			s = s + a->g();
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int x = 1;
	int y = 2;
	int z = 3;
	int w = 4;
	int *p = &x;
	int *q = &y;
	int *r = &z;
	int *t = &w;
	int **pp = &p;
	int **qq = &q;
	C obj(p, pp, r, t);
	A *ap = &obj;
	B *bp = &obj;
	A **app = &ap;
	int total;

	**pp = **pp + 7;
	*bp->pb = *bp->pb + 1;

	total = apply(*app, qq, 3);
	total = total + bp->f() + ap->g();

	if (total > 0) {
		total = total + **qq;
	} else {
		total = total - **pp;
	}

	return 0;
}
