// <original>

#include <memory>
#include <new>
#include <cstddef>

struct Pair {
	int *left;
	int **right;
};

int reduce(Pair *p, std::size_t n, int **out) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (p[i].left != 0 && p[i].right != 0) {
			s = s + *p[i].left + **p[i].right;
		} else if (p[i].left != 0) {
			s = s + *p[i].left;
		} else {
			s = s - 1;
		}
	}
	**out = **out + s;
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Pair proto;
	Pair *buf;
	std::size_t n;
	int total;

	x = 13;
	y = 2;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;
	n = 4;

	proto.left = p;
	proto.right = pp;

	buf = static_cast<Pair *>(::operator new(sizeof(Pair) * n));

	std::uninitialized_fill(buf, buf + n, proto);

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = reduce(buf, n, qq);
	buf[1].left = q;
	buf[1].right = qq;
	total = total + *buf[1].left + **buf[2].right;

	std::destroy_at(buf);
	std::destroy_n(buf + 1, n - 1);
	::operator delete(buf);

	if (total > 0 || **pp > 0) {
		total = total - x;
	} else {
		total = total + y;
	}

	return 0;
}
