// <original>

int ga;
int gb;
int gc;

struct Node {
	int tag;
	union Slot {
		int *p;
		int **pp;
	} u;
};

int *gp = &ga;
int **gpp = &gp;

struct Node gnode = { 1, { &ga } };
struct Node garr[3] = { { 1, { &ga } }, { 2, { &gb } }, { 3, { &gc } } };

int *choose(int *x, int *y, int k) {
	int *r;
	if (k < 0) {
		r = x;
	} else if (k == 0) {
		r = y;
	} else {
		r = &gc;
	}
	return r;
}

int **choose2(int **x, int **y, int k) {
	int **r;
	if (k > 1) {
		r = x;
	} else if (k == 1) {
		r = y;
	} else {
		r = &gp;
	}
	return r;
}

int scan(struct Node *n, int **pp, int **qq, int m) {
	int i;
	int s = 0;
	for (i = 0; i < m; i = i + 1) {
		if (i == 0) {
			s = s + *n->u.p;
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
	struct Node n;
	struct Node *np;
	struct Node local = { 2, { &gb } };

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	n.tag = 1;
	n.u.p = &x;
	np = &n;

	*pp = &y;
	*q = 3;
	**qq = 4;
	*p = *p + **pp;
	*np->u.p = 5;

	r = choose(p, q, 0);
	*r = *r + 1;

	via = choose2(pp, qq, 1);
	**via = **via + 1;

	total = scan(np, pp, qq, 3);
	total = total + **via + *np->u.p + *local.u.p;

	if (total > 10) {
		total = total - x;
	} else if (total < 0) {
		total = total + y;
	} else {
		total = 0;
	}

	return 0;
}
