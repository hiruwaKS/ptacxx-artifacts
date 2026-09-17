// <original>

#include <utility>
#include <vector>

struct Node {
	int *val;
	int **link;

	Node() : val(0), link(0) {}
	Node(int *v, int **l) : val(v), link(l) {}

	Node(Node &&o) : val(o.val), link(o.link) {
		o.val = 0;
		o.link = 0;
	}

	Node &operator=(Node &&o) {
		if (this != &o) {
			val = o.val;
			link = o.link;
			o.val = 0;
			o.link = 0;
		}
		return *this;
	}
};

struct Bag {
	std::vector<Node> nodes;

	Bag() {}
	Bag(Bag &&o) : nodes(std::move(o.nodes)) {}

	Bag &operator=(Bag &&o) {
		if (this != &o) {
			nodes = std::move(o.nodes);
		}
		return *this;
	}
};

int walkBag(Bag *b, int **pp) {
	int i;
	int s = 0;
	for (i = 0; i < (int)b->nodes.size(); ++i) {
		Node &n = b->nodes[i];
		if (n.val != 0) {
			s = s + *n.val;
		} else if (n.link != 0) {
			s = s + **n.link;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

void grow(Bag *b, int *p, int **pp, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			b->nodes.push_back(Node(p, 0));
		} else {
			b->nodes.push_back(Node(0, pp));
		}
	}
}

int transfer(Bag *src, Bag *dst, int **pp) {
	*dst = std::move(*src);
	if (dst->nodes.size() > 0 && dst->nodes[0].val != 0) {
		**pp = **pp + *dst->nodes[0].val;
	} else {
		**pp = **pp - 1;
	}
	return **pp;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Bag a;
	Bag c;
	int total;

	x = 10;
	y = 20;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 2;
	**qq = **qq + 3;
	*p = *p + *q;

	grow(&a, p, qq, 4);

	total = walkBag(&a, pp);
	total = total + transfer(&a, &c, qq);
	total = total + *q + **pp + **qq;

	if (total > 0 && **qq > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
