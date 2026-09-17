// <original>

#include <cstdio>

struct Node {
	int value;
	Node *next;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

Node *make_node(int v, Node *next) {
	Node *n;
	n = new Node;
	n->value = v;
	n->next = next;
	return n;
}

void free_list(Node *head) {
	Node *cur;
	Node *tmp;
	cur = head;
	while (cur != 0) {
		tmp = cur->next;
		delete cur;
		cur = tmp;
	}
}

int push(Node **head, int v, int **count) {
	Node *n;
	n = make_node(v, *head);
	if (n == 0) {
		throw "alloc failed";
	}
	*head = n;
	**count = **count + 1;
	return n->value;
}

int build(Node **head, int n, int **count) {
	int i;
	int last;
	last = 0;
	for (i = 0; i < n; i = i + 1) {
		try {
			last = push(head, i + 1, count);
		} catch (const char *msg) {
			throw;
		}
		if (last < 0) {
			throw last;
		}
	}
	return last;
}

int drain(Node **head, int **out) {
	int s;
	Node *cur;
	s = 0;
	cur = *head;
	while (cur != 0) {
		s = s + cur->value;
		if (cur->next != 0) {
			s = s + cur->next->value / 2;
		}
		cur = cur->next;
	}
	*head = 0;
	**out = **out + s;
	return s;
}

int main() {
	Node *head;
	Node *rev;
	int count;
	int *pc;
	int **ppc;
	int *slot;
	int **pps;
	int total;
	int rc;

	head = 0;
	rev = 0;
	count = 0;
	slot = &count;
	pc = &count;
	ppc = &pc;
	pps = &slot;

	*g_dptr = &count;
	*ppc = &count;
	**ppc = **ppc + 2;
	*slot = *slot + 1;

	total = 0;
	rc = 0;
	try {
		build(&head, 4, ppc);
		total = drain(&head, pps);
		total = total + **ppc + **pps;
		rev = make_node(total, 0);
	} catch (const char *msg) {
		rc = 1;
	} catch (int code) {
		rc = code;
	}

	total = total + rc;
	free_list(head);
	free_list(rev);
	return 0;
}
