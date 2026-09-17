// <original>

#include <utility>
#include <vector>

int g_a;
int g_b;
int *g_p = &g_a;
int **g_pp = &g_p;

struct Owner {
	int *res;

	Owner() : res(0) {}
	explicit Owner(int *r) : res(r) {}

	Owner(Owner &&o) : res(o.res) {
		o.res = 0;
	}

	Owner &operator=(Owner &&o) {
		if (this != &o) {
			res = o.res;
			o.res = 0;
		}
		return *this;
	}

	int value() const {
		return res != 0 ? *res : 0;
	}
};

int drain(std::vector<Owner> *v) {
	int i;
	int s = 0;
	for (i = 0; i < (int)v->size(); ++i) {
		if ((*v)[i].res != 0) {
			s = s + *(*v)[i].res;
		} else {
			s = s - 1;
		}
	}
	return s;
}

void adopt(std::vector<Owner> *v, int **pp, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		Owner o(*pp);
		if (i == 0) {
			v->push_back(std::move(o));
		} else {
			v->push_back(Owner(*pp));
		}
	}
}

int moveInto(int *&&rp, int **pp) {
	int *t = rp;
	rp = 0;
	if (t != 0) {
		**pp = **pp + *t;
	} else {
		**pp = **pp - 1;
	}
	return **pp;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *s;
	int **pp;
	int **qq;
	std::vector<Owner> v;
	std::vector<Owner> w;
	int total;

	x = 7;
	y = 8;
	p = &x;
	q = &y;
	s = &x;
	pp = &p;
	qq = &q;

	*pp = &y;
	**qq = **qq + 1;
	*p = *p + 3;

	adopt(&v, qq, 3);

	w = std::move(v);
	total = drain(&w);
	total = total + moveInto(std::move(s), qq);
	total = total + *q + **pp + **qq + **g_pp;

	if (total > 0 && *q > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
