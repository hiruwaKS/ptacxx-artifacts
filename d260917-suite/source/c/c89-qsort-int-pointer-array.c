// <original>

#include <stdlib.h>

int gvals[8];
int *gptr;

int cmp_int_ptr(const void *a, const void *b) {
	int *pa;
	int *pb;
	pa = *(int *const *)a;
	pb = *(int *const *)b;
	if (*pa < *pb) {
		return -1;
	}
	if (*pa > *pb) {
		return 1;
	}
	return 0;
}

int sum_ptrs(int **arr, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + *arr[i];
	}
	return s;
}

void fill(int **arr, int **src, int n) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		arr[i] = src[i];
	}
}

int main(void) {
	int i;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *parr[8];
	int *backup[8];
	int total;
	int swapped;

	for (i = 0; i < 8; i = i + 1) {
		gvals[i] = 7 - i;
	}
	p = gvals;
	q = &gvals[7];
	pp = &p;
	qq = &q;
	gptr = *pp;

	for (i = 0; i < 8; i = i + 1) {
		parr[i] = &gvals[i];
	}
	fill(backup, parr, 8);
	qsort(parr, 8, sizeof(int *), cmp_int_ptr);

	total = sum_ptrs(parr, 8);
	if (total > 0) {
		total = total + **pp;
	} else {
		total = total + **qq;
	}

	swapped = 0;
	for (i = 0; i < 8; i = i + 1) {
		if (*parr[i] != *backup[i]) {
			swapped = swapped + 1;
		}
	}
	if (swapped > 0 && total > 0) {
		total = total - swapped;
	}
	return 0;
}
