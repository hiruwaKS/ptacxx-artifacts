// <original>

#include <stdlib.h>

struct IntArray {
	int *buf;
	int **view;
	int n;

	IntArray(int size) {
		int i;
		n = size;
		buf = (int *)malloc(sizeof(int) * n);
		view = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i = i + 1) {
			buf[i] = 0;
			view[i] = &buf[i];
		}
	}

	IntArray(const IntArray &o) {
		int i;
		n = o.n;
		buf = (int *)malloc(sizeof(int) * n);
		view = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i = i + 1) {
			buf[i] = o.buf[i];
			view[i] = &buf[i];
		}
	}

	IntArray &operator=(const IntArray &o) {
		int i;
		if (this == &o) {
			return *this;
		}
		if (n != o.n) {
			free(view);
			free(buf);
			n = o.n;
			buf = (int *)malloc(sizeof(int) * n);
			view = (int **)malloc(sizeof(int *) * n);
		}
		for (i = 0; i < n; i = i + 1) {
			buf[i] = o.buf[i];
			view[i] = &buf[i];
		}
		return *this;
	}

	~IntArray() {
		free(view);
		free(buf);
	}
};

int fill(int *a, int *b, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		*a = *a + i;
		*b = *b + i;
		s = s + *a + *b;
	}
	return s;
}

int scan(int **vv, int n) {
	int i;
	int s = 0;
	int **p = vv;
	i = 0;
	while (i < n) {
		if (**p > 0) {
			s = s + **p;
		} else {
			s = s - 1;
		}
		p = p + 1;
		i = i + 1;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	IntArray a(3);
	IntArray b(3);
	IntArray c(5);
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	*pp = &y;
	**pp = **pp + 4;
	*q = *q + *p;

	*a.view[0] = *a.view[0] + 7;
	*a.buf = *a.buf + 3;

	IntArray *self = &a;
	a = *self;
	b = a;
	c = b;

	total = fill(p, q, 3);
	total = total + scan(c.view, c.n);

	if (total > 0 || **qq > 0) {
		total = total + **pp;
	} else {
		total = total - 1;
	}

	return 0;
}
