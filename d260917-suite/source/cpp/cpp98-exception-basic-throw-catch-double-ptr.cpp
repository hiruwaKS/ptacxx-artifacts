// <original>

#include <cstdio>

struct Box {
	int *p;
	int **pp;
};

int g_a;
int g_b;

int *g_p = &g_a;
int **g_pp = &g_p;

int checked_div(int *num, int *den, int **out) {
	if (den == 0 || *den == 0) {
		throw "division by zero";
	}
	if (*num < 0) {
		throw -1;
	}
	**out = *num / *den;
	return **out;
}

int accumulate(Box *boxes, int n, int **total) {
	int i;
	int s;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (boxes[i].p == 0) {
			continue;
		}
		s = s + *boxes[i].p;
		if (boxes[i].pp != 0) {
			s = s + **boxes[i].pp;
		}
	}
	**total = **total + s;
	return s;
}

int run(Box *boxes, int n, int **total) {
	int rc;
	rc = 0;
	try {
		accumulate(boxes, n, total);
		checked_div(boxes[0].p, boxes[1].p, total);
	} catch (const char *msg) {
		rc = 1;
	} catch (int code) {
		rc = code;
	} catch (...) {
		rc = 9;
	}
	return rc;
}

int main() {
	int x;
	int y;
	int z;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Box boxes[2];
	Box *bp;
	int total;
	int *pt;
	int **ppt;
	int rc;

	x = 10;
	y = 2;
	z = 0;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	boxes[0].p = &x;
	boxes[0].pp = &q;
	boxes[1].p = &y;
	boxes[1].pp = pp;

	bp = &boxes[0];

	total = 0;
	pt = &total;
	ppt = &pt;
	*pp = &z;
	*q = 5;
	**qq = **qq + 1;
	*bp->p = 12;

	rc = run(boxes, 2, ppt);
	if (rc != 0) {
		total = total + rc;
	}

	boxes[1].p = 0;
	rc = run(boxes, 2, ppt);
	if (rc == 0) {
		total = total - 1;
	}

	return 0;
}
