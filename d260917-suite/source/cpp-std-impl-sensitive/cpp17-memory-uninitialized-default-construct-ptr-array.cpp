// <original>

#include <memory>
#include <new>
#include <cstddef>

struct Cell {
	int *value;
	int **link;

	Cell() {
		value = 0;
		link = 0;
	}
};

int seed(std::size_t n, int *base, int **root) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (base != 0) {
			s = s + *base + static_cast<int>(i);
		} else {
			s = s - 1;
		}
	}
	if (root != 0 && *root != 0) {
		s = s + **root;
	}
	return s;
}

int attach(Cell *cells, std::size_t n, int **slot) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		cells[i].value = *slot;
		cells[i].link = slot;
		if (cells[i].value != 0) {
			s = s + *cells[i].value;
		} else {
			s = s + 0;
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
	Cell *buf;
	std::size_t n;
	int total;

	x = 5;
	y = 7;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	n = 3;

	buf = static_cast<Cell *>(::operator new(sizeof(Cell) * n));

	std::uninitialized_default_construct(buf, buf + n);

	**pp = **pp + 1;
	**qq = **qq + 2;
	total = attach(buf, n, pp);

	buf[0].link = qq;
	*buf[0].value = *buf[0].value + 1;
	total = total + **buf[1].link + seed(n, *pp, qq);

	std::destroy_n(buf, n);
	::operator delete(buf);

	if (total > 0 && **pp > 0) {
		total = total - x;
	} else {
		total = total + y;
	}

	return 0;
}
