// <original>

int gbase;

struct Node {
	int val;
	int *link;
};

int *gptr = &gbase;

int read_node(struct Node *n) {
	int s;
	s = n->val + *gptr;
	if (n->link != 0) {
		s = s + *n->link;
	}
	return s;
}

int read_node2(struct Node **nn) {
	int s;
	s = (*nn)->val;
	if ((*nn)->link != 0) {
		s = s + *(*nn)->link;
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
	struct Node *np;
	struct Node **npp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	np = &(struct Node){ 5, &x };
	npp = &np;

	*pp = &(int){ 7 };
	*q = *np->link + 1;
	**pp = **pp + 1;
	**qq = **qq + 2;
	(*npp)->val = (*npp)->val + 1;

	r = find(p, q, 3);
	*r = *r + 1;

	via = find2(pp, qq, 2);
	**via = **via + 3;

	total = read_node(np) + read_node2(npp) + **via + *r;

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
