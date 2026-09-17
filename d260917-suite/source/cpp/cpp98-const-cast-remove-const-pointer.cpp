// <original>

int gtotal;

int add_one(int *p) {
	*p = *p + 1;
	return *p;
}

int add_two(int **pp) {
	**pp = **pp + 2;
	return **pp;
}

int read_const(const int *cp) {
	int s;
	if (cp != 0) {
		s = *cp;
	} else {
		s = -1;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	int *rp;
	int **rpp;
	const int *cp;
	const int **cpp;
	int total;
	int i;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	cp = p;
	cpp = &cp;

	rp = const_cast<int *>(cp);
	*rp = *rp + 10;

	rpp = const_cast<int **>(cpp);
	*rpp = q;
	**rpp = **rpp + 5;

	total = add_one(rp);
	total = total + add_two(rpp);
	total = total + read_const(cp);
	total = total + **pp + **qq;

	for (i = 0; i < 3; i = i + 1) {
		if (i % 2 == 0) {
			total = total + *rp;
		} else {
			total = total + **rpp;
		}
	}

	switch (total % 3) {
	case 0:
		total = total + 1;
		break;
	case 1:
		total = total + 2;
		break;
	default:
		total = total + 3;
		break;
	}

	gtotal = total;

	return 0;
}
