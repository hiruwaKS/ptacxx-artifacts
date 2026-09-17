// <original>

#include <memory>
#include <new>
#include <cstddef>

struct Entry {
	int *key;
	int **link;
};

int probe(Entry *e, std::size_t n, int **acc) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (e[i].key != 0) {
			s = s + *e[i].key;
		} else {
			s = s - 1;
		}
	}
	if (acc != 0) {
		**acc = **acc + s;
	}
	return s;
}

int gather(Entry *dst, std::size_t n, int **tag) {
	std::size_t i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		if (dst[i].link == 0) {
			dst[i].link = tag;
		} else if (**dst[i].link > 0) {
			s = s + **dst[i].link;
		} else {
			s = s - 1;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int *pa;
	int *pb;
	int **pp;
	int **qq;
	Entry src[2];
	Entry *raw;
	std::size_t n;
	int total;

	a = 4;
	b = 9;
	pa = &a;
	pb = &b;
	pp = &pa;
	qq = &pb;
	n = 2;

	src[0].key = pa;
	src[0].link = pp;
	src[1].key = pb;
	src[1].link = qq;

	raw = static_cast<Entry *>(::operator new(sizeof(Entry) * n));

	std::uninitialized_copy(src, src + n, raw);
	std::uninitialized_move(raw, raw + n, src);

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = probe(src, n, pp);
	total = total + gather(raw, n, qq);
	total = total + **raw[0].link + *raw[1].key;

	std::destroy_n(raw, n);
	::operator delete(raw);

	if (total > 0 && **qq > 0) {
		total = total - a;
	} else {
		total = total + b;
	}

	return 0;
}
