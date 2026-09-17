// <original>

int gbase;
int gother;

void fill_ptrs(int n, int *arr[n], int *a, int *b) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			arr[i] = a;
		} else {
			arr[i] = b;
		}
	}
}

int deref_all(int n, int *arr[n]) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + *arr[i];
	}
	return s;
}

int **find_slot(int **base, int n, int idx) {
	int **r;
	if (idx < 0 || idx >= n) {
		r = base;
	} else {
		r = base + idx;
	}
	return r;
}

int main() {
	int n = 4;
	int i;
	int x = 3;
	int y = 5;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int **slot;
	int *ptrarr[n];
	int total;

	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	fill_ptrs(n, ptrarr, p, q);
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;

	total = deref_all(n, ptrarr);

	slot = find_slot(ptrarr, n, 1);
	**slot = **slot + 1;

	for (i = 0; i < n; i = i + 1) {
		if (*ptrarr[i] > 0) {
			total = total + *ptrarr[i];
		}
	}

	if (total > 0) {
		total = total - x;
	}
	return 0;
}
