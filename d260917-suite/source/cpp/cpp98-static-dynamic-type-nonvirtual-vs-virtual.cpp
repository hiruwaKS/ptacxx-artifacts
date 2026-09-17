// <original>

struct Counter {
	int *value;
	int **shared;

	Counter(int *v, int **s) {
		value = v;
		shared = s;
	}

	int step() {
		return *value + 1;
	}

	virtual int tick() {
		return *value;
	}
};

struct Doubler : Counter {
	Doubler(int *v, int **s) : Counter(v, s) {
	}

	int step() {
		return *value + 2;
	}

	virtual int tick() {
		return *value * 2 + **shared;
	}
};

int run(Counter *c, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			s = s + c->step();
		} else {
			s = s + c->tick();
		}
	}
	if (s == 0) {
		s = **pp;
	}
	return s;
}

int main() {
	int x = 6;
	int y = 7;
	int *p = &x;
	int *q = &y;
	int **pp = &p;
	int **qq = &q;
	Doubler d(p, pp);
	Counter *cp = &d;
	Counter **cpp = &cp;
	int total;

	**pp = **pp + 3;
	*cp->value = *cp->value + 1;

	total = run(*cpp, qq, 4);
	total = total + cp->step() + cp->tick();

	if (total > 0) {
		total = total + **qq;
	} else {
		total = total - **pp;
	}

	return 0;
}
