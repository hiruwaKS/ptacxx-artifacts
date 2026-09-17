// <original>

int gbase;

struct Box {
	int *p;
	int v;
};

int *gptr = &gbase;

int apply(int *a, int **b, int n) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			s = s + *a;
		} else {
			s = s + **b;
		}
	}
	return s;
}

int take_box(struct Box *b) {
	return *b->p + b->v + *gptr;
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
	struct Box *bp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;

	pp = &(int*){ p };
	qq = &(int*){ q };
	via = pp;

	bp = &(struct Box){ &x, 4 };

	*p = *p + 1;
	*q = *q + 2;
	**pp = **pp + 1;
	**qq = **qq + 2;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = apply(&(int){ 9 }, pp, 3) + apply(p, qq, 2) + take_box(bp);
	total = total + **via + *r;

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
