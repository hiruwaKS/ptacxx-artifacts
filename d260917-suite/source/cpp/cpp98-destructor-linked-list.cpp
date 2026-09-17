// <original>

int gnodes;

struct Node {
	int *value;
	int **link;
	Node *next;

	Node(int *v, int **l) {
		value = v;
		link = l;
		next = 0;
		gnodes = gnodes + 1;
	}

	~Node() {
		if (value != 0) {
			*value = *value + 1;
		}
		if (link != 0) {
			**link = **link + 1;
		}
		gnodes = gnodes - 1;
	}
};

struct List {
	Node *head;
	int count;

	List() {
		head = 0;
		count = 0;
	}

	void push(int *v, int **l) {
		Node *n = new Node(v, l);
		n->next = head;
		head = n;
		count = count + 1;
	}

	~List() {
		Node *cur = head;
		while (cur != 0) {
			Node *nxt = cur->next;
			delete cur;
			cur = nxt;
		}
		head = 0;
		count = 0;
	}

	int total() {
		int s = 0;
		Node *cur = head;
		while (cur != 0) {
			if (cur->value != 0) {
				s = s + *cur->value;
			} else {
				s = s + 0;
			}
			cur = cur->next;
		}
		return s;
	}
};

int walk(List **ll, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i == 0) {
			s = s + (*ll)->total();
		} else if (i == 1) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int *p;
	int *q;
	int **pp;
	int **qq;
	List *lst;
	List **ll;
	int total;

	a = 1;
	b = 2;
	p = &a;
	q = &b;
	pp = &p;
	qq = &q;

	lst = new List();
	ll = &lst;

	(*ll)->push(p, pp);
	(*ll)->push(q, qq);

	total = walk(ll, pp, qq, 3);
	**pp = **pp + 5;
	**qq = **qq + 6;

	if (gnodes > 0) {
		total = total + *p;
	} else {
		total = total + *q;
	}

	delete *ll;

	return 0;
}
