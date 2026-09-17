// <original>

struct Empty {};

struct Packed {
	int first;
	[[no_unique_address]] Empty e1;
	int second;
	[[no_unique_address]] Empty e2;
	int *p;
};

struct Padded {
	int first;
	Empty e1;
	int second;
	Empty e2;
	int **pp;
};

int packed_probe(Packed *k, int **pp) {
	int r;
	r = k->first + k->second;
	if (pp != 0) {
		r = r + **pp;
	}
	if (k->p != 0) {
		r = r + *k->p;
	}
	return r;
}

int padded_probe(Padded *k, int **pp, int ***qq) {
	int r;
	r = k->first + k->second;
	if (k->pp != 0) {
		r = r + **k->pp;
	}
	if (pp != 0) {
		r = r + **pp;
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
	Packed pk;
	Padded pd;
	Packed *kp;
	Padded *dp;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	qqq = &qq;

	pk.first = 3;
	pk.second = 4;
	pk.p = &x;
	pd.first = 5;
	pd.second = 6;
	pd.pp = &q;

	kp = &pk;
	dp = &pd;

	*pp = &pk.first;
	*q = *kp->p + 1;
	**qq = **qq + 2;
	***qqq = ***qqq + 3;
	if (*dp->pp != 0) {
		**dp->pp = x;
	}

	total = packed_probe(kp, pp);
	total = total + padded_probe(dp, qq, qqq);

	if (total > 0) {
		total = total + *p;
	}
	if (total % 2 == 0) {
		total = total + y;
	} else {
		total = total - x;
	}

	return 0;
}
