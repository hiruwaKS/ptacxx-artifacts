// <original>

#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

#if defined(__clang__) && (__clang_major__ < 15)
#define PAD_NO_VIEWS 1
#endif

int g_n;
int *g_ptr = &g_n;
int **g_dptr = &g_ptr;

int countBig(std::vector<int *> *v, int limit, int **pp) {
	auto n = std::ranges::count_if(*v, [limit](int *e) { return e != 0 && *e > limit; });
	if (n == 0) {
		**pp = **pp + 1;
	} else if (n > 2) {
		**pp = **pp - 1;
	}
	return (int)n;
}

int copyPositive(std::vector<int *> *v, std::vector<int> *out, int **pp) {
	for (int *e : *v) {
		if (e != 0) {
			out->push_back(*e);
		}
	}
#ifndef PAD_NO_VIEWS
	std::ranges::copy(*v | std::views::transform([](int *e) { return e != 0 ? *e : 0; }),
	                  std::back_inserter(*out));
#else
	for (int *e : *v) {
		out->push_back(e != 0 ? *e : 0);
	}
#endif
	return (int)out->size() + **pp;
}

int viewSum(std::vector<int *> *v, int **pp, int **qq) {
	int s = 0;
#ifndef PAD_NO_VIEWS
	auto view = *v | std::views::filter([](int *e) { return e != 0; }) |
	            std::views::transform([](int *e) { return *e; });
	for (int x : view) {
		s = s + x;
	}
#else
	for (int *e : *v) {
		if (e != 0) {
			s = s + *e;
		}
	}
#endif
	if (s > 0) {
		**pp = s;
	} else {
		**qq = s;
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
	std::vector<int> out;
	int total;

	a = 60;
	b = 70;
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

	total = countBig(vp, 50, pp);
	total = total + copyPositive(vp, &out, pp);
	total = total + viewSum(vp, pp, qq);

	**pp = **pp + 1;
	*q = *q + **qq;
	**g_dptr = **g_dptr + *r;
	*(*vp)[0] = *(*vp)[0] + 5;

	if (total > 0 && a > 0) {
		total = total - a;
	} else if (total < 0 || b < 0) {
		total = total + b;
	} else {
		total = 0;
	}

	return 0;
}
