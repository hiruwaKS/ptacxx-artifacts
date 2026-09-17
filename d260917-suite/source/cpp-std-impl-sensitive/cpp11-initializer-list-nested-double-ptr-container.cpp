// <original>

#include <vector>
#include <map>
#include <initializer_list>

int g_a;
int g_b;
int *g_pa = &g_a;
int *g_pb = &g_b;
int **g_pp = &g_pa;

struct Cell {
	int *slot;
	int **link;

	Cell(std::initializer_list<int *> init) {
		std::initializer_list<int *>::iterator it = init.begin();
		if (it != init.end()) {
			slot = *it;
		} else {
			slot = 0;
		}
		link = 0;
	}
};

int drain(std::vector<int **> *vp, std::map<int, int **> *mp) {
	std::vector<int **>::iterator it;
	std::map<int, int **>::iterator mit;
	int s = 0;
	for (it = vp->begin(); it != vp->end(); ++it) {
		if (*it != 0) {
			s = s + ***it;
		}
	}
	for (mit = mp->begin(); mit != mp->end(); ++mit) {
		s = s + **mit->second;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::vector<int **> refs = { &p, &q, g_pp };
	std::map<int, int **> table = { { 1, &p }, { 2, &q } };
	Cell c({ &x, &y });
	int total;

	x = 6;
	y = 8;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	c.link = pp;

	total = drain(&refs, &table);
	total = total + *c.slot + **c.link;
	total = total + **pp + **qq + *p + *q;
	total = total + **refs[0] + **refs[2];

	if (total > 0 && **pp > 0) {
		total = total - x;
	} else if (total < 0 || **qq < 0) {
		total = total + y;
	} else {
		total = 0;
	}

	return 0;
}
