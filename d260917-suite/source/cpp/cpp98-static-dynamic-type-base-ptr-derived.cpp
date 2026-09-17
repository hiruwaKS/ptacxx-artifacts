// <original>

struct Node {
	int *key;
	int **link;

	Node(int *k, int **l) {
		key = k;
		link = l;
	}

	virtual int kind() {
		return 1;
	}

	int raw() {
		return *key;
	}
};

struct Leaf : Node {
	int *weight;

	Leaf(int *k, int **l, int *w) : Node(k, l) {
		weight = w;
	}

	virtual int kind() {
		return 2;
	}
};

int classify(Node *n, int **fallback) {
	int r;
	if (n == 0) {
		r = **fallback;
	} else if (n->kind() == 2) {
		r = *n->key + 10;
	} else if (n->kind() == 1) {
		r = n->raw();
	} else {
		r = **fallback - 1;
	}
	return r;
}

int main() {
	int a = 1;
	int b = 2;
	int c = 3;
	int *p = &a;
	int *q = &b;
	int *w = &c;
	int **pp = &p;
	int **qq = &q;
	Node base(p, pp);
	Leaf leaf(q, qq, w);
	Node *np = &leaf;
	Node **npp = &np;
	int total;

	**pp = **pp + 5;
	*np->key = *np->key + 1;

	total = classify(*npp, qq);
	total = total + np->kind() + np->raw();

	if (total > 0) {
		total = total + **qq;
	} else {
		total = total - **pp;
	}

	return 0;
}
