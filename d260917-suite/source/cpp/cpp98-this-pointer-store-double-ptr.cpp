// <original>

struct Registry {
	int id;
	int *slot;
	int **dptr;
	Registry *next;
	Registry **link;

	Registry(int n) {
		id = n;
		slot = &id;
		dptr = &slot;
		next = 0;
		link = 0;
	}

	Registry *self() {
		return this;
	}

	void store(Registry **where) {
		if (where != 0) {
			*where = this;
		}
	}

	void chain_to(Registry **where) {
		link = where;
		if (link != 0) {
			*link = this;
		}
	}

	int probe(int **pp) {
		int r;
		r = id;
		if (pp != 0) {
			r = r + **pp;
		}
		if (dptr != 0) {
			r = r + **dptr;
		}
		return r;
	}
};

Registry *forward(Registry *r, Registry **slot) {
	Registry *cur;
	cur = r;
	if (slot != 0) {
		*slot = cur;
	}
	if (cur != 0) {
		cur = cur->self();
	}
	return cur;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Registry r1(5);
	Registry r2(7);
	Registry *rp;
	Registry *rq;
	Registry **rpp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	rp = 0;
	rq = 0;
	rpp = 0;

	r1.store(&rp);
	r2.chain_to(&rq);
	rpp = &rp;

	*pp = &r1.id;
	*q = **qq + r2.id;
	**pp = **pp + 1;
	*rpp = rq;

	if (r1.probe(pp) > 0) {
		r1.chain_to(rpp);
	}
	if (r2.probe(qq) > 0) {
		r2.store(&rq);
	}

	rp = forward(rp, &rq);
	if (rp != 0) {
		rp->store(&rq);
	}

	return 0;
}
