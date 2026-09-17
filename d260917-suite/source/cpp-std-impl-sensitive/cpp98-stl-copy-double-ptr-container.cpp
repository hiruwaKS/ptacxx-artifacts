// <original>

#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

struct Holder {
	int **slot;
	int *cell;
};

int walkDeque(std::deque<int **> *dq) {
	std::deque<int **>::iterator it;
	int s = 0;
	for (it = dq->begin(); it != dq->end(); ++it) {
		if (*it != 0) {
			s = s + ***it;
		} else {
			s = s - 1;
		}
	}
	return s;
}

void load(std::vector<int **> *vp, int **pp, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		vp->push_back(pp);
	}
}

void shift(std::deque<int **> *dq, int **pp) {
	std::deque<int **>::iterator it;
	for (it = dq->begin(); it != dq->end(); ++it) {
		if (**it != 0) {
			***it = ***it + **pp;
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
	std::vector<int **> src;
	std::deque<int **> dst;
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;

	load(&src, pp, 2);
	load(&src, qq, 3);

	std::copy(src.begin(), src.end(), std::back_inserter(dst));
	std::copy_backward(dst.begin(), dst.begin() + 3, dst.end());

	shift(&dst, pp);
	total = walkDeque(&dst);
	total = total + **pp + **qq + *p + *q;

	if (total > 0 && **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
