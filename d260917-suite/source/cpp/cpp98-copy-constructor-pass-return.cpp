// <original>

#include <stdlib.h>

struct Vec {
	int *slot;
	int **index;
	int n;

	Vec(int size) {
		int i;
		n = size;
		slot = (int *)malloc(sizeof(int) * n);
		index = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i = i + 1) {
			slot[i] = i * i;
			index[i] = &slot[i];
		}
	}

	Vec(const Vec &o) {
		int i;
		n = o.n;
		slot = (int *)malloc(sizeof(int) * n);
		index = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i = i + 1) {
			slot[i] = o.slot[i];
			index[i] = &slot[i];
		}
	}

	~Vec() {
		free(index);
		free(slot);
	}
};

Vec bump(Vec v) {
	int i;
	for (i = 0; i < v.n; i = i + 1) {
		*v.index[i] = *v.index[i] + 1;
	}
	return v;
}

int consume(Vec v, int **pp) {
	int i;
	int s = 0;
	for (i = 0; i < v.n; i = i + 1) {
		if (**pp > 0) {
			s = s + *v.slot;
		} else {
			s = s + *v.index[i];
		}
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
	Vec base(3);
	Vec result = bump(base);
	int total;

	x = 5;
	y = 6;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 2;
	**qq = **qq + 3;
	*p = *p + *q;

	total = consume(result, pp);
	total = total + **qq + *result.slot;

	if (total > 0 && **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
