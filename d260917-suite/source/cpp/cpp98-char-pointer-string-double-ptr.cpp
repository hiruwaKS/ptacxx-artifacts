// <original>

int glen;

int slen(const char *s) {
	int n = 0;
	while (*s != 0) {
		n = n + 1;
		s = s + 1;
	}
	return n;
}

char *findchar(char *s, char c) {
	while (*s != 0) {
		if (*s == c) {
			return s;
		}
		s = s + 1;
	}
	return 0;
}

char **findptr(char **a, char **b, int k) {
	char **r;
	if (k <= 0) {
		r = a;
	} else if (k == 1) {
		r = b;
	} else {
		r = findptr(a, b, k - 2);
	}
	return r;
}

struct Name {
	char *text;
	char **alias;
	unsigned char *raw;
	int len;

	Name(char *t, char **a) {
		text = t;
		alias = a;
		raw = (unsigned char *)t;
		len = slen(t);
	}

	char at(int i) {
		return *(text + i);
	}

	int size() {
		return len;
	}
};

int walk(Name **names, char **pp, unsigned char **up, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*names)->size();
		} else if (i == 1) {
			s = s + (int)**pp;
		} else {
			s = s + (int)**up;
		}
	}
	return s;
}

int main() {
	char buf[8] = { 'h', 'e', 'l', 'l', 'o', 0, 0, 0 };
	char alt[8] = { 'w', 'o', 'r', 'l', 'd', 0, 0, 0 };
	char *p;
	char *q;
	char **pp;
	char **qq;
	char **via;
	char *hit;
	unsigned char *u;
	unsigned char **up;
	Name *nm;
	Name **names;
	int total;

	p = buf;
	q = alt;
	pp = &p;
	qq = &q;
	u = (unsigned char *)buf;
	up = &u;

	nm = new Name(p, pp);
	names = &nm;

	*p = 'H';
	*q = 'W';
	**pp = 'J';
	**qq = 'K';
	**up = (unsigned char)(**up + 1);

	hit = findchar(p, 'l');
	if (hit != 0) {
		*hit = 'L';
	}

	via = findptr(pp, qq, 2);
	**via = 'M';

	total = walk(names, pp, up, 3);
	total = total + (int)(*names)->at(1) + (int)(**up) + (int)(**pp);

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - slen(p);
		} else {
			total = total + slen(q);
		}
	} else {
		total = 0;
	}

	delete *names;

	return 0;
}
