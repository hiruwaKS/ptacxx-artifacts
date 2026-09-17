// <original>

struct Empty {};

struct EmptyBase : Empty {
	int value;
	int *slot;
};

int probe(EmptyBase *e, int **pp) {
	int r;
	r = e->value;
	if (pp != 0) {
		r = r + **pp;
	}
	if (e->slot != 0) {
		r = r + *e->slot;
	}
	return r;
}

int relay(EmptyBase *e, int **pp, int ***qq) {
	int r;
	r = 0;
	if (e != 0) {
		r = r + probe(e, pp);
	}
	if (qq != 0 && *qq != 0) {
		r = r + ***qq;
	}
	return r;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int ***qqq;
	int total;
	Empty e;
	EmptyBase obj;
	Empty *ep;
	EmptyBase *bp;
	EmptyBase *bp2;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	qqq = &qq;

	obj.value = 10;
	obj.slot = &y;

	ep = &obj;
	bp = &obj;
	bp2 = &obj;
	if (ep == &e) {
		obj.value = obj.value + 1;
	}

	*pp = &obj.value;
	*q = *bp->slot + 1;
	**qq = **qq + 1;
	***qqq = ***qqq + 2;
	*bp->slot = x + y;

	total = probe(bp, pp);
	total = total + relay(bp2, qq, qqq);
	if (ep == bp) {
		total = total + 1;
	}

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
