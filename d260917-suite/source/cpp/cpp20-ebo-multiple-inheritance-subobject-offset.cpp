// <original>

struct Left {
	int lv;
	int *lp;
};

struct Right {
	int rv;
	int **rpp;
};

struct Both : Left, Right {
	int bv;
};

int scan_left(Left *p, int **pp) {
	int r;
	r = p->lv;
	if (pp != 0) {
		r = r + **pp;
	}
	if (p->lp != 0) {
		r = r + *p->lp;
	}
	return r;
}

int scan_right(Right *p, int **pp) {
	int r;
	r = p->rv;
	if (p->rpp != 0) {
		r = r + **p->rpp;
	}
	if (pp != 0) {
		r = r + **pp;
	}
	return r;
}

int scan_both(Both *p, int **pp, int ***qq) {
	int r;
	Left *l;
	Right *rt;
	l = p;
	rt = p;
	r = scan_left(l, pp);
	r = r + scan_right(rt, *qq);
	r = r + p->bv;
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
	Both obj;
	Left *lp;
	Right *rp;
	Both *bp;

	x = 5;
	y = 6;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	qqq = &qq;

	obj.lv = 1;
	obj.lp = &x;
	obj.rv = 2;
	obj.rpp = &q;
	obj.bv = 3;

	lp = &obj;
	rp = &obj;
	bp = &obj;

	*pp = &obj.lv;
	*q = *lp->lp + 1;
	**qq = **qq + 2;
	***qqq = ***qqq + 1;
	*bp->lp = obj.rv;

	total = scan_both(bp, pp, qqq);
	total = total + scan_left(lp, qq);
	total = total + scan_right(rp, pp);

	if (total > 0) {
		total = total - 1;
	} else if (total == 0) {
		total = 7;
	} else {
		total = 0;
	}

	return 0;
}
