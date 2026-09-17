// <original>

#include <stdlib.h>

struct Buffer {
	int *data;
	int **rows;
	int len;

	Buffer(int n) {
		int i;
		len = n;
		data = (int *)malloc(sizeof(int) * n);
		rows = (int **)malloc(sizeof(int *) * n);
		for (i = 0; i < n; i = i + 1) {
			data[i] = i + 1;
			rows[i] = &data[i];
		}
	}

	Buffer(const Buffer &other) {
		int i;
		len = other.len;
		data = (int *)malloc(sizeof(int) * len);
		rows = (int **)malloc(sizeof(int *) * len);
		for (i = 0; i < len; i = i + 1) {
			data[i] = other.data[i];
			rows[i] = &data[i];
		}
	}

	~Buffer() {
		free(rows);
		free(data);
	}
};

int shallowSum(int *a, int *b) {
	int *p;
	int *q;
	p = a;
	q = b;
	return *p + *q;
}

int deepSum(int **ra, int **rb, int n) {
	int i;
	int s = 0;
	int **pp;
	pp = ra;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			s = s + **pp;
		} else {
			s = s + **rb;
		}
		pp = pp + 1;
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
	Buffer original(4);
	Buffer copy(original);
	int total;

	x = 10;
	y = 20;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;

	*original.rows[0] = *original.rows[0] + 5;
	*original.data = *original.data + 1;

	total = shallowSum(p, q);
	total = total + deepSum(copy.rows, original.rows, copy.len);

	if (total > 0 && **pp > 0) {
		total = total + **qq;
	} else {
		total = total - 1;
	}

	return 0;
}
