// <original>

#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

struct Cell {
	int id;
	int *val;
};

int g_seed;
int *g_ptr = &g_seed;
int **g_dptr = &g_ptr;

int transformInto(std::vector<Cell *> *in, std::vector<int> *out, int **pp) {
	std::ranges::transform(*in, std::back_inserter(*out),
	                       [](Cell *c) { return c != 0 ? c->id : 0; });
	int s = 0;
	for (int x : *out) {
		s = s + x;
	}
	if (s == 0) {
		s = **pp;
	}
	return s;
}

int applyEach(std::vector<Cell *> *v, int **pp) {
	int s = 0;
	std::ranges::for_each(*v, [&s, pp](Cell *c) {
		if (c != 0 && c->val != 0) {
			s = s + *c->val;
		} else {
			s = s + **pp;
		}
	});
	return s;
}

int scaleAll(std::vector<Cell *> *v, int *factor, int **pp) {
	for (Cell *c : *v) {
		if (c != 0 && c->val != 0) {
			*c->val = *c->val * *factor;
		}
	}
	**pp = **pp + *factor;
	return **pp;
}

int main() {
	int a;
	int b;
	int c;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::vector<Cell *> v;
	std::vector<Cell *> *vp;
	std::vector<int> ids;
	Cell c1;
	Cell c2;
	Cell c3;
	int total;

	a = 2;
	b = 5;
	c = 3;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;

	c1.id = 1;
	c1.val = p;
	c2.id = 2;
	c2.val = q;
	c3.id = 3;
	c3.val = 0;

	v.push_back(&c1);
	v.push_back(&c2);
	v.push_back(&c3);
	vp = &v;

	total = transformInto(vp, &ids, pp);
	total = total + applyEach(vp, pp);
	total = total + scaleAll(vp, &c, qq);

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_dptr = **g_dptr + *p;
	*(*vp)[0]->val = *(*vp)[0]->val + 4;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - a;
		} else {
			total = total + b;
		}
	} else {
		total = 0;
	}

	return 0;
}
