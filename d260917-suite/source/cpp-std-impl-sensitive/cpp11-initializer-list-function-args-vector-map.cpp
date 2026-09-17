// <original>

#include <vector>
#include <map>
#include <initializer_list>

int g_base;
int g_other;
int *g_p = &g_base;
int *g_q = &g_other;

static std::initializer_list<int *> g_first = { &g_base, &g_other, g_p };
static std::initializer_list<int *> g_second = { g_p, g_q };
static std::initializer_list<int **> g_refs = { &g_p, &g_q };

std::initializer_list<int *> pick(int **pp, int **qq, int which) {
	if (which != 0) {
		return g_first;
	}
	return g_second;
}

std::initializer_list<int **> pickRefs(int **pp, int **qq) {
	if (pp != 0 && qq != 0) {
		return g_refs;
	}
	return std::initializer_list<int **>();
}

int sum(std::initializer_list<int *> xs, int **acc) {
	int s = 0;
	std::initializer_list<int *>::iterator it;
	for (it = xs.begin(); it != xs.end(); ++it) {
		s = s + **it;
	}
	**acc = **acc + s;
	return s;
}

int sumRefs(std::initializer_list<int **> xs) {
	int s = 0;
	std::initializer_list<int **>::iterator it;
	for (it = xs.begin(); it != xs.end(); ++it) {
		if (*it != 0) {
			s = s + ***it;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int *pa;
	int *pb;
	int **pp;
	int **qq;
	std::vector<int *> v = { &a, &b };
	std::map<int, int **> m = { { 1, &pa }, { 2, &pb } };
	std::vector<int **> refs = { &pa, &pb };
	int total;

	a = 4;
	b = 9;
	pa = &a;
	pb = &b;
	pp = &pa;
	qq = &pb;

	total = sum({ pa, pb, g_p }, pp);
	total = total + sumRefs({ pp, qq });
	total = total + sum(pick(pp, qq, 1), qq);
	total = total + sumRefs(pickRefs(pp, qq));

	total = total + *v[0] + *v[1];
	total = total + **m[1];
	total = total + **refs[0] + **refs[1];
	total = total + *g_p;

	if (total > 0 && **pp > 0) {
		total = total - a;
	} else if (total < 0 || **qq < 0) {
		total = total + b;
	} else {
		total = 0;
	}

	return 0;
}
