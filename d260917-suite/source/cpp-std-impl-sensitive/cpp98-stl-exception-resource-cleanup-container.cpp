// <original>

#include <deque>
#include <list>
#include <stdexcept>
#include <string>

class Buffer {
public:
	Buffer(int n) : data_(new int[n]), n_(n) {}
	~Buffer() { delete[] data_; }

	int &at(int i) {
		if (i < 0 || i >= n_) {
			throw std::out_of_range("buffer index");
		}
		return data_[i];
	}

	int size() const { return n_; }

private:
	int *data_;
	int n_;
	Buffer(const Buffer &);
	Buffer &operator=(const Buffer &);
};

int fill_and_sum(Buffer *buf, const std::deque<int> *dq, int **acc, int *err) {
	int sum = 0;
	std::size_t i;
	for (i = 0; i < dq->size(); ++i) {
		try {
			buf->at(static_cast<int>(i)) = (*dq)[i];
			sum += buf->at(static_cast<int>(i));
			**acc += 1;
		} catch (const std::out_of_range &e) {
			*err += static_cast<int>(std::string(e.what()).size());
		}
	}
	return sum;
}

int drain(const std::list<int> *src, Buffer *buf, int **acc) {
	int moved = 0;
	std::list<int>::const_iterator it;
	for (it = src->begin(); it != src->end(); ++it) {
		try {
			buf->at(moved) = *it;
			moved += 1;
			**acc += 1;
		} catch (const std::exception &e) {
			break;
		}
	}
	return moved;
}

int main() {
	int x = 1;
	int y = 2;
	int *p = &x;
	int *q = &y;
	int **pp = &p;
	int **qq = &q;
	Buffer buf(3);
	Buffer *bp = &buf;
	std::deque<int> dq;
	std::deque<int> *dp = &dq;
	std::list<int> ls;
	std::list<int> *sp = &ls;
	int count = 0;
	int *cp = &count;
	int err = 0;
	int *ep = &err;
	int total;

	dq.push_back(10);
	dq.push_back(20);
	dq.push_back(30);
	dq.push_back(40);

	ls.push_back(5);
	ls.push_back(6);
	ls.push_back(7);
	ls.push_back(8);

	**pp = **pp + 1;
	**qq = **qq + 2;

	total = fill_and_sum(bp, dp, &cp, ep);
	total += drain(sp, bp, &cp);

	if (count > 0 && err >= 0) {
		total += *cp;
	} else {
		total += *p + *q;
	}

	if (total > 100) {
		total = total % 100;
	} else if (total > 50) {
		total = total % 50;
	} else {
		total = total + 1;
	}

	return 0;
}
