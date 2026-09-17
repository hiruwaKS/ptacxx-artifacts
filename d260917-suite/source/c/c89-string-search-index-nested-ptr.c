// <original>

#include <string.h>

char gtext[128] = "hello world hello";
char *gscan = gtext;
char **gscanp = &gscan;

int count_char(char **sp, int c) {
	char *s;
	int n;
	s = *sp;
	n = 0;
	while (*s != '\0') {
		if (*s == (char)c) {
			n = n + 1;
		}
		s = s + 1;
	}
	*sp = s;
	return n;
}

char *locate(char **hayp, char *needle, char **endp) {
	char *hit;
	char *next;
	hit = strstr(*hayp, needle);
	if (hit != 0) {
		next = hit + strlen(needle);
		*endp = next;
		return hit;
	}
	*endp = *hayp;
	return 0;
}

int walk_words(char *s, char **first, char **last) {
	char *p;
	char *tok;
	int n;
	n = 0;
	p = s;
	tok = 0;
	for (;;) {
		if (*p == ' ' || *p == '\0') {
			if (tok != 0) {
				n = n + 1;
				if (n == 1) {
					*first = tok;
				}
				*last = p;
				tok = 0;
			}
			if (*p == '\0') {
				break;
			}
		} else if (tok == 0) {
			tok = p;
		}
		p = p + 1;
	}
	return n;
}

int main() {
	char buf[128];
	char *p;
	char *q;
	char *r;
	char **pp;
	char **qq;
	int a;
	int b;
	int total;

	strcpy(buf, gtext);
	p = buf;
	q = gtext;
	pp = &p;
	qq = &q;

	a = count_char(pp, 'l');
	b = count_char(qq, 'o');

	r = locate(pp, "world", qq);
	if (r != 0) {
		*r = 'W';
	}
	total = walk_words(gtext, pp, qq);
	total = total + a + b + (int)strlen(gtext);

	if (total > 0 && *pp != 0) {
		if (strchr(*qq, 'e') != 0 || **gscanp == 'h') {
			total = total + 1;
		} else {
			total = total - 1;
		}
	} else {
		total = 0;
	}

	return 0;
}
