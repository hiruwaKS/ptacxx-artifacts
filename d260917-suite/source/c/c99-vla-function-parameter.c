// <original>

int gbase;
int gother;

int sum_vla(int n, int a[n]) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + a[i];
	}
	return s;
}

void fill_vla(int n, int a[n], int *src, int **pp) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		a[i] = *src + i;
		**pp = **pp + 1;
	}
}

int *select_ptr(int *a, int *b, int flag) {
	int *r;
	if (flag) {
		r = a;
	} else {
		r = b;
	}
	return r;
}

int main() {
	int n = 4;
	int i;
	int x = 1;
	int y = 2;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *via;
	int total;
	int vla[n];
	int vla2[n];

	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	fill_vla(n, vla, p, pp);
	fill_vla(n, vla2, q, qq);

	via = select_ptr(p, q, 1);
	*via = *via + 1;
	**pp = **pp + **qq;

	total = sum_vla(n, vla) + sum_vla(n, vla2);
	if (total > 0 && x > 0) {
		total = total - x;
	} else if (total == 0 || y == 0) {
		total = total + y;
	} else {
		total = 0;
	}
	for (i = 0; i < n; i = i + 1) {
		total = total + vla[i];
	}
	return 0;
}
