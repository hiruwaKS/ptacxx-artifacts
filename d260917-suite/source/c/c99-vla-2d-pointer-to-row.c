// <original>

int gbase;
int gother;

void fill_matrix(int rows, int cols, int m[rows][cols], int *v) {
	int i;
	int j;
	for (i = 0; i < rows; i = i + 1) {
		for (j = 0; j < cols; j = j + 1) {
			m[i][j] = *v + i + j;
		}
	}
}

int sum_matrix(int rows, int cols, int m[rows][cols]) {
	int i;
	int j;
	int s = 0;
	for (i = 0; i < rows; i = i + 1) {
		for (j = 0; j < cols; j = j + 1) {
			s = s + m[i][j];
		}
	}
	return s;
}

int *pick(int *a, int *b, int d) {
	int *r;
	if (d <= 0) {
		r = a;
	} else {
		r = pick(b, a, d - 1);
	}
	return r;
}

int main() {
	int rows = 3;
	int cols = 4;
	int i;
	int j;
	int x = 2;
	int y = 7;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *via;
	int m[rows][cols];
	int (*rowp)[cols];
	int total;

	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	fill_matrix(rows, cols, m, p);
	rowp = m;
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 1;

	total = sum_matrix(rows, cols, m);
	via = pick(p, q, 2);
	**pp = **pp + *via;

	for (i = 0; i < rows; i = i + 1) {
		for (j = 0; j < cols; j = j + 1) {
			total = total + rowp[i][j];
		}
	}

	if (total > 0 && x > 0) {
		total = total - x;
	}
	return 0;
}
