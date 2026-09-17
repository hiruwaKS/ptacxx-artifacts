// <original>

#include <stddef.h>
#include <stdlib.h>

int g_alloc_count;
int g_free_count;

struct Tracked {
	int id;
	int *slot;
	static void *operator new(size_t sz);
	static void operator delete(void *p);
	static void *operator new[](size_t sz);
	static void operator delete[](void *p);
};

void *Tracked::operator new(size_t sz) {
	void *p;
	p = malloc(sz);
	g_alloc_count = g_alloc_count + 1;
	return p;
}

void Tracked::operator delete(void *p) {
	if (p != 0) {
		g_free_count = g_free_count + 1;
		free(p);
	}
}

void *Tracked::operator new[](size_t sz) {
	void *p;
	p = malloc(sz);
	g_alloc_count = g_alloc_count + 1;
	return p;
}

void Tracked::operator delete[](void *p) {
	if (p != 0) {
		g_free_count = g_free_count + 1;
		free(p);
	}
}

Tracked *make(int v, int *slot) {
	Tracked *t;
	t = new Tracked;
	if (t == 0) {
		return 0;
	}
	t->id = v;
	t->slot = slot;
	return t;
}

int total_ids(Tracked **arr, int n, int **pp, int **qq) {
	int s;
	int i;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (arr[i] == 0) {
			continue;
		}
		if (i == 0) {
			s = s + *arr[i]->slot;
		} else if (i == 1) {
			s = s + **pp;
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
	Tracked *a;
	Tracked *b;
	Tracked *block;
	Tracked **vec;
	int total;

	g_alloc_count = 0;
	g_free_count = 0;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	a = make(10, p);
	b = make(20, q);
	block = new Tracked[3];
	vec = new Tracked *[2];
	vec[0] = a;
	vec[1] = b;

	*pp = &y;
	**pp = **pp + 1;
	*q = *q + 1;
	**qq = **qq + 2;

	total = total_ids(vec, 2, pp, qq);
	total = total + a->id + b->id + **pp;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	delete a;
	delete b;
	delete [] block;
	delete [] vec;

	if (g_alloc_count >= g_free_count) {
		total = total + 1;
	}

	return 0;
}
