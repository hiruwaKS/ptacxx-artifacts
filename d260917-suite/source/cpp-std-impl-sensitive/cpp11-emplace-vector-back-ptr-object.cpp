// <original>

#include <vector>

struct Node {
	int *p;
	int **pp;
	Node(int *a, int **b) : p(a), pp(b) {}
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

int scanNodes(std::vector<Node> *v, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < (int)v->size(); ++i) {
		Node *n = &(*v)[i];
		if (n->p != 0) {
			s = s + *n->p;
		} else if (n->pp != 0) {
			s = s + **n->pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int scanSlots(std::vector<int **> *slots, int **pp) {
	int i;
	int s = 0;
	for (i = 0; i < (int)slots->size(); ++i) {
		int **e = (*slots)[i];
		if (e != 0) {
			**e = **e + 1;
			s = s + **e;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

void grow(std::vector<Node> *v, std::vector<int **> *slots, int **pp, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		v->emplace_back(*pp, pp);
		slots->emplace_back(pp);
	}
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::vector<Node> v;
	std::vector<int **> slots;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	v.emplace_back(p, pp);
	v.emplace_back(q, qq);
	slots.emplace_back(pp);
	slots.emplace_back(qq);

	grow(&v, &slots, pp, 2);

	*pp = &y;
	**qq = **qq + 1;
	*g_ptr = *g_ptr + 2;
	**g_dptr = **g_dptr + 3;

	total = scanNodes(&v, qq);
	total = total + scanSlots(&slots, pp);

	if (total > 0 && **pp > 0) {
		total = total - *q;
	} else if (total < 0) {
		total = total + *p;
	} else {
		total = 0;
	}

	return 0;
}
