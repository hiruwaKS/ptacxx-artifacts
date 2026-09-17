// <original>

struct Acc {
	int total;
	int *slot;
	int **dptr;
	int weight;

	Acc(int w) {
		total = 0;
		weight = w;
		slot = &total;
		dptr = &slot;
	}

	void add(int v) {
		total = total + v;
	}

	int value() {
		return total;
	}
};

int apply(Acc *self, int n) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		self->add(i * self->weight);
	}
	return self->value();
}

int combine(Acc *a, Acc *b) {
	int r;
	r = a->value() + b->value();
	if (a->total > b->total) {
		r = r + *a->slot;
	} else {
		r = r + **b->dptr;
	}
	return r;
}

int relay(Acc *self, Acc **out) {
	if (out != 0) {
		*out = self;
	}
	return self->value();
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Acc a(2);
	Acc b(3);
	Acc *pa;
	Acc *pb;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	pa = &a;
	pb = &b;

	apply(pa, 3);
	apply(pb, 2);

	relay(pa, &pb);
	relay(pb, &pa);

	*pp = &a.total;
	*q = **qq + a.total;
	**pp = **pp + 1;

	if (combine(pa, pb) > 0) {
		pa->add(1);
	}

	return 0;
}
