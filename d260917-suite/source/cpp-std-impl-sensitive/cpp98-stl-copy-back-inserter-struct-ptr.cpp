// <original>

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

struct Holder {
	int *cell;
	int **slot;
};

int totalList(std::list<Holder *> *lp) {
	std::list<Holder *>::iterator it;
	int s = 0;
	for (it = lp->begin(); it != lp->end(); ++it) {
		if ((*it)->cell != 0) {
			s = s + *(*it)->cell;
		}
		if ((*it)->slot != 0 && **(*it)->slot > 0) {
			s = s + **(*it)->slot;
		}
	}
	return s;
}

void seed(std::vector<Holder *> *vp, Holder *h, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		vp->push_back(h);
	}
}

void fillList(std::vector<Holder *> *vp, std::list<Holder *> *lp) {
	std::copy(vp->begin(), vp->end(), std::back_inserter(*lp));
}

void fillVector(std::list<Holder *> *lp, std::vector<Holder *> *vp) {
	std::copy(lp->begin(), lp->end(), std::back_inserter(*vp));
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Holder h1;
	Holder h2;
	Holder *hp;
	Holder *hq;
	std::vector<Holder *> src;
	std::list<Holder *> mid;
	std::vector<Holder *> dst;
	int total;

	x = 3;
	y = 4;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	h1.cell = p;
	h1.slot = pp;
	h2.cell = q;
	h2.slot = qq;
	hp = &h1;
	hq = &h2;

	**pp = **pp + 1;
	**qq = **qq + 2;

	seed(&src, hp, 2);
	seed(&src, hq, 3);

	fillList(&src, &mid);
	fillVector(&mid, &dst);

	hp->cell = q;
	*hp->slot = p;

	total = totalList(&mid);
	total = total + totalList(&mid) + *hp->cell + **hq->slot;

	if (total > 0 && **pp > 0) {
		total = total - *p;
	} else {
		total = total + *q;
	}

	return 0;
}
