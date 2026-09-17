// <original>

struct Empty {};

struct Holder {
	int tag;
	[[no_unique_address]] Empty e;
	int *slot;
	int **dptr;
};

int read_holder(Holder *h, int **pp) {
	int r;
	r = h->tag;
	if (h->slot != 0) {
		r = r + *h->slot;
	}
	if (h->dptr != 0) {
		r = r + **h->dptr;
	}
	if (pp != 0) {
		r = r + **pp;
	}
	return r;
}

int share_holder(Holder *a, Holder *b, int **pp, int ***qq) {
	int r;
	r = 0;
	if (a != 0) {
		r = r + read_holder(a, pp);
	}
	if (b != 0 && a != b) {
		r = r + b->tag;
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
	Holder h1;
	Holder h2;
	Holder *hp;
	Holder *hq;
	Empty *ep;

	x = 7;
	y = 8;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	qqq = &qq;

	h1.tag = 11;
	h1.slot = &x;
	h1.dptr = &q;
	h2.tag = 22;
	h2.slot = &y;
	h2.dptr = &p;

	hp = &h1;
	hq = &h2;
	ep = &h1.e;

	*pp = &h1.tag;
	*q = *hp->slot + 1;
	**qq = **qq + 2;
	***qqq = ***qqq + 3;
	*hq->slot = h1.tag;

	total = read_holder(hp, pp);
	total = total + share_holder(hp, hq, qq, qqq);
	if (static_cast<void *>(ep) == static_cast<void *>(hp)) {
		total = total + 1;
	}

	if (total > 0) {
		total = total + *p;
	}
	if (total % 2 == 0) {
		total = total - x;
	} else {
		total = total + y;
	}

	return 0;
}
