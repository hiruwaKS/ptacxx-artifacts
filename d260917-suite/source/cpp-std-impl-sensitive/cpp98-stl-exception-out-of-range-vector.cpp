// <original>

#include <vector>
#include <stdexcept>
#include <string>

int score(const std::vector<int> *vp, std::size_t idx, bool guard) {
	int v = 0;
	if (vp == 0) {
		return -1;
	}
	if (guard && idx >= vp->size()) {
		return 0;
	}
	try {
		v = vp->at(idx);
	} catch (const std::out_of_range &e) {
		v = -static_cast<int>(std::string(e.what()).size());
	}
	return v;
}

int scan(const std::vector<int> *vp, int *out, int n) {
	int hits = 0;
	int i;
	for (i = 0; i < n; ++i) {
		try {
			*out = vp->at(static_cast<std::size_t>(i));
			if (*out % 2 == 0 || *out > 100) {
				hits += 1;
			}
			out += 1;
		} catch (const std::exception &e) {
			if (std::string(e.what()).size() > 0) {
				hits += 2;
			}
		}
	}
	return hits;
}

int main() {
	int x = 3;
	int y = 4;
	int *p = &x;
	int *q = &y;
	int **pp = &p;
	int **qq = &q;
	std::vector<int> data;
	std::vector<int> *vp = &data;
	int results[8];
	int *rp = results;
	int total;

	data.push_back(10);
	data.push_back(20);
	data.push_back(30);

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = score(vp, 1, true);
	total += score(vp, 5, false);
	total += scan(vp, rp, 4);

	if (**pp > **qq) {
		total += *p;
	} else {
		total += *q;
	}

	switch (total % 3) {
	case 0:
		total += 1;
		break;
	case 1:
		total += 2;
		break;
	default:
		total += 3;
		break;
	}

	return 0;
}
