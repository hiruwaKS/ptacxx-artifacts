// <original>

#include <stdlib.h>

int gdata[6];
int *gslots[6];
int **gindex[6];

int cmp_slot(const void *a, const void *b) {
	int **pa;
	int **pb;
	pa = (int **)a;
	pb = (int **)b;
	if (**pa < **pb) {
		return -1;
	} else if (**pa > **pb) {
		return 1;
	} else {
		return 0;
	}
}

int cmp_ptr_ptr(const void *a, const void *b) {
	int *const *pa;
	int *const *pb;
	pa = (int *const *)a;
	pb = (int *const *)b;
	if (**pa < **pb) {
		return -1;
	} else if (**pa > **pb) {
		return 1;
	} else {
		return 0;
	}
}

int reduce(int ***base, int n, int ***out) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (**base[i] % 2 == 0) {
			s = s + **base[i];
		} else {
			s = s - **base[i];
		}
		out[i] = base[i];
	}
	return s;
}

int main(void) {
	int *p;
	int *q;
	int **pp;
	int **qq;
	int **tmp[6];
	int *arr[6];
	int **copy;
	int total;
	int i;

	for (i = 0; i < 6; i = i + 1) {
		gdata[i] = (i * 5) % 7;
		gslots[i] = &gdata[i];
		gindex[i] = &gslots[i];
	}
	p = &gdata[0];
	q = &gdata[5];
	pp = &p;
	qq = &q;

	total = reduce(gindex, 6, tmp);
	qsort(gindex, 6, sizeof(int **), cmp_slot);

	for (i = 0; i < 6; i = i + 1) {
		arr[i] = *gindex[i];
	}
	copy = arr;
	qsort(copy, 6, sizeof(int *), cmp_ptr_ptr);
	total = total + **pp + **qq;

	for (i = 0; i < 6; i = i + 1) {
		if (*arr[i] > **gindex[i]) {
			total = total + 1;
		} else if (total > 0 && arr[i] != 0) {
			total = total - 1;
		} else {
			total = total + 0;
		}
	}
	return 0;
}
