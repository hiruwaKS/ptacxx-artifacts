// <original>

#include <list>

struct Link {
	int *val;
	int **ref;
	Link(int *v, int **r) : val(v), ref(r) {}
};

int g_cell;
int *g_ptr = &g_cell;
int **g_dptr = &g_ptr;

int sumList(std::list<Link> *lst, int **pp) {
	std::list<Link>::iterator it;
	int s = 0;
	for (it = lst->begin(); it != lst->end(); ++it) {
		if (it->val != 0) {
			s = s + *it->val;
		} else if (it->ref != 0) {
			s = s + **it->ref;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int bumpList(std::list<int **> *lst, int **pp) {
	std::list<int **>::iterator it;
	int s = 0;
	for (it = lst->begin(); it != lst->end(); ++it) {
		int **e = *it;
		if (e != 0) {
			**e = **e + **pp;
			s = s + **e;
		} else {
			s = s - 1;
		}
	}
	return s;
}

void fill(std::list<Link> *lst, std::list<int **> *raw, int *p, int **pp, int n) {
	int i;
	std::list<Link>::iterator hint = lst->begin();
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			lst->emplace_front(p, pp);
			raw->emplace_front(pp);
		} else {
			lst->emplace(hint, p, pp);
			raw->emplace_back(pp);
		}
	}
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::list<Link> lst;
	std::list<int **> raw;
	int total;

	x = 7;
	y = 8;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	lst.emplace_back(p, pp);
	lst.emplace_front(q, qq);
	raw.emplace_back(pp);
	raw.emplace_front(qq);

	fill(&lst, &raw, p, pp, 3);

	*pp = &y;
	**qq = **qq + 1;
	*g_ptr = *g_ptr + 4;
	**g_dptr = **g_dptr + 5;

	total = sumList(&lst, qq);
	total = total + bumpList(&raw, pp);

	if (total > 0 && **pp > 0) {
		total = total - *q;
	} else if (total < 0) {
		total = total + *p;
	} else {
		total = 0;
	}

	return 0;
}
