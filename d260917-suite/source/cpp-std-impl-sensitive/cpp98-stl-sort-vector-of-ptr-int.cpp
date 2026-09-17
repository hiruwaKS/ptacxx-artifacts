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

struct GreaterPtr {
	bool operator()(int *a, int *b) const {
		return *a > *b;
	}
};

int gather(std::vector<int *> *v, int **pp) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < (int)v->size(); i = i + 1) {
		int *e;
		e = (*v)[i];
		if (e != 0) {
			s = s + *e;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int sortForward(std::vector<int *> *v, int *first, int **last) {
	std::sort(v->begin(), v->end(), LessPtr());
	*first = *(*v)[0];
	**last = *(*v)[v->size() - 1];
	return *first + **last;
}

int sortBackward(std::vector<int *> *v, int **pp) {
	std::sort(v->begin(), v->end(), GreaterPtr());
	**pp = *(*v)[0];
	return **pp;
}

int main() {
	int a;
	int b;
	int c;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	std::vector<int *> v;
	std::vector<int *> *vp;
	int total;

	a = 5;
	b = 1;
	c = 3;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	v.push_back(p);
	v.push_back(q);
	v.push_back(r);
	vp = &v;

	total = sortForward(vp, &a, qq);
	total = total + sortBackward(vp, pp);
	total = total + gather(vp, pp);

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_dptr = **g_dptr + *r;

	if (total > 0) {
		total = total - 1;
	} else {
		total = 0;
	}

	return 0;
}
