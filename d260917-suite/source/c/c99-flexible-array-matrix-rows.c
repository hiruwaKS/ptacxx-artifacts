// <original>

#include <stdlib.h>

struct Matrix {
	int rows;
	int cols;
	int **rowptr;
	int cells[];
};

struct Matrix *make_matrix(int rows, int cols) {
	struct Matrix *m;
	m = (struct Matrix *)malloc(sizeof(struct Matrix) + rows * cols * sizeof(int));
	m->rows = rows;
	m->cols = cols;
	m->rowptr = (int **)malloc(rows * sizeof(int *));
	return m;
}

void bind_rows(struct Matrix *m) {
	int i;
	for (i = 0; i < m->rows; i = i + 1) {
		m->rowptr[i] = &m->cells[i * m->cols];
	}
}

void set_cell(struct Matrix *m, int r, int c, int v) {
	if (r >= 0 && r < m->rows && c >= 0 && c < m->cols) {
		m->rowptr[r][c] = v;
	} else {
		m->cells[0] = v;
	}
}

int get_cell(struct Matrix **mp, int **pp, int r, int c) {
	int v;
	if (r < (*mp)->rows && c < (*mp)->cols) {
		v = (*mp)->rowptr[r][c] + **pp;
	} else {
		v = **pp;
	}
	return v;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int **via;
	struct Matrix *m;
	struct Matrix *n;
	struct Matrix **mp;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	m = make_matrix(3, 3);
	n = make_matrix(2, 2);
	bind_rows(m);
	bind_rows(n);

	mp = &m;
	set_cell(m, 0, 0, *p);
	set_cell(n, 1, 1, *q);
	**pp = **pp + 4;
	**qq = **qq + 5;
	(*mp)->rowptr[1][1] = **pp;

	via = &q;
	**via = **via + 1;

	total = get_cell(mp, pp, 0, 0) + get_cell(&n, qq, 1, 1);
	total = total + **pp + **qq + **via;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(m->rowptr);
	free(n->rowptr);
	free(m);
	free(n);
	return 0;
}
