// <original>

int gbase;

struct Rec {
	int tag;
	union {
		int *p;
		int **pp;
	};
	struct {
		int a;
		int b;
	};
};

int *gptr = &gbase;
struct Rec grec = { 1, { &gbase }, { 2, 3 } };
struct Rec grecs[2] = {
	{ 1, { &gbase }, { 2, 3 } },
	{ 4, { &gbase }, { 5, 6 } }
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

int walk(struct Rec *recs, int n, int **pp, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *recs[i].p;
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
	struct Rec local;
	struct Rec other;
	struct Rec *rp;
	struct Rec *rq;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	rp = &local;
	rq = &other;
	local.tag = 5;
	local.p = &x;
	local.a = 7;
	local.b = 8;

	other.tag = 6;
	other.pp = &p;
	other.a = 9;
	other.b = 10;

	*pp = &y;
	*q = 6;
	**qq = **qq + 1;
	*rp->p = 12;
	rp->a = rp->a + *rp->p;
	rq->b = rq->b + **rq->pp;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = walk(grecs, 2, pp, qq);
	total = total + **via + *rp->p + grec.a;

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
