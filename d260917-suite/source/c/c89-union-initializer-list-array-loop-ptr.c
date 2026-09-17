// <original>

int gv[4];

union Cell {
	int *p;
	int **pp;
};

int *gptr = &gv[0];
union Cell gcells[4] = { { &gv[0] }, { &gv[1] }, { &gv[2] }, { &gv[3] } };

void bump(int **pp, int d) {
	if (d > 0) {
		**pp = **pp + d;
	} else if (d < 0) {
		**pp = **pp - 1;
	} else {
		**pp = 0;
	}
}

int sum_cells(union Cell *cells, int n, int **pp) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			s = s + *cells[i].p;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int i;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int total;
	union Cell local = { &a };
	union Cell *cp;

	a = 1;
	b = 2;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;

	cp = &local;

	*pp = &b;
	*q = 7;
	**pp = **pp + 1;
	*cp->p = 8;

	bump(pp, 2);
	bump(qq, -1);

	total = sum_cells(gcells, 4, pp);
	total = total + **qq + *cp->p;

	for (i = 0; i < 2; i = i + 1) {
		if (i == 0) {
			total = total + *p;
		} else {
			total = total - *q;
		}
	}

	return 0;
}
