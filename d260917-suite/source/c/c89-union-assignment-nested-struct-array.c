// <original>

int gbase;

struct Pair {
	int a;
	int b;
};

union Val {
	int i;
	int arr[3];
	struct Pair pair;
};

int *gptr = &gbase;
union Val gv = { 7 };
union Val gvals[2] = { { 1 }, { 2 } };

void copy_val(union Val *dst, union Val *src) {
	*dst = *src;
}

int read_val(union Val *v) {
	int s;
	s = 0;
	switch (gbase % 3) {
	case 0:
		s = v->i;
		break;
	case 1:
		s = v->arr[1];
		break;
	default:
		s = v->pair.a + v->pair.b;
		break;
	}
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

int combine(union Val *v, int **pp, int **qq, int n) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *v->arr;
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
	union Val local;
	union Val other;
	union Val *vp;
	union Val *vq;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	gbase = 1;
	gv.i = 5;
	gv.pair.a = 6;
	gv.pair.b = 7;
	gv.arr[0] = 8;
	gv.arr[1] = 9;
	gv.arr[2] = 10;

	local = gv;
	other.i = 11;
	local = other;
	vp = &local;
	vq = &other;

	*pp = &y;
	*q = *q + 1;
	**qq = **qq + 2;
	*vp->arr = *vq->arr + 1;
	vp->pair.a = vq->pair.a + *gptr;

	copy_val(vp, vq);
	copy_val(&local, &gvals[0]);
	*vp = *vq;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = combine(vp, pp, qq, 3);
	total = total + read_val(&local) + *vp->arr;

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
