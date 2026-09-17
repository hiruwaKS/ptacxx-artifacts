// <original>

int gbase;

struct Inner {
	int a;
	int b;
};

struct Outer {
	struct Inner in;
	int c;
};

int *gptr = &gbase;

int read_outer(struct Outer *o) {
	return o->in.a + o->in.b + o->c + *gptr;
}

int read_inner(struct Inner **ii) {
	return (*ii)->a + (*ii)->b;
}

int *find(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = find(a, b, depth - 1);
	}
	return r;
}

int **find2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = find2(b, a, depth - 1);
	}
	return r;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	struct Outer *op;
	struct Outer **opp;
	struct Inner *ip;
	struct Inner **ipp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	op = &(struct Outer){ { 3, 4 }, 5 };
	opp = &op;
	ip = &op->in;
	ipp = &ip;

	*p = op->in.a;
	*q = ip->b;
	**pp = **pp + 1;
	**qq = **qq + 2;
	(*opp)->c = (*opp)->c + (*ipp)->a;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = read_outer(op) + read_inner(ipp) + **via + *r;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	return 0;
}
