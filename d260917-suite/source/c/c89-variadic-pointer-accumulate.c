// <original>

#include <stdarg.h>

int gx;
int gy;

int *pick(int **slot) {
	int *p;
	p = *slot;
	if (p == 0) {
		p = &gx;
	} else if (*p < 0) {
		p = &gy;
	}
	return p;
}

int sum_ptrs(int n, ...) {
	va_list ap;
	int i;
	int *p;
	int **pp;
	int s;
	s = 0;
	va_start(ap, n);
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			p = va_arg(ap, int *);
			s = s + *p;
		} else {
			pp = va_arg(ap, int **);
			if (pp != 0 && *pp != 0) {
				s = s + **pp;
			}
		}
	}
	va_end(ap);
	return s;
}

void bump(int **pp, int *p) {
	if (pp != 0) {
		*pp = p;
	}
	if (p != 0) {
		*p = *p + 1;
	}
}

int main(void) {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *sel;
	int total;

	x = 3;
	y = 5;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	total = sum_ptrs(4, p, pp, q, qq);
	total = total + *p + **pp;

	sel = pick(qq);
	*sel = *sel + 2;

	bump(pp, &y);
	bump(qq, &x);

	if (total > 0 && sel != 0) {
		total = total - *p;
	} else {
		total = total + *q;
	}

	*pp = &x;
	**qq = **qq + *sel;

	return 0;
}
