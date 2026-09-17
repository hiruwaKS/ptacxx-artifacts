// <original>

int gcount;

struct Cell {
	const int *ro;
	int *rw;
	int **pp;
};

const int *pick(const int *a, const int *b, int flag) {
	if (flag == 0) {
		return a;
	} else if (flag == 1) {
		return b;
	}
	return 0;
}

int write_through(int *p, int v) {
	*p = *p + v;
	return *p;
}

int main() {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int **pp;
	int **qq;
	const int *c1;
	const int *c2;
	int *w;
	int **wp;
	Cell c;
	int total;

	x = 1;
	y = 2;
	z = 3;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	c1 = p;
	c2 = q;

	w = const_cast<int *>(pick(c1, c2, 0));
	*w = *w + 20;

	wp = const_cast<int **>(pp);
	*wp = q;
	**wp = **wp + 7;

	c.ro = c1;
	c.rw = w;
	c.pp = pp;

	total = *c.ro + *c.rw + **c.pp + **qq;

	total = total + write_through(w, 2);

	while (total > 0) {
		if (total % 2 == 0) {
			total = total - 1;
		} else {
			total = total - 2;
		}
		if (total < 0) {
			total = 0;
		}
	}

	switch (total % 2) {
	case 0:
		total = total + 1;
		break;
	case 1:
		total = total + 2;
		break;
	default:
		total = total + 3;
		break;
	}

	gcount = total + z;

	return 0;
}
