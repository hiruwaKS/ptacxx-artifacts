// <original>

int gbase;

struct Pair {
	int a;
	int b;
};

int *gptr = &gbase;

int sum_array(int *arr, int n) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + arr[i];
	}
	return s;
}

int sum_pair(struct Pair *sp) {
	return sp->a + sp->b + *gptr;
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
	int *arrp;
	struct Pair *pr;

	x = 1;
	y = 2;
	pp = &p;
	qq = &q;

	p = (int[]){ 3, 4, 5 };
	q = &(int){ 6 };

	arrp = (int[]){ 7, 8, 9 };
	pr = &(struct Pair){ 10, 11 };

	*p = *p + 1;
	*q = *q + 2;
	*pp = arrp;
	**pp = **pp + 1;
	**qq = **qq + 2;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = sum_array(arrp, 3) + sum_pair(pr) + sum_array(p, 3);
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
