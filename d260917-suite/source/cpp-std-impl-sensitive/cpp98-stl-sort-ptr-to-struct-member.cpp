// <original>

#include <algorithm>
#include <vector>

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

struct Node {
	int rank;
	int *payload;
	int **mirror;

	Node(int r, int *p, int **m) {
		rank = r;
		payload = p;
		mirror = m;
	}
};

struct RankLess {
	bool operator()(const Node *x, const Node *y) const {
		return x->rank < y->rank;
	}
};

struct RankGreater {
	bool operator()(const Node *x, const Node *y) const {
		if (x->rank != y->rank) {
			return x->rank > y->rank;
		}
		return *x->payload > *y->payload;
	}
};

int scan(std::vector<Node *> *v, int **acc) {
	std::vector<Node *>::iterator it;
	int s;
	s = 0;
	for (it = v->begin(); it != v->end(); ++it) {
		Node *n;
		n = *it;
		s = s + n->rank;
		if (n->mirror != 0) {
			s = s + **n->mirror;
		}
	}
	**acc = **acc + s;
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int *pa;
	int *pb;
	int *pc;
	int **pp;
	int **qq;
	std::vector<Node *> v;
	std::vector<Node *> *vp;
	Node n1(2, &a, &pa);
	Node n2(1, &b, &pb);
	Node n3(3, &c, &pc);
	int total;

	a = 10;
	b = 20;
	c = 30;
	pa = &a;
	pb = &b;
	pc = &c;
	pp = &pa;
	qq = &pb;

	v.push_back(&n1);
	v.push_back(&n2);
	v.push_back(&n3);
	vp = &v;

	std::sort(vp->begin(), vp->end(), RankLess());
	total = scan(vp, pp);
	std::sort(vp->begin(), vp->end(), RankGreater());
	total = total + (*vp)[0]->rank;

	n1.mirror = qq;
	*n1.payload = *n1.payload + 1;
	**n1.mirror = **n1.mirror + *pc;
	**pp = **pp + **qq;
	**g_dptr = **g_dptr + *pa;

	if (total > 0 && **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
