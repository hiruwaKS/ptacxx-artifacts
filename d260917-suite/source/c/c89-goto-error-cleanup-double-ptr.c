// <original>

#include <stdlib.h>

struct Node {
	int value;
	struct Node *next;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

struct Node *make_node(int v, struct Node *next) {
	struct Node *n;
	n = (struct Node *) malloc(sizeof(struct Node));
	if (n == 0) {
		goto bad;
	}
	n->value = v;
	n->next = next;
	return n;
bad:
	return 0;
}

void free_list(struct Node *head) {
	struct Node *cur;
	struct Node *tmp;
	cur = head;
again:
	if (cur == 0) {
		goto out;
	}
	tmp = cur->next;
	free(cur);
	cur = tmp;
	goto again;
out:
	return;
}

int sum_list(struct Node *head, int **out) {
	int total;
	struct Node *cur;
	total = 0;
	cur = head;
	while (cur != 0) {
		total = total + cur->value;
		cur = cur->next;
	}
	if (out != 0) {
		**out = **out + total;
	}
	return total;
}

struct Node *reverse_list(struct Node *head) {
	struct Node *prev;
	struct Node *cur;
	struct Node *next;
	prev = 0;
	cur = head;
step:
	if (cur == 0) {
		goto end;
	}
	next = cur->next;
	cur->next = prev;
	prev = cur;
	cur = next;
	goto step;
end:
	return prev;
}

int build(int n, struct Node **head_out, int **sum_out) {
	struct Node *head;
	struct Node *tail;
	struct Node *n1;
	struct Node *n2;
	int i;
	int rc;
	head = 0;
	tail = 0;
	rc = 0;
	if (n <= 0) {
		rc = -1;
		goto fail;
	}
	n1 = make_node(1, 0);
	if (n1 == 0) {
		rc = -2;
		goto fail;
	}
	head = n1;
	tail = n1;
	for (i = 1; i < n; i = i + 1) {
		n2 = make_node(i + 1, 0);
		if (n2 == 0) {
			rc = -3;
			goto fail;
		}
		tail->next = n2;
		tail = n2;
	}
	*head_out = head;
	*sum_out = g_ptr;
	return rc;
fail:
	free_list(head);
	*head_out = 0;
	return rc;
}

int main() {
	struct Node *head;
	struct Node *rev;
	int *sum;
	int *slot;
	int **pp;
	int **qq;
	int total;
	int rc;

	head = 0;
	rev = 0;
	sum = &g_base;
	slot = 0;
	pp = &sum;
	qq = &slot;

	g_base = 0;
	*pp = &g_base;
	**pp = 10;
	*qq = &g_base;
	**qq = **qq + 5;
	*g_dptr = &g_base;

	rc = build(4, &head, &sum);
	if (rc != 0) {
		goto cleanup;
	}

	total = sum_list(head, pp);
	total = total + **pp + **qq;

	rev = reverse_list(head);
	head = 0;
	if (rev != 0) {
		total = total + rev->value;
	}

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - *slot;
		} else {
			total = total + **g_dptr;
		}
	} else {
		total = 0;
	}

cleanup:
	free_list(head);
	free_list(rev);
	return 0;
}
