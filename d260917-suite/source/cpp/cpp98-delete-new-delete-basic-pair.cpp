// <original>

struct Cell {
	int value;
	int *link;
};

int g_base;
int *g_ptr = &g_base;
int **g_dptr = &g_ptr;

Cell *make_cell(int v, int *link) {
	Cell *c;
	c = new Cell;
	if (c == 0) {
		return 0;
	}
	c->value = v;
	c->link = link;
	return c;
}

void set_link(Cell *c, int *v, int **out) {
	if (c != 0) {
		c->link = v;
		*c->link = *c->link + 1;
	}
	if (out != 0) {
		**out = **out + 1;
	}
}

int sum_cells(Cell **cells, int n, int **pp, int **qq) {
	int s;
	int i;
	s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (cells[i] == 0) {
			continue;
		}
		if (i == 0) {
			s = s + *cells[i]->link;
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
	int **via;
	Cell *c;
	Cell *d;
	Cell **table;
	int total;

	x = 1;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	c = make_cell(3, p);
	d = make_cell(4, q);
	table = new Cell *[2];
	table[0] = c;
	table[1] = d;

	*pp = &y;
	**pp = **pp + 1;
	*q = *q + 1;
	**qq = **qq + 2;
	set_link(c, q, pp);

	via = &p;
	**via = **via + 3;

	total = sum_cells(table, 2, pp, qq);
	total = total + *c->link + **via;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total - x;
		} else {
			total = total + y;
		}
	} else {
		total = 0;
	}

	delete c;
	delete d;
	delete [] table;

	return 0;
}
