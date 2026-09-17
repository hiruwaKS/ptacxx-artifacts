// <original>

#include <stdlib.h>

struct Row {
	int *cells;
	int width;
};

int *find(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = find(a, b, depth - 1);
	}
	return r;
}

int **find2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = find2(b, a, depth - 1);
	}
	return r;
}

int **make_matrix(int rows, int cols) {
	int **m;
	int i;
	m = aligned_alloc(16, 64);
	if (m == 0) {
		return 0;
	}
	for (i = 0; i < rows; i = i + 1) {
		m[i] = aligned_alloc(16, 64);
		if (m[i] == 0) {
			return 0;
		}
	}
	return m;
}

int sum_rows(struct Row *rs, int n, int **pp, int **qq) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		switch (i) {
		case 0:
			s = s + *rs[i].cells;
			break;
		case 1:
			s = s + **pp;
			break;
		default:
			s = s + **qq;
			break;
		}
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	struct Row *rs;
	int **m;
	int i;

	rs = aligned_alloc(16, 64);
	m = make_matrix(4, 4);
	if (rs == 0 || m == 0) {
		free(rs);
		return 1;
	}

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	for (i = 0; i < 4; i = i + 1) {
		m[i][0] = i;
		m[i][1] = i + 1;
	}

	rs[0].cells = m[0];
	rs[0].width = 4;
	rs[1].cells = m[1];
	rs[1].width = 4;
	rs[2].cells = m[2];
	rs[2].width = 4;
	rs[3].cells = m[3];
	rs[3].width = 4;

	*m[0] = 10;
	*m[1] = 20;
	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 4;

	total = sum_rows(rs, 4, pp, qq);
	total = total + **m + *rs[1].cells;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	for (i = 0; i < 4; i = i + 1) {
		free(m[i]);
	}
	free(m);
	free(rs);

	return 0;
}
