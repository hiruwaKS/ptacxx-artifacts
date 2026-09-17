// <original>

#include <new>
#include <cstddef>

struct Block {
	int *head;
	int **tail;
};

int churn(Block *b, std::size_t n, int **a, int **c) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			b[i].head = *a;
			b[i].tail = a;
		} else {
			b[i].head = *c;
			b[i].tail = c;
		}
		s = s + *b[i].head + **b[i].tail;
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
	std::size_t n;
	Block *arr;
	Block *one;
	int total;

	x = 8;
	y = 3;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	n = 4;

	arr = new (std::align_val_t(64)) Block[n];
	one = new (std::align_val_t(64)) Block;

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = churn(arr, n, pp, qq);
	one->head = *pp;
	one->tail = qq;
	total = total + *one->head + **one->tail;

	delete one;
	delete[] arr;

	if (total > 0 && **pp > 0) {
		total = total - x;
	} else {
		total = total + y;
	}

	return 0;
}
