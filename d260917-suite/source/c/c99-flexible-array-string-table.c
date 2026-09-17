// <original>

#include <stdlib.h>

struct Str {
	int len;
	char *tag;
	char text[];
};

struct Str *make_str(char *tag, int n) {
	struct Str *s;
	int i;
	s = (struct Str *)malloc(sizeof(struct Str) + (n + 1) * sizeof(char));
	s->len = n;
	s->tag = tag;
	for (i = 0; i < n; i = i + 1) {
		s->text[i] = (char)('a' + (i % 26));
	}
	s->text[n] = 0;
	return s;
}

int len_via(struct Str **pp) {
	return (*pp)->len;
}

char *tag_via(struct Str *s, struct Str **pp, char **tp) {
	if (s->tag != 0) {
		return s->tag;
	} else if ((*pp)->tag != 0) {
		return (*pp)->tag;
	} else {
		return *tp;
	}
}

int score(struct Str *s, char **cp, int **np, int n) {
	int i;
	int total;
	total = 0;
	for (i = 0; i < n && i < s->len; i = i + 1) {
		if (s->text[i] == *s->tag) {
			total = total + **np;
		} else {
			total = total + *(*cp);
		}
	}
	return total;
}

int main() {
	char a;
	char b;
	char *cp;
	char *cp2;
	char **cpp;
	char **cpp2;
	char **via;
	int *np;
	int **npp;
	struct Str *s;
	struct Str *t;
	struct Str **sp;
	int total;

	a = 'a';
	b = 'b';
	cp = &a;
	cp2 = &b;
	cpp = &cp;
	cpp2 = &cp2;
	np = (int *)malloc(sizeof(int));
	*np = 3;
	npp = &np;

	s = make_str(cp, 5);
	t = make_str(cp2, 4);
	sp = &t;

	*cpp = &b;
	**cpp2 = 'c';
	**npp = **npp + 2;
	s->tag = cp;
	(*sp)->text[0] = *cp;

	via = cpp;
	*via = &a;

	total = score(s, cpp, npp, 4);
	total = total + len_via(sp) + **npp;
	total = total + *tag_via(s, sp, cpp);

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - a;
		} else {
			total = total + b;
		}
	} else {
		total = 0;
	}

	free(np);
	free(s);
	free(t);
	return 0;
}
