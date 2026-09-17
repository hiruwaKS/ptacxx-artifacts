// <original>

#include <string.h>

char gbuf[128];
char gtail[64] = "tail";
char *gcur = gbuf;
char **gcurp = &gcur;

int append_all(char **dstp, char *parts[], int n) {
	char *d;
	int i;
	int total;
	d = *dstp;
	total = 0;
	for (i = 0; i < n; i = i + 1) {
		if (parts[i] != 0) {
			strcat(d, parts[i]);
			total = total + (int)strlen(parts[i]);
		} else if (i == 0) {
			strcpy(d, "");
		} else {
			strcat(d, gtail);
		}
	}
	*dstp = d;
	return total;
}

char *find_join(char *hay, char *needle, char **out) {
	char *hit;
	hit = strstr(hay, needle);
	if (hit != 0) {
		*out = hit;
	} else {
		*out = hay;
	}
	return *out;
}

int scan_copy(char **srcp, char **dstp, int n) {
	int count;
	int i;
	char *s;
	char *d;
	count = 0;
	s = *srcp;
	d = *dstp;
	for (i = 0; i < n; i = i + 1) {
		if (strchr(s, 'z') != 0) {
			count = count + 1;
			strcpy(d, s);
		} else if (strlen(s) > 0) {
			strcat(d, s);
			count = count + 2;
		} else {
			count = count - 1;
		}
		s = d;
	}
	*srcp = s;
	*dstp = d;
	return count;
}

int main() {
	char local[128];
	char tmp[64];
	char *parts[3];
	char *p;
	char *q;
	char **pp;
	char **qq;
	int r;
	int total;

	parts[0] = "ab";
	parts[1] = "cd";
	parts[2] = "az";

	strcpy(local, "x");
	p = local;
	q = tmp;
	pp = &p;
	qq = &q;

	strcpy(q, "qq");
	*pp = gbuf;
	strcpy(*pp, "start-");

	total = append_all(pp, parts, 3);
	total = total + scan_copy(pp, qq, 2);
	r = (int)strlen(*pp);
	total = total + r + (int)strlen(*qq);

	p = find_join(gbuf, "cd", qq);
	*q = 'C';
	if (total > 0) {
		if (strchr(*pp, 'x') != 0) {
			total = total + 1;
		} else {
			total = total - 1;
		}
	} else {
		total = 0;
	}
	**gcurp = 'G';
	return 0;
}
