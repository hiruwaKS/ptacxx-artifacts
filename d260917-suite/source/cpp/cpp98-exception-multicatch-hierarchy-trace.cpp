// <original>

#include <cstdio>

struct Error {
	int code;
	int *where;
	virtual ~Error() {}
};

struct IOError : Error {
	int **trace;
};

struct Value {
	int *p;
	int **pp;
};

int g_a;
int g_b;
int *g_p = &g_a;
int **g_pp = &g_p;

void fail_io(Value *v) {
	IOError e;
	e.code = 7;
	e.where = (v != 0 && v->p != 0) ? v->p : g_p;
	e.trace = g_pp;
	throw e;
}

int work(Value *v, int **acc) {
	int r;
	r = 0;
	try {
		if (v->p == 0) {
			throw Error();
		}
		if (*v->p < 0) {
			fail_io(v);
		}
		r = *v->p;
		if (v->pp != 0) {
			r = r + **v->pp;
		}
		**acc = **acc + r;
	} catch (IOError &e) {
		r = e.code + **e.trace;
		throw;
	} catch (Error &e) {
		r = e.code + *e.where;
	} catch (...) {
		r = -1;
	}
	return r;
}

int run(Value *vals, int n, int **acc) {
	int i;
	int r;
	int sub;
	r = 0;
	for (i = 0; i < n; i = i + 1) {
		sub = 0;
		try {
			sub = work(&vals[i], acc);
		} catch (IOError &e) {
			sub = 1000 + e.code;
		} catch (Error &e) {
			sub = 2000 + e.code;
		}
		r = r + sub;
	}
	return r;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Value vals[2];
	int total;
	int *pt;
	int **ppt;
	int rc;

	x = 4;
	y = -6;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	vals[0].p = &x;
	vals[0].pp = pp;
	vals[1].p = &y;
	vals[1].pp = &q;

	*pp = &y;
	*q = 11;
	**qq = **qq + 1;
	*g_pp = &x;

	total = 0;
	pt = &total;
	ppt = &pt;
	rc = run(vals, 2, ppt);
	if (rc != 0) {
		total = total + rc;
	}
	if (total > 0) {
		total = total - **g_pp;
	} else {
		total = total + **qq;
	}
	return 0;
}
