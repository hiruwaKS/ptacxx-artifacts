// <original>

int gbase;

struct Outer {
	int id;
	struct {
		int flag;
		union {
			int *p;
			int **pp;
		};
		struct {
			int lo;
			int hi;
		};
	};
};

int *gptr = &gbase;
struct Outer gouter = { 1, { 2, { &gbase }, { 3, 4 } } };
struct Outer gouters[2] = {
	{ 1, { 2, { &gbase }, { 3, 4 } } },
	{ 5, { 6, { &gbase }, { 7, 8 } } }
};

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

int scan(struct Outer *outs, int n, int **pp, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *outs[i].p;
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
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	struct Outer local;
	struct Outer other;
	struct Outer *op;
	struct Outer *oq;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	op = &local;
	oq = &other;
	local.id = 9;
	local.flag = 1;
	local.p = &x;
	local.lo = 5;
	local.hi = 6;

	other.id = 10;
	other.flag = 2;
	other.pp = &p;
	other.lo = 7;
	other.hi = 8;

	*pp = &y;
	*q = 6;
	**qq = **qq + 1;
	*op->p = 12;
	op->lo = op->lo + *op->p;
	oq->hi = oq->hi + **oq->pp;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = scan(gouters, 2, pp, qq);
	total = total + **via + *op->p + gouter.lo;

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
