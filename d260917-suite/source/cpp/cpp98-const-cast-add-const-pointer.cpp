// <original>

int gsum;

struct Holder {
	int *slot;
	int **link;
};

int sum_const(const int *cp) {
	int s;
	if (cp == 0) {
		s = 0;
	} else {
		s = *cp;
	}
	return s;
}

int sum_const2(const int **cpp) {
	const int *c;
	int s;
	c = *cpp;
	if (c == 0) {
		s = 0;
	} else {
		s = *c;
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
	const int *cp;
	const int **cpp;
	const int *arr[2];
	Holder h;
	int total;
	int i;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	cp = const_cast<const int *>(p);
	cpp = const_cast<const int **>(pp);

	arr[0] = cp;
	arr[1] = const_cast<const int *>(q);

	total = sum_const(cp);
	total = total + sum_const2(cpp);
	total = total + sum_const2(arr);

	h.slot = p;
	h.link = pp;
	total = total + *h.slot + **h.link + **qq;

	i = 0;
	while (total > 0 && i < 2) {
		total = total - 1;
		i = i + 1;
	}

	if (total < 0 || y > 0) {
		total = total + *cp;
	} else {
		total = total - *p;
	}

	gsum = total;

	return 0;
}
