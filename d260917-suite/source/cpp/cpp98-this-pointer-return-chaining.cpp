// <original>

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

struct Counter {
	int value;
	int *slot;
	int **dptr;

	Counter(int v, int *p, int **pp) {
		value = v;
		slot = p;
		dptr = pp;
	}

	Counter &add(int n) {
		value = value + n;
		return *this;
	}

	Counter &scale(int n) {
		value = value * n;
		return *this;
	}

	Counter &bind(int *p, int **pp) {
		slot = p;
		dptr = pp;
		return *this;
	}

	int read() {
		int r;
		r = value + *slot;
		if (dptr != 0) {
			r = r + **dptr;
		}
		return r;
	}
};

int chain(Counter *c, int n) {
	int i;
	int acc;
	acc = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			c->add(i);
		} else {
			c->scale(2);
		}
		acc = acc + c->read();
	}
	return acc;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Counter *cp;
	Counter c(1, &x, 0);

	x = 2;
	y = 3;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	c.bind(p, pp);
	cp = &c;
	c.bind(p, pp).add(5).scale(2);
	**pp = **pp + 1;
	*q = *q + **qq;

	cp->bind(q, qq).add(3);
	*pp = q;

	cp->add(1).scale(3).add(2);
	**qq = **qq + *p;

	if (cp->read() > 0) {
		cp->add(1);
	}

	return 0;
}
