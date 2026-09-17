// <original>

#include <set>
#include <map>
#include <vector>
#include <initializer_list>

int g_x;
int g_y;
int *g_px = &g_x;
int *g_py = &g_y;

static std::initializer_list<int *> g_gathered = { &g_x, &g_y, g_px };

std::initializer_list<int *> gather(int **pp, int **qq) {
	if (pp != 0 && qq != 0) {
		return g_gathered;
	}
	return std::initializer_list<int *>();
}

int tally(std::set<int *> *s, std::map<int, int **> *m) {
	std::set<int *>::iterator it;
	std::map<int, int **>::iterator mit;
	int total = 0;
	for (it = s->begin(); it != s->end(); ++it) {
		total = total + **it;
	}
	for (mit = m->begin(); mit != m->end(); ++mit) {
		if (mit->second != 0) {
			total = total + **mit->second;
		}
	}
	return total;
}

int main() {
	int a;
	int b;
	int *pa;
	int *pb;
	int **pp;
	int **qq;
	std::set<int *> s = { &a, &b, g_px };
	std::map<int, int **> m = { { 1, &pa }, { 2, &pb } };
	std::vector<int *> v;
	int total;

	a = 2;
	b = 3;
	pa = &a;
	pb = &b;
	pp = &pa;
	qq = &pb;

	v = { pa, pb, g_py };

	total = tally(&s, &m);
	total = total + *v[0] + *v[1] + *v[2];
	total = total + **pp + **qq + *g_px;

	std::initializer_list<int *> got = gather(pp, qq);
	std::initializer_list<int *>::iterator git;
	for (git = got.begin(); git != got.end(); ++git) {
		total = total + **git;
	}

	if (total > 0 && **pp > 0) {
		total = total - a;
	} else if (total < 0 || **qq < 0) {
		total = total + b;
	} else {
		total = 0;
	}

	return 0;
}
