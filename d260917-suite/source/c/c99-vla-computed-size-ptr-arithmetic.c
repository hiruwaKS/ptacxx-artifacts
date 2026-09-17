// <original>

int gbase;
int gother;

int *advance(int *a, int n) {
	int *r;
	int i;
	r = a;
	for (i = 0; i < n; i = i + 1) {
		r = r + 1;
	}
	return r;
}

int count_positive(int n, int *a) {
	int i;
	int c = 0;
	for (i = 0; i < n; i = i + 1) {
		if (*a > 0) {
			c = c + 1;
		}
		a = a + 1;
	}
	return c;
}

void mirror(int n, int *a, int **out) {
	int i;
	int *p;
	p = a;
	for (i = 0; i < n; i = i + 1) {
		p[i] = -p[i];
	}
	*out = a;
}

int main() {
	int n = 6;
	int i;
	int x = 4;
	int y = 9;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *via;
	int vla[n];
	int *vp;
	int total;

	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	vp = vla;
	for (i = 0; i < n; i = i + 1) {
		vp[i] = i - 2;
	}
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 1;

	mirror(n, vla, &via);
	**pp = **pp + *via;
	q = advance(vla, 3);
	*q = *q + 1;

	total = count_positive(n, vla);
	for (i = 0; i < n; i = i + 1) {
		if (vla[i] != 0) {
			total = total + vla[i];
		}
	}

	if (total > 0) {
		total = total - x;
	} else if (total < 0) {
		total = total + y;
	} else {
		total = 0;
	}
	return 0;
}
