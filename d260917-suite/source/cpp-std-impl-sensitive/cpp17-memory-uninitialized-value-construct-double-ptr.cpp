// <original>

#include <memory>
#include <new>
#include <cstddef>

struct Slot {
	int *ref;
	int **back;
};

int sum(std::size_t n, int **scan) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (scan[i] != 0) {
			s = s + *scan[i];
		} else {
			s = s + 0;
		}
	}
	return s;
}

int link(Slot *slots, std::size_t n, int **a, int **b) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (i % 2 == 0) {
			slots[i].ref = *a;
			slots[i].back = a;
		} else if (i == 1) {
			slots[i].ref = *b;
			slots[i].back = b;
		} else {
			slots[i].ref = *a;
			slots[i].back = b;
		}
		s = s + *slots[i].ref;
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int *vals[2];
	int **pp;
	int **qq;
	int **vp;
	Slot *buf;
	std::size_t n;
	int total;

	x = 11;
	y = 6;
	p = &x;
	q = &y;
	vals[0] = p;
	vals[1] = q;
	vp = vals;
	pp = &p;
	qq = &q;
	n = 3;

	buf = static_cast<Slot *>(::operator new(sizeof(Slot) * n));

	std::uninitialized_value_construct(buf, buf + n);

	**pp = **pp + 1;
	**qq = **qq + 2;
	total = link(buf, n, pp, qq);

	total = total + sum(2, vp);
	total = total + **buf[0].back + *buf[1].ref;

	std::destroy_at(buf);
	std::destroy_n(buf + 1, n - 1);
	::operator delete(buf);

	if (total > 0 && **qq > 0) {
		total = total - x;
	} else {
		total = total + y;
	}

	return 0;
}
