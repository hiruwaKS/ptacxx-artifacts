// <original>

#include <algorithm>
#include <vector>

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

struct LessPtr {
	bool operator()(int *a, int *b) const {
		return *a < *b;
	}
};

int *lowerBound(std::vector<int *> *v, int *key) {
	std::vector<int *>::iterator it;
	it = std::lower_bound(v->begin(), v->end(), key, LessPtr());
	if (it == v->end()) {
		return 0;
	}
	return *it;
}

int span(std::vector<int *> *v, int **lo, int **hi) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < (int)v->size(); i = i + 1) {
		int *e;
		e = (*v)[i];
		if (e != 0) {
			s = s + *e;
		} else {
			s = s + **lo;
		}
	}
	**hi = **hi + s;
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int *p;
	int *q;
	int *r;
	int *hit;
	int **pp;
	int **qq;
	std::vector<int *> v;
	std::vector<int *> *vp;
	int total;

	a = 4;
	b = 2;
	c = 6;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	v.push_back(p);
	v.push_back(q);
	v.push_back(r);
	vp = &v;

	std::sort(vp->begin(), vp->end(), LessPtr());
	hit = lowerBound(vp, q);
	total = span(vp, pp, qq);
	if (hit != 0) {
		total = total + *hit;
	} else {
		total = total + **g_dptr;
	}

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_dptr = **g_dptr + *r;

	return 0;
}
