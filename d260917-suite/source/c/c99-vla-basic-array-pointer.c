// <original>

int gbase;
int gother;

int *pick(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = pick(b, a, depth - 1);
	}
	return r;
}

int sum_row(int n, int *row) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + *row;
		row = row + 1;
	}
	return s;
}

int main() {
	int n = 5;
	int i;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *via;
	int total;
	int vla[n];
	int *vp;
	int (*rowp)[n];
	int (*matp)[n];

	p = &gbase;
	q = &gother;
	pp = &p;
	qq = &q;

	vp = vla;
	for (i = 0; i < n; i = i + 1) {
		vla[i] = i + 1;
	}
	rowp = &vla;
	matp = &vla;

	*pp = &gother;
	*q = 6;
	**qq = **qq + 1;
	*vp = 10;

	total = sum_row(n, vla);
	via = pick(p, q, 2);
	**pp = **pp + *via;
	total = total + (*rowp)[0] + (*matp)[1];

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - gbase;
		} else {
			total = total + gother;
		}
	}
	return 0;
}
