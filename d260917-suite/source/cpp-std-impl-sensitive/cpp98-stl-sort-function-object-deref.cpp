// <original>

#include <algorithm>
#include <vector>

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

struct Cursor {
	int *pos;
	int **home;

	Cursor(int *p, int **h) {
		pos = p;
		home = h;
	}

	int read() {
		return *pos + **home;
	}
};

struct ByValue {
	int *bias;

	ByValue(int *b) {
		bias = b;
	}

	bool operator()(Cursor *x, Cursor *y) const {
		return x->read() + *bias < y->read() + *bias;
	}
};

int touch(std::vector<Cursor *> *v, int **acc) {
	std::vector<Cursor *>::iterator it;
	int s;
	s = 0;
	for (it = v->begin(); it != v->end(); ++it) {
		Cursor *cur;
		cur = *it;
		if (cur->home != 0) {
			s = s + cur->read();
		} else {
			s = s + **acc;
		}
	}
	**acc = **acc + s;
	return s;
}

int main() {
	int a;
	int b;
	int base;
	int *pa;
	int *pb;
	int *bias;
	int **pp;
	int **qq;
	std::vector<Cursor *> v;
	std::vector<Cursor *> *vp;
	Cursor c1(&a, &bias);
	Cursor c2(&b, &bias);
	Cursor *cp;
	int total;

	a = 7;
	b = 2;
	base = 1;
	pa = &a;
	pb = &b;
	bias = &base;
	pp = &pa;
	qq = &pb;

	v.push_back(&c1);
	v.push_back(&c2);
	vp = &v;
	cp = &c1;

	std::sort(vp->begin(), vp->end(), ByValue(bias));
	total = touch(vp, pp);
	total = total + (*vp)[0]->read();

	*cp->pos = *cp->pos + *bias;
	**cp->home = **cp->home + **qq;
	**pp = **pp + **qq;
	**g_dptr = **g_dptr + *pb;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - 1;
		} else {
			total = total + 1;
		}
	} else {
		total = 0;
	}

	return 0;
}
