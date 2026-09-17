// <original>

int gbase;

union Box {
	int *p;
	int **pp;
};

int *gptr = &gbase;
union Box gbox = { &gbase };
union Box gboxes[2] = { { &gbase }, { &gbase } };

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

int walk(union Box *boxes, int n, int **pp, int **qq) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *boxes[i].p;
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
	union Box local = { &x };
	union Box *bp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	bp = &local;

	*pp = &y;
	*q = 6;
	**qq = **qq + 1;
	*bp->p = 12;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = walk(gboxes, 2, pp, qq);
	total = total + **via + *bp->p;

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
