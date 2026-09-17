// <original>

int gcount;

struct Cell {
	int *value;
	int **ref;

	Cell(int *v, int **r) {
		value = v;
		ref = r;
	}

	int get() {
		return *value + **ref;
	}

	void put(int v) {
		*value = v;
		**ref = **ref + 1;
	}
};

int adjust(int **pp, void **vv, int mode) {
	if (mode == 0) {
		return **pp;
	} else if (mode == 1) {
		int *ip = static_cast<int *>(vv[0]);
		return *ip;
	} else {
		return **pp + 1;
	}
}

int drain(Cell **cc, void **vv, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*cc)->get();
		} else if (i == 1) {
			int *ip = static_cast<int *>(vv[0]);
			s = s + *ip;
		} else {
			s = s + **pp;
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
	void *vp;
	void **vpp;
	Cell *c;
	Cell **cc;
	int total;

	x = 10;
	y = 20;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	c = new Cell(p, pp);
	cc = &c;

	vp = static_cast<void *>(q);
	vpp = &vp;

	total = drain(cc, vpp, qq, 3);
	total = total + adjust(qq, vpp, 1);

	int *r = static_cast<int *>(*vpp);
	*r = *r + 1;
	total = total + *r;

	Cell *c2 = static_cast<Cell *>(static_cast<void *>(c));
	c2->put(7);
	total = total + c2->get();

	if (total > 0) {
		total = total - *p;
	} else {
		total = total - *q;
	}

	gcount = total;

	delete c;

	return 0;
}
