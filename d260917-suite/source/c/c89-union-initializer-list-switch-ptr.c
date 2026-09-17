// <original>

int gs[3];

union Word {
	int *p;
	int **pp;
};

int *gwp = &gs[0];
union Word gword = { &gs[0] };

int *route(int *a, int *b, int sel) {
	int *r;
	switch (sel) {
	case 0:
		r = a;
		break;
	case 1:
		r = b;
		break;
	default:
		r = &gs[2];
		break;
	}
	return r;
}

int **route2(int **a, int **b, int sel) {
	int **r;
	if (sel == 0) {
		r = a;
	} else if (sel == 1) {
		r = b;
	} else {
		r = &gwp;
	}
	return r;
}

int mix(union Word *w, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i < 1) {
			s = s + *w->p;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	int **via;
	int total;
	union Word local = { &a };
	union Word *wp;

	a = 1;
	b = 2;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;

	wp = &local;

	*pp = &b;
	*q = 9;
	**qq = **qq + 1;
	*wp->p = 11;

	r = route(p, q, 1);
	*r = *r + 1;

	via = route2(pp, qq, 1);
	**via = **via + 2;

	total = mix(wp, pp, 3);
	total = total + **via + *wp->p;

	switch (total % 3) {
	case 0:
		total = total + a;
		break;
	case 1:
		total = total - b;
		break;
	default:
		total = total * 2;
		break;
	}

	return 0;
}
