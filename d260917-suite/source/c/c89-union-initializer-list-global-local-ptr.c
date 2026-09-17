// <original>

int gx;
int gy;
int gz;

union Slot {
	int *p;
	int **pp;
	int value;
};

int *gp = &gx;
int **gpp = &gp;

union Slot gslot = { &gx };
union Slot gslots[2] = { { &gy }, { &gz } };

int *pick_ptr(int *a, int *b, int flag) {
	int *r;
	if (flag == 0) {
		r = a;
	} else if (flag == 1) {
		r = b;
	} else {
		r = &gz;
	}
	return r;
}

int **pick_pp(int **a, int **b, int flag) {
	int **r;
	if (flag > 0) {
		r = a;
	} else if (flag < 0) {
		r = b;
	} else {
		r = &gp;
	}
	return r;
}

int fold(int **pp, int **qq, int n) {
	int sum = 0;
	int i;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			sum = sum + **pp;
		} else if (i % 3 == 0) {
			sum = sum - **qq;
		} else {
			sum = sum + *(*pp);
		}
	}
	return sum;
}

int main() {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **rr;
	int **via;
	int total;
	union Slot slot;
	union Slot *sp;

	x = 1;
	y = 2;
	z = 3;

	p = &x;
	q = &y;
	r = &z;
	pp = &p;
	qq = &q;
	rr = &r;

	slot.p = &x;
	sp = &slot;

	*pp = &z;
	*q = 10;
	**qq = 20;
	*r = *q + **pp;
	*sp->p = 30;

	via = pick_pp(pp, qq, 1);
	**via = **via + 1;

	r = pick_ptr(p, q, 0);
	*r = *r + **rr;

	total = fold(pp, qq, 4);
	total = total + **via + *sp->p;

	if (total > 0) {
		total = total - x;
	} else if (total < 0) {
		total = total + y;
	} else {
		total = z;
	}

	return 0;
}
