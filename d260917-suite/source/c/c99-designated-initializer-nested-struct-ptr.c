// <original>

int gx;
int gy;
int gz;
int *gp = &gx;
int **gpp = &gp;

struct Inner {
	int *p;
	int **pp;
	int arr[3];
};

struct Outer {
	struct Inner in;
	struct Inner *link;
	int *ptr;
	int **dptr;
};

struct Inner g_inner = {
	.p = &gy,
	.pp = &gp,
	.arr = { [0] = 1, [2] = 3 }
};

struct Outer g_outer = {
	.in = { .p = &gx, .pp = &gp, .arr = { [1] = 5 } },
	.link = &g_inner,
	.ptr = &gz,
	.dptr = &gp
};

struct Outer g_table[2] = {
	[0] = { .in = { .p = &gx, .arr = { [0] = 2 } }, .ptr = &gy },
	[1] = { .in = { .p = &gy, .pp = &gp }, .link = &g_inner, .ptr = &gx, .dptr = &gp }
};

int sum_inner(struct Inner *ip) {
	int s = 0;
	if (ip->p != 0) {
		s = s + *ip->p;
	}
	if (ip->pp != 0) {
		s = s + **ip->pp;
	}
	s = s + ip->arr[0] + ip->arr[2];
	return s;
}

int sum_outer(struct Outer *op) {
	int s = 0;
	s = s + sum_inner(&op->in);
	if (op->link != 0) {
		s = s + *op->link->p;
	}
	if (op->ptr != 0) {
		s = s + *op->ptr;
	}
	if (op->dptr != 0) {
		s = s + **op->dptr;
	}
	return s;
}

int **pick(int **a, int **b, int depth) {
	int **r;
	if (depth <= 0) {
		r = a;
	} else if (depth == 1) {
		r = b;
	} else {
		r = pick(a, b, depth - 1);
	}
	return r;
}

int scan(struct Outer *tab, int n, int **fallback) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		switch (i) {
		case 0:
			s = s + sum_outer(&tab[i]);
			break;
		case 1:
			s = s + **fallback;
			break;
		default:
			s = s + *tab[i].ptr;
			break;
		}
	}
	return s;
}

int main(void) {
	int a;
	int b;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	struct Outer local = {
		.in = { .p = &a, .pp = &p, .arr = { [1] = 7 } },
		.ptr = &b,
		.dptr = &q
	};
	struct Outer *op;

	a = 1;
	b = 2;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;
	op = &local;

	*pp = &b;
	*q = *q + 6;
	**qq = **qq + 1;
	*op->ptr = *op->ptr + 2;
	*op->in.p = *op->in.p + 3;

	r = *pp;
	*r = *r + 1;

	via = pick(pp, qq, 3);
	**via = **via + 4;

	total = sum_outer(&g_outer);
	total = total + sum_outer(&g_table[1]);
	total = total + scan(g_table, 2, pp);
	total = total + sum_inner(&g_inner);
	total = total + **via + *op->in.p + **gpp;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - a;
		} else {
			total = total + b;
		}
	} else {
		total = 0;
	}

	return 0;
}
