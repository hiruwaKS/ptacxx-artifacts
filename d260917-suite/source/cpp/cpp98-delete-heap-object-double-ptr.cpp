// <original>

struct Holder {
	int **slot;
	int *direct;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

int **make_slot(int *init) {
	int **s;
	s = new int *;
	*s = init;
	return s;
}

int *make_int(int v) {
	int *p;
	p = new int;
	*p = v;
	return p;
}

void wire(Holder *h, int **s, int *d, int **out) {
	h->slot = s;
	h->direct = d;
	if (out != 0) {
		**out = **out + 1;
	}
	if (*s != 0) {
		**s = **s + 1;
	}
}

int collect(Holder **hs, int n, int **pp, int **qq) {
	int sum;
	int i;
	sum = 0;
	for (i = 0; i < n; i = i + 1) {
		if (hs[i] == 0) {
			continue;
		}
		if (i == 0) {
			sum = sum + **hs[i]->slot;
		} else if (i == 1) {
			sum = sum + *hs[i]->direct;
		} else {
			sum = sum + **pp + **qq;
		}
	}
	return sum;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **heap_slot;
	Holder *h0;
	Holder *h1;
	Holder **box;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	r = make_int(7);
	heap_slot = make_slot(r);
	h0 = new Holder;
	h1 = new Holder;
	box = new Holder *[2];
	box[0] = h0;
	box[1] = h1;

	*pp = &y;
	**pp = **pp + 1;
	*q = *q + 1;
	**qq = **qq + 2;

	wire(h0, heap_slot, p, pp);
	wire(h1, qq, q, qq);

	**heap_slot = **heap_slot + 3;

	total = collect(box, 2, pp, qq);
	total = total + **heap_slot + *r + **pp;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	delete r;
	delete heap_slot;
	delete h0;
	delete h1;
	delete [] box;

	return 0;
}
