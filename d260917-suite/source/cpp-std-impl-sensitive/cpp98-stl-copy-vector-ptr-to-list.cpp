// <original>

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

int drainList(std::list<int *> *lp) {
	std::list<int *>::iterator it;
	int s = 0;
	for (it = lp->begin(); it != lp->end(); ++it) {
		if (*it != 0) {
			s = s + **it;
		} else {
			s = s - 1;
		}
	}
	return s;
}

int gather(std::vector<int *> *vp, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; ++i) {
		vp->push_back(*pp);
		s = s + **pp;
	}
	return s;
}

void relocate(std::vector<int *> *vp, std::list<int *> *lp) {
	std::copy(vp->begin(), vp->end(), std::back_inserter(*lp));
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	std::vector<int *> src;
	std::list<int *> dst;
	std::list<int *>::iterator lit;
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = gather(&src, pp, 2);
	total = total + gather(&src, qq, 3);

	relocate(&src, &dst);

	for (lit = dst.begin(); lit != dst.end(); ++lit) {
		if (*lit != 0) {
			**lit = **lit + *p;
		}
	}

	total = total + drainList(&dst);
	total = total + (int)src.size() + *q;

	if (total > 0 && **pp > 0) {
		total = total - *p;
	} else {
		total = total + *q;
	}

	return 0;
}
