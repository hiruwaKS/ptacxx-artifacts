// <original>

int gstate;

struct Item {
	int *v;
	int **r;

	Item(int *a, int **b) {
		v = a;
		r = b;
	}

	virtual ~Item() {}

	int get() {
		return *v + **r;
	}
};

struct Pair : Item {
	int *w;
	int **s;

	Pair(int *a, int **b, int *c, int **d) : Item(a, b) {
		w = c;
		s = d;
	}

	int both() {
		return *w + **s;
	}
};

int pick(Item **slot, Pair **pslot, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*slot)->get();
		} else if (i == 1) {
			s = s + (*pslot)->both();
		} else if (i == 2) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int d;
	int *p1;
	int *p2;
	int *p3;
	int *p4;
	int **q1;
	int **q2;
	int **q3;
	int **q4;
	Item *it;
	Pair *pr;
	Item **slots;
	Pair **pslots;
	void *raw;
	int total;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	p1 = &a;
	p2 = &b;
	p3 = &c;
	p4 = &d;
	q1 = &p1;
	q2 = &p2;
	q3 = &p3;
	q4 = &p4;

	pr = new Pair(p1, q1, p2, q2);
	it = static_cast<Item *>(pr);
	slots = &it;
	pslots = &pr;

	raw = static_cast<void *>(static_cast<Item *>(pr));
	Item *fromvoid = static_cast<Item *>(raw);
	total = fromvoid->get();

	total = total + pick(slots, pslots, q3, q4, 4);

	Pair *down = static_cast<Pair *>(static_cast<Item *>(pr));
	*down->w = *down->w + 5;
	**down->s = **down->s + 6;
	total = total + down->both();

	Item *up = static_cast<Item *>(*pslots);
	total = total + *up->v + **up->r;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - a;
		} else {
			total = total + b;
		}
	} else {
		total = 0;
	}

	gstate = total;

	delete pr;

	return 0;
}
