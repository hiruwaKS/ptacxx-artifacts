// <original>

struct RefA {
	int *pa;

	RefA(int *a) {
		pa = a;
	}

	virtual int idA() {
		return 1;
	}

	virtual int readA() {
		return *pa;
	}
};

struct RefB {
	int *pb;
	int **ppb;

	RefB(int *b, int **c) {
		pb = b;
		ppb = c;
	}

	virtual int idB() {
		return 2;
	}

	virtual int readB() {
		return *pb + **ppb;
	}
};

struct Both : RefA, RefB {
	int *own;

	Both(int *a, int *b, int **c, int *o) : RefA(a), RefB(b, c) {
		own = o;
	}

	virtual int idA() {
		return 11;
	}

	virtual int idB() {
		return 22;
	}

	virtual int readA() {
		return *pa + *own;
	}

	virtual int readB() {
		return *pb + **ppb + *own;
	}
};

int probe(RefA *a, RefB *b, int **pp) {
	int s = 0;
	if (a != 0) {
		s = s + a->idA();
		s = s + a->readA();
	}
	if (b != 0) {
		s = s + b->idB();
		s = s + b->readB();
	}
	if (s == 0) {
		s = **pp;
	}
	return s;
}

int main() {
	int x = 3;
	int y = 4;
	int z = 5;
	int *p = &x;
	int *q = &y;
	int *o = &z;
	int **pp = &p;
	int **qq = &q;
	Both obj(p, q, pp, o);
	RefA *ap = &obj;
	RefB *bp = &obj;
	RefA **app = &ap;
	int total;

	**pp = **pp + 2;
	*bp->pb = *bp->pb + 1;

	total = probe(*app, bp, qq);
	total = total + ap->readA() + bp->readB();

	if (total > 0) {
		total = total + **qq;
	} else {
		total = total - **pp;
	}

	return 0;
}
