// <original>

int gval;

struct Table {
	int **rows;
	int * const *view;
	const int **cview;
};

int add(int **pp, int v) {
	int i;
	for (i = 0; i < 2; i = i + 1) {
		if (pp[i] != 0) {
			*pp[i] = *pp[i] + v;
		}
	}
	return **pp;
}

int read_ro(const int **ccp) {
	const int *c = *ccp;
	if (c == 0) {
		return 0;
	}
	return *c;
}

int main() {
	int a[2];
	int b[2];
	int *p;
	int *q;
	int *slots[2];
	int **pp;
	int **qq;
	int * const *cpp;
	const int **ccp;
	int **rp;
	int **rcp;
	Table t;
	int total;
	int i;

	a[0] = 1;
	a[1] = 2;
	b[0] = 3;
	b[1] = 4;
	p = a;
	q = b;
	slots[0] = p;
	slots[1] = q;
	pp = slots;
	qq = &q;

	cpp = pp;
	ccp = const_cast<const int **>(pp);

	rp = const_cast<int **>(cpp);
	**rp = **rp + 10;

	rcp = const_cast<int **>(ccp);
	*rcp = q;
	**rcp = **rcp + 20;

	t.rows = pp;
	t.view = cpp;
	t.cview = ccp;

	total = add(rp, 1);
	total = total + add(rcp, 2);
	total = total + **t.rows + **t.view + **t.cview;

	for (i = 0; i < 2; i = i + 1) {
		switch (i) {
		case 0:
			total = total + a[i];
			break;
		case 1:
			total = total + b[i];
			break;
		default:
			break;
		}
	}

	total = total + read_ro(ccp) + **qq;

	if (total > 0) {
		total = total % 100;
	}

	gval = total;

	return 0;
}
