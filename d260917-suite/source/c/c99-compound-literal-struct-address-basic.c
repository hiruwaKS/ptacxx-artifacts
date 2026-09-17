// <original>

int gbase;

struct Point {
	int x;
	int y;
};

int *gptr = &gbase;

int add_point(struct Point *a, struct Point *b) {
	int s;
	s = a->x + a->y + b->x + b->y + *gptr;
	return s;
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

int walk(struct Point *pts, int n, int **pp, int **qq) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + pts[i].x;
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
	struct Point *sp;
	struct Point *sq;
	struct Point pts[2];

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	sp = &(struct Point){ 3, 4 };
	sq = &(struct Point){ 5, 6 };

	pts[0] = *sp;
	pts[1] = *sq;

	*p = sp->x;
	*q = sq->y;
	**pp = **pp + 1;
	**qq = **qq + 2;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = walk(pts, 2, pp, qq);
	total = total + add_point(sp, sq) + **via + *r;

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
