// <original>

#include <stdlib.h>

struct Node {
	int id;
	int score;
	struct Node *next;
};

int cmp_node_score(const void *a, const void *b) {
	struct Node *na;
	struct Node *nb;
	na = *(struct Node *const *)a;
	nb = *(struct Node *const *)b;
	if (na->score < nb->score) {
		return -1;
	} else if (na->score > nb->score) {
		return 1;
	} else {
		return 0;
	}
}

int cmp_node_id(const void *a, const void *b) {
	struct Node *na;
	struct Node *nb;
	na = *(struct Node *const *)a;
	nb = *(struct Node *const *)b;
	return na->id - nb->id;
}

void link_nodes(struct Node **arr, int n) {
	int i;
	for (i = 0; i < n - 1; i = i + 1) {
		arr[i]->next = arr[i + 1];
	}
	if (n > 0) {
		arr[n - 1]->next = 0;
	}
}

int walk(struct Node **arr, int n, int **acc) {
	struct Node *cur;
	int i;
	int s = 0;
	cur = arr[0];
	for (i = 0; i < n; i = i + 1) {
		if (cur != 0) {
			s = s + cur->score;
			*acc = &cur->score;
			cur = cur->next;
		} else {
			break;
		}
	}
	return s;
}

int main(void) {
	struct Node nodes[5];
	struct Node *ptrs[5];
	struct Node **head;
	struct Node **tail;
	struct Node *p;
	struct Node *q;
	int *hit;
	int *miss;
	struct Node **pp;
	struct Node **qq;
	int total;
	int i;

	for (i = 0; i < 5; i = i + 1) {
		nodes[i].id = i;
		nodes[i].score = (i * 3) % 4;
		nodes[i].next = 0;
		ptrs[i] = &nodes[i];
	}
	head = ptrs;
	tail = ptrs + 4;
	p = *head;
	q = *tail;
	pp = &p;
	qq = &q;
	hit = &nodes[0].score;
	miss = &nodes[4].score;

	qsort(ptrs, 5, sizeof(struct Node *), cmp_node_score);
	link_nodes(ptrs, 5);
	total = walk(ptrs, 5, &hit);
	(*pp)->score = (*pp)->score + (*qq)->score;
	qsort(ptrs, 5, sizeof(struct Node *), cmp_node_id);
	total = total + (*qq)->score;

	if (total > 0 || *pp != 0) {
		total = total + *miss;
	} else {
		total = total - *hit;
	}
	return 0;
}
