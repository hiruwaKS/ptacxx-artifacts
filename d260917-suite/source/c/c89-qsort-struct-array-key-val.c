// <original>

#include <stdlib.h>

struct Rec {
	int key;
	int val;
	int *link;
};

int cmp_rec_key(const void *a, const void *b) {
	const struct Rec *ra;
	const struct Rec *rb;
	ra = (const struct Rec *)a;
	rb = (const struct Rec *)b;
	if (ra->key < rb->key) {
		return -1;
	} else if (ra->key > rb->key) {
		return 1;
	} else {
		return 0;
	}
}

int cmp_rec_val(const void *a, const void *b) {
	const struct Rec *ra;
	const struct Rec *rb;
	ra = (const struct Rec *)a;
	rb = (const struct Rec *)b;
	return rb->val - ra->val;
}

void init(struct Rec *arr, int n, int *base) {
	int i;
	for (i = 0; i < n; i = i + 1) {
		arr[i].key = (n - i) % 3;
		arr[i].val = i * 2;
		arr[i].link = base + i;
	}
}

int collect(struct Rec *arr, int n, int **out) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (arr[i].key == 0) {
			out[i] = arr[i].link;
			s = s + *arr[i].link;
		} else if (arr[i].key == 1) {
			out[i] = &arr[i].val;
			s = s + *out[i];
		} else {
			out[i] = arr[i].link;
			s = s - *out[i];
		}
	}
	return s;
}

int main(void) {
	struct Rec recs[6];
	struct Rec *rp;
	struct Rec *rq;
	struct Rec **rpp;
	int *links[6];
	int *first;
	int *last;
	int **pp;
	int **qq;
	int total;

	init(recs, 6, &recs[0].val);
	rp = &recs[0];
	rq = &recs[5];
	rpp = &rp;
	first = &recs[0].val;
	last = &recs[5].val;
	pp = &first;
	qq = &last;

	total = collect(recs, 6, links);
	qsort(recs, 6, sizeof(struct Rec), cmp_rec_key);
	(*rpp)->key = (*rpp)->key + **pp;
	total = total + rq->val + *rq->link;

	qsort(recs, 6, sizeof(struct Rec), cmp_rec_val);
	if (total > 0 && rq->key >= 0) {
		total = total + rq->key;
	} else {
		total = total - *rq->link;
	}

	if (total != 0) {
		total = total + **qq;
	}
	return 0;
}
