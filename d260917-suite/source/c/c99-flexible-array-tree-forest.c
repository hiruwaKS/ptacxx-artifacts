// <original>

#include <stdlib.h>

struct Node {
	int id;
	int *payload;
	struct Node **kids;
};

struct Forest {
	int count;
	struct Node *root;
	int depth[];
};

struct Node *make_node(int id, int *payload) {
	struct Node *n;
	n = (struct Node *)malloc(sizeof(struct Node));
	n->id = id;
	n->payload = payload;
	n->kids = (struct Node **)malloc(2 * sizeof(struct Node *));
	n->kids[0] = 0;
	n->kids[1] = 0;
	return n;
}

struct Forest *make_forest(int count, struct Node *root) {
	struct Forest *f;
	f = (struct Forest *)malloc(sizeof(struct Forest) + count * sizeof(int));
	f->count = count;
	f->root = root;
	return f;
}

void link(struct Node *parent, struct Node *child, int slot) {
	if (slot == 0) {
		parent->kids[0] = child;
	} else if (slot == 1) {
		parent->kids[1] = child;
	} else {
		parent->kids[1] = child;
	}
}

int walk(struct Node *n, int **pp, int **qq) {
	int s;
	s = 0;
	if (n == 0) {
		s = **pp;
	} else {
		s = *n->payload;
		if (n->kids[0] != 0) {
			s = s + walk(n->kids[0], pp, qq);
		} else if (n->kids[1] != 0) {
			s = s + walk(n->kids[1], qq, pp);
		} else {
			s = s + **qq;
		}
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
	int **via;
	struct Node *a;
	struct Node *b;
	struct Node *c;
	struct Node **np;
	struct Forest *f;
	struct Forest **fp;
	int total;
	int i;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	a = make_node(1, p);
	b = make_node(2, q);
	c = make_node(3, p);
	link(a, b, 0);
	link(b, c, 1);

	f = make_forest(3, a);
	fp = &f;
	np = &a;

	for (i = 0; i < f->count; i = i + 1) {
		f->depth[i] = i;
	}

	(*fp)->root->id = **pp;
	(*np)->payload = q;
	*a->kids[0]->payload = *a->kids[0]->payload + 1;
	**qq = **qq + 7;

	via = pp;
	**via = **via + 3;

	total = walk((*fp)->root, pp, qq) + f->depth[1];
	total = total + **via + *(*np)->payload;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	free(a->kids);
	free(b->kids);
	free(c->kids);
	free(a);
	free(b);
	free(c);
	free(f);
	return 0;
}
