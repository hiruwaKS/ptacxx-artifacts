// <original>

#include <map>
#include <set>

struct Cell {
	int *p;
	int **pp;
	Cell(int *a, int **b) : p(a), pp(b) {}
};

int g_val;
int *g_ptr = &g_val;
int **g_dptr = &g_ptr;

int walkMap(std::map<int, Cell> *m, int **qq) {
	std::map<int, Cell>::iterator it;
	int s = 0;
	for (it = m->begin(); it != m->end(); ++it) {
		Cell *c = &it->second;
		if (c->p != 0) {
			s = s + *c->p;
		} else if (c->pp != 0) {
			s = s + **c->pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int walkSet(std::set<int **> *st, int **pp) {
	std::set<int **>::iterator it;
	int s = 0;
	for (it = st->begin(); it != st->end(); ++it) {
		int **e = *it;
		if (e != 0) {
			**e = **e + 1;
			s = s + **e;
		} else {
			s = s + **pp;
		}
	}
	return s;
}

void insertCells(std::map<int, Cell> *m, int *p, int **pp, int n) {
	int i;
	std::map<int, Cell>::iterator hint = m->begin();
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			m->emplace(i, Cell(p, pp));
		} else {
			m->emplace_hint(hint, i, Cell(p, pp));
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
	std::map<int, Cell> m;
	std::set<int **> st;
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	m.emplace(0, Cell(p, pp));
	m.emplace(1, Cell(q, qq));
	st.emplace(pp);
	st.emplace(qq);

	insertCells(&m, q, qq, 2);

	*pp = &y;
	**qq = **qq + 1;
	*g_ptr = *g_ptr + 5;
	**g_dptr = **g_dptr + 6;

	total = walkMap(&m, qq);
	total = total + walkSet(&st, pp);

	if (total > 0 && **pp > 0) {
		total = total - *q;
	} else if (total < 0) {
		total = total + *p;
	} else {
		total = 0;
	}

	return 0;
}
