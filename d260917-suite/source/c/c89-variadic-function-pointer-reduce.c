// <original>

#include <stdarg.h>

typedef int (*binop)(int, int);

int add(int a, int b) {
	return a + b;
}

int sub(int a, int b) {
	return a - b;
}

int mul(int a, int b) {
	return a * b;
}

int apply_ptrs(int n, ...) {
	va_list ap;
	int i;
	int *p;
	int acc;
	acc = 0;
	va_start(ap, n);
	for (i = 0; i < n; i = i + 1) {
		p = va_arg(ap, int *);
		if (p != 0) {
			acc = add(acc, *p);
		}
	}
	va_end(ap);
	return acc;
}

int reduce_ops(int seed, int n, ...) {
	va_list ap;
	int i;
	int **pp;
	binop f;
	int acc;
	acc = seed;
	va_start(ap, n);
	for (i = 0; i < n; i = i + 1) {
		f = va_arg(ap, binop);
		pp = va_arg(ap, int **);
		if (f != 0 && pp != 0 && *pp != 0) {
			acc = f(acc, **pp);
		} else if (f != 0) {
			acc = f(acc, i);
		}
	}
	va_end(ap);
	return acc;
}

int main(void) {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int total;
	binop f;

	x = 4;
	y = 7;
	z = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	total = apply_ptrs(3, p, q, &z);
	total = total + *p + *q;

	f = sub;
	total = reduce_ops(total, 2, f, pp, mul, qq);

	if (total > 0) {
		**pp = **pp + 1;
	} else {
		**qq = **qq - 1;
	}

	*pp = q;
	*q = *p + z;
	total = total + **pp + **qq;

	return 0;
}
