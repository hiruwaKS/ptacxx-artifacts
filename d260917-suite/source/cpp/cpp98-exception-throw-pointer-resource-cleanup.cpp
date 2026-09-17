// <original>

#include <cstdio>

struct Resource {
	int id;
	int *value;
};

int g_store;
int *g_ptr = &g_store;
int **g_dptr = &g_ptr;

Resource *acquire(int *v, int id) {
	Resource *r;
	r = new Resource;
	r->id = id;
	r->value = v;
	if (v == 0) {
		throw r;
	}
	if (*v < 0) {
		throw g_dptr;
	}
	return r;
}

int consume(Resource **res, int **out) {
	int s;
	if (*res == 0) {
		throw *out;
	}
	s = *(*res)->value;
	if ((*res)->id > 0) {
		s = s + **g_dptr;
	}
	**out = **out + s;
	return s;
}

int process(int *v, int id, int **out) {
	Resource *res;
	int rc;
	res = 0;
	rc = 0;
	try {
		res = acquire(v, id);
		consume(&res, out);
	} catch (Resource *rp) {
		rc = rp->id + 100;
		delete rp;
		res = 0;
	} catch (int **dp) {
		rc = **dp + 200;
	} catch (...) {
		rc = 300;
	}
	if (res != 0) {
		delete res;
	}
	return rc;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int total;
	int *pt;
	int **ppt;
	int rc;

	x = 5;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	*g_dptr = &y;
	*pp = &y;
	*q = 9;
	**qq = **qq + 1;

	total = 0;
	pt = &total;
	ppt = &pt;
	rc = process(p, 1, ppt);
	if (rc != 0) {
		total = total + rc;
	}
	rc = process(0, 2, ppt);
	if (rc != 0) {
		total = total + rc;
	}
	rc = process(q, 3, ppt);
	if (rc != 0) {
		total = total - rc;
	}
	return 0;
}
