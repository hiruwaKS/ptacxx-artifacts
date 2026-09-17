// <original>

#include <cstdio>

struct BaseError {
	int code;
	int *slot;
};

struct DerivedError : BaseError {
	int **extra;
};

int g_v;
int *g_p = &g_v;
int **g_pp = &g_p;

void may_throw(int *v, int **out) {
	if (v == 0) {
		BaseError e;
		e.code = 1;
		e.slot = g_p;
		throw e;
	}
	if (*v < 0) {
		DerivedError d;
		d.code = 2;
		d.slot = g_p;
		d.extra = g_pp;
		throw d;
	}
	**out = **out + *v;
}

int classify(int *v, int **out) {
	int r;
	r = 0;
	try {
		may_throw(v, out);
	} catch (DerivedError &d) {
		r = d.code + **d.extra;
	} catch (BaseError &b) {
		r = b.code + *b.slot;
	} catch (...) {
		r = -1;
	}
	return r;
}

int walk(int **vals, int n, int **acc) {
	int i;
	int r;
	r = 0;
	for (i = 0; i < n; i = i + 1) {
		if (vals[i] == 0) {
			r = r + 1;
		} else {
			r = r + classify(vals[i], acc);
		}
	}
	return r;
}

int main() {
	int a;
	int b;
	int c;
	int *pa;
	int *pb;
	int **ppa;
	int **ppb;
	int *vals[3];
	int total;
	int *pt;
	int **ppt;
	int rc;

	a = 3;
	b = -4;
	c = 0;
	pa = &a;
	pb = &b;
	ppa = &pa;
	ppb = &pb;

	vals[0] = &a;
	vals[1] = &b;
	vals[2] = 0;

	*ppa = &c;
	*ppb = &a;
	**ppa = **ppa + 7;
	*pa = *pa + 1;

	total = 0;
	pt = &total;
	ppt = &pt;
	rc = walk(vals, 3, ppt);
	if (rc != 0) {
		total = total + rc;
	}
	if (total > 0) {
		total = total - **ppa;
	} else {
		total = total + **ppb;
	}
	return 0;
}
