// <original>

#include <algorithm>
#include <ranges>
#include <vector>

#if defined(__clang__) && (__clang_major__ < 15)
#define PAD_NO_VIEWS 1
#endif

int g_a;
int g_b;
int *g_p = &g_a;
int **g_pp = &g_p;

int sumEven(std::vector<int *> *v, int **pp) {
	int s = 0;
#ifndef PAD_NO_VIEWS
	auto view = *v | std::views::filter([](int *e) { return e != 0 && (*e % 2) == 0; });
	for (int *e : view) {
		s = s + *e;
	}
#else
	for (int *e : *v) {
		if (e != 0 && (*e % 2) == 0) {
			s = s + *e;
		}
	}
#endif
	if (s == 0) {
		s = **pp;
	} else if (s < 0) {
		s = -s;
	}
	return s;
}

int findValue(std::vector<int *> *v, int target, int **pp) {
	auto it = std::ranges::find(*v, target, [](int *e) { return e != 0 ? *e : -1; });
	if (it != v->end()) {
		**pp = **it;
		return 1;
	} else {
		**pp = -1;
		return 0;
	}
}

int findIfBig(std::vector<int *> *v, int **pp, int **qq) {
	auto it = std::ranges::find_if(*v, [](int *e) { return e != 0 && *e > 50; });
	if (it != v->end()) {
		**pp = **it;
	} else {
		**qq = **pp;
	}
	return **pp + **qq;
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

	a = 2;
	b = 4;
	c = 99;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	v.push_back(p);
	v.push_back(q);
	v.push_back(r);
	vp = &v;

	total = sumEven(vp, pp);
	total = total + findValue(vp, 4, qq);
	total = total + findIfBig(vp, pp, qq);

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_pp = **g_pp + *r;

	if (total > 0 && a > 0) {
		total = total - a;
	} else if (total < 0 || b < 0) {
		total = total + b;
	} else {
		total = 0;
	}

	return 0;
}
