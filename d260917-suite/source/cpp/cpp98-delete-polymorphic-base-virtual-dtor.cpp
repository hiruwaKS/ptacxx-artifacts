// <original>

struct Base {
	int *tag;
	virtual int weight();
	virtual ~Base();
};

struct Left : Base {
	int *extra;
	virtual int weight();
	virtual ~Left();
};

struct Right : Base {
	int *extra;
	virtual int weight();
	virtual ~Right();
};

int Base::weight() {
	return *tag;
}

Base::~Base() {
}

int Left::weight() {
	return *tag + *extra;
}

Left::~Left() {
}

int Right::weight() {
	return *tag + *extra;
}

Right::~Right() {
}

Base *make_base(int *tag) {
	Base *b;
	b = new Base;
	b->tag = tag;
	return b;
}

Base *make_left(int *tag, int *extra) {
	Left *l;
	l = new Left;
	l->tag = tag;
	l->extra = extra;
	return l;
}

Base *make_right(int *tag, int *extra) {
	Right *r;
	r = new Right;
	r->tag = tag;
	r->extra = extra;
	return r;
}

int gather(Base **items, int n, int **pp, int **qq) {
	int s;
	int i;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (items[i] == 0) {
			continue;
		}
		if (i == 0) {
			s = s + items[i]->weight();
		} else if (i == 1) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
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
	Base *b;
	Base *l;
	Base *r;
	Base **all;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	b = make_base(p);
	l = make_left(p, q);
	r = make_right(q, p);
	all = new Base *[3];
	all[0] = b;
	all[1] = l;
	all[2] = r;

	*pp = &y;
	**pp = **pp + 1;
	*q = *q + 1;
	**qq = **qq + 2;

	total = gather(all, 3, pp, qq);
	total = total + **pp + **qq;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	delete b;
	delete l;
	delete r;
	delete [] all;

	return 0;
}
