// <original>

#include <stdlib.h>
#include <string.h>

char gbuf[64];

int cmp_str(const void *a, const void *b) {
	const char *sa;
	const char *sb;
	sa = *(const char *const *)a;
	sb = *(const char *const *)b;
	return strcmp(sa, sb);
}

int cmp_str_len(const void *a, const void *b) {
	const char *sa;
	const char *sb;
	int la;
	int lb;
	sa = *(const char *const *)a;
	sb = *(const char *const *)b;
	la = (int)strlen(sa);
	lb = (int)strlen(sb);
	if (la < lb) {
		return -1;
	} else if (la > lb) {
		return 1;
	} else {
		return 0;
	}
}

int total_len(char **v, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		s = s + (int)strlen(*v);
		v = v + 1;
	}
	return s;
}

void copy_words(char **dst, char **src, int n) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		dst[i] = src[i];
	}
}

int main(void) {
	char *words[5];
	char *saved[5];
	char **wp;
	char **wq;
	char *cur;
	char *end;
	char **pp;
	char **qq;
	int total;
	int i;

	words[0] = "pear";
	words[1] = "apple";
	words[2] = "fig";
	words[3] = "banana";
	words[4] = "date";
	copy_words(saved, words, 5);

	wp = words;
	wq = saved;
	cur = *wp;
	end = *(wq + 4);
	pp = &cur;
	qq = &end;

	total = total_len(wp, 5);
	qsort(words, 5, sizeof(char *), cmp_str);
	total = total + (int)strlen(*wp);
	qsort(words, 5, sizeof(char *), cmp_str_len);
	total = total + (int)strlen(*pp);

	strcpy(gbuf, *wp);
	total = total + (int)strlen(gbuf);

	for (i = 0; i < 5; i = i + 1) {
		if (strcmp(words[i], saved[i]) != 0) {
			total = total + 1;
		} else if (total > 0 && *qq != 0) {
			total = total - 1;
		} else {
			total = total + 0;
		}
	}
	return 0;
}
