// <original>

#include <algorithm>
#include <vector>

struct Entry {
	int key;
	int *value;
	int **link;
};

struct EntryLess {
	bool operator()(const Entry *x, const Entry *y) const {
		if (x->key != y->key) {
			return x->key < y->key;
		}
		return *x->value < *y->value;
	}
};

int linkSum(std::vector<Entry *> *v, int **acc) {
	std::vector<Entry *>::iterator it;
	int s;
	s = 0;
	for (it = v->begin(); it != v->end(); ++it) {
		Entry *e;
		e = *it;
		if (e->link != 0) {
			s = s + **e->link;
		} else {
			s = s + *e->value;
		}
	}
	**acc = **acc + s;
	return s;
}

int stablePick(std::vector<Entry *> *v, int **first, int **last) {
	std::stable_sort(v->begin(), v->end(), EntryLess());
	**first = (*v)[0]->key;
	**last = (*v)[v->size() - 1]->key;
	return **first + **last;
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
	Entry e1;
	Entry e2;
	Entry e3;
	Entry *ep;
	std::vector<Entry *> v;
	std::vector<Entry *> *vp;
	int total;

	a = 3;
	b = 1;
	c = 2;
	pa = &a;
	pb = &b;
	pc = &c;
	pp = &pa;
	qq = &pb;

	e1.key = 2;
	e1.value = pa;
	e1.link = pp;
	e2.key = 1;
	e2.value = pb;
	e2.link = qq;
	e3.key = 2;
	e3.value = pc;
	e3.link = 0;

	v.push_back(&e1);
	v.push_back(&e2);
	v.push_back(&e3);
	vp = &v;
	ep = &e1;

	total = stablePick(vp, pp, qq);
	total = total + linkSum(vp, pp);

	*ep->value = *ep->value + 1;
	**ep->link = **ep->link + **qq;
	*pa = *pa + **pp;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - 1;
		} else {
			total = total + 1;
		}
	}

	return 0;
}
