// <original>

#include <utility>
#include <vector>

struct Box {
	int *data;
	int **slot;

	Box() : data(0), slot(0) {}
	Box(int *d, int **s) : data(d), slot(s) {}

	Box(Box &&o) : data(o.data), slot(o.slot) {
		o.data = 0;
		o.slot = 0;
	}

	Box &operator=(Box &&o) {
		if (this != &o) {
			data = o.data;
			slot = o.slot;
			o.data = 0;
			o.slot = 0;
		}
		return *this;
	}
};

int sumBoxes(std::vector<Box> *v) {
	int i;
	int s = 0;
	for (i = 0; i < (int)v->size(); ++i) {
		Box &b = (*v)[i];
		if (b.data != 0) {
			s = s + *b.data;
		} else if (b.slot != 0) {
			s = s + **b.slot;
		} else {
			s = s - 1;
		}
	}
	return s;
}

void fill(std::vector<Box> *v, int *p, int **pp, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			v->push_back(Box(p, 0));
		} else {
			v->push_back(Box(0, pp));
		}
	}
}

int take(Box *b, int **pp) {
	Box local(std::move(*b));
	if (local.data != 0) {
		**pp = **pp + *local.data;
	} else {
		**pp = **pp - 1;
	}
	return **pp;
}

int main() {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	std::vector<Box> v;
	std::vector<Box> w;
	Box *bp;
	int total;

	x = 3;
	y = 4;
	z = 5;
	p = &x;
	q = &y;
	r = &z;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;
	*q = *q + *p;

	fill(&v, p, pp, 4);

	w = std::move(v);
	bp = &w[0];

	total = sumBoxes(&w);
	total = total + take(bp, qq);
	total = total + **pp + **qq + *r;

	if (total > 0 && **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
