// <original>

#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

int sumRange(std::vector<int *> *vp, int lo, int hi) {
	std::vector<int *>::iterator it;
	int s = 0;
	for (it = vp->begin() + lo; it != vp->begin() + hi; ++it) {
		if (*it != 0) {
			s = s + **it;
		} else {
			s = s - 1;
		}
	}
	return s;
}

void bump(std::vector<int *> *vp, int idx, int **pp) {
	std::vector<int *>::iterator it;
	it = vp->begin() + idx;
	if (it != vp->end()) {
		**it = **it + **pp;
	}
}

int main() {
	int a;
	int b;
	int c;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	std::vector<int *> buf(6);
	std::deque<int *> out;
	std::deque<int *>::iterator dit;
	int total;

	a = 1;
	b = 2;
	c = 5;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;

	buf[0] = p;
	buf[1] = q;
	buf[2] = r;
	buf[3] = *pp;
	buf[4] = *qq;
	buf[5] = p;

	std::copy_backward(buf.begin(), buf.begin() + 3, buf.end());

	bump(&buf, 0, pp);
	bump(&buf, 2, qq);

	std::copy(buf.begin(), buf.begin() + 4, std::back_inserter(out));

	total = sumRange(&buf, 0, 6);
	for (dit = out.begin(); dit != out.end(); ++dit) {
		if (*dit != 0 && **dit > 0) {
			total = total + **dit;
		}
	}
	total = total + *p + *q + *r;

	if (total > 0 || **pp > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	return 0;
}
