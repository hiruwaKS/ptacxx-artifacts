// <original>

int gtag;

struct Blob {
	char *bytes;
	unsigned char *ubytes;
	signed char *sbytes;
	int **owner;
	int size;

	Blob(char *b, int **o, int n) {
		bytes = b;
		ubytes = (unsigned char *)b;
		sbytes = (signed char *)b;
		owner = o;
		size = n;
	}

	char head() {
		return *bytes;
	}

	unsigned char uhead() {
		return *ubytes;
	}

	signed char shead() {
		return *sbytes;
	}

	int touch(int **pp) {
		if (owner != 0) {
			**owner = **owner + 1;
		}
		if (pp != 0) {
			**pp = **pp + 1;
		}
		return size;
	}
};

char *pick(char *a, char *b, int k) {
	char *r;
	if (k <= 0) {
		r = a;
	} else if (k == 1) {
		r = b;
	} else {
		r = pick(a, b, k - 2);
	}
	return r;
}

unsigned char **findu(unsigned char **a, unsigned char **b, int k) {
	unsigned char **r;
	if (k <= 0) {
		r = a;
	} else {
		r = findu(b, a, k - 1);
	}
	return r;
}

int mix(char *cp, unsigned char **up, signed char **sp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + *cp;
		} else if (i == 1) {
			s = s + (int)**up;
		} else {
			s = s + (int)**sp;
		}
	}
	return s;
}

int main() {
	int x;
	int y;
	char a;
	char b;
	char *p;
	char *q;
	unsigned char *u;
	unsigned char **up;
	signed char **sp;
	unsigned char **via;
	int *ip;
	int **ipp;
	int total;
	Blob *bl;
	Blob **bp;

	a = 'A';
	b = 'B';
	x = 3;
	y = 4;
	p = &a;
	q = &b;
	u = (unsigned char *)p;
	up = &u;
	sp = (signed char **)&p;
	ip = &x;
	ipp = &ip;

	bl = new Blob(p, ipp, 2);
	bp = &bl;

	*p = 'C';
	*u = (unsigned char)(*u + 1);
	**up = (unsigned char)(**up + 1);
	*ip = *ip + 1;
	**ipp = **ipp + 1;

	total = (int)bl->head() + (int)bl->uhead() + (int)bl->shead();
	total = total + bl->touch(ipp);
	total = total + (*bp)->touch(ipp);

	q = pick(p, q, 3);
	*q = (char)(*q + 1);

	via = findu(up, (unsigned char **)&q, 2);
	**via = (unsigned char)(**via + 1);

	total = total + mix(q, up, sp, 3);
	total = total + (int)(**up) + (int)(**sp) + **ipp + y;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - (int)a;
		} else {
			total = total + (int)b;
		}
	} else {
		total = 0;
	}

	delete *bp;

	return 0;
}
