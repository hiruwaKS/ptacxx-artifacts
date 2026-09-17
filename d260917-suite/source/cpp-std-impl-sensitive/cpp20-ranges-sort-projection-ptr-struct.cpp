// <original>

#include <algorithm>
#include <ranges>
#include <vector>

struct Item {
	int value;
	int *ref;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

int sumValues(std::vector<Item *> *v, int **pp) {
	int s = 0;
	for (Item *e : *v) {
		if (e != 0) {
			s = s + e->value;
			if (e->ref != 0) {
				s = s + *e->ref;
			}
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int sortByValue(std::vector<Item *> *v, int *first, int **last) {
	std::ranges::sort(*v, {}, &Item::value);
	*first = (*v)[0]->value;
	**last = (*v)[v->size() - 1]->value;
	return *first + **last;
}

int maxByValue(std::vector<Item *> *v, int **pp) {
	auto m = std::ranges::max_element(*v, {}, &Item::value);
	if (m != v->end()) {
		**pp = (*m)->value;
	} else {
		**pp = 0;
	}
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
	std::vector<Item *> v;
	std::vector<Item *> *vp;
	Item i1;
	Item i2;
	Item i3;
	int total;

	a = 3;
	b = 7;
	c = 1;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;

	i1.value = 30;
	i1.ref = p;
	i2.value = 10;
	i2.ref = q;
	i3.value = 20;
	i3.ref = 0;

	v.push_back(&i1);
	v.push_back(&i2);
	v.push_back(&i3);
	vp = &v;

	total = sumValues(vp, pp);
	total = total + sortByValue(vp, &c, qq);
	total = total + maxByValue(vp, pp);

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_dptr = **g_dptr + *p;
	*(*vp)[0]->ref = *(*vp)[0]->ref + 2;

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
