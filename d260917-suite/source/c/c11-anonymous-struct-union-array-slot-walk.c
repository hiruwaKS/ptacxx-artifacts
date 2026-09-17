// <original>

int gbase;

struct Slot {
	int kind;
	union {
		int *p;
		int **pp;
		int value;
	};
	struct {
		int lo;
		int hi;
	};
};

int *gptr = &gbase;
struct Slot gslot = { 1, { &gbase }, { 2, 3 } };
struct Slot gslots[3] = {
	{ 1, { &gbase }, { 2, 3 } },
	{ 2, { &gbase }, { 4, 5 } },
	{ 3, { &gbase }, { 6, 7 } }
};

int *pick(int *a, int *b, int depth) {
	int *r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = pick(a, b, depth - 1);
	}
	return r;
}

int **pick2(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else {
		r = pick2(b, a, depth - 1);
	}
	return r;
}

int collect(struct Slot *slots, int n, int **pp, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		switch (slots[i].kind) {
		case 1:
			s = s + *slots[i].p;
			break;
		case 2:
			s = s + **pp;
			break;
		default:
			s = s + **qq + slots[i].lo;
			break;
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
	struct Slot local;
	struct Slot other;
	struct Slot *sp;
	struct Slot *sq;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	sp = &local;
	sq = &other;
	local.kind = 1;
	local.p = &x;
	local.lo = 3;
	local.hi = 4;

	other.kind = 2;
	other.pp = &p;
	other.lo = 5;
	other.hi = 6;

	*pp = &y;
	*q = 6;
	**qq = **qq + 1;
	*sp->p = 12;
	sp->lo = sp->lo + *sp->p;
	sq->hi = sq->hi + **sq->pp;

	r = pick(p, q, 3);
	*r = *r + 1;

	via = pick2(pp, qq, 2);
	**via = **via + 3;

	total = collect(gslots, 3, pp, qq);
	total = total + **via + *sp->p + gslot.lo;

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
