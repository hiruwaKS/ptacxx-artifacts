// <original>

#include <vector>
#include <stdexcept>
#include <string>

class AppError : public std::exception {
public:
	explicit AppError(int code) : code_(code) {}
	virtual ~AppError() throw() {}
	virtual const char *what() const throw() { return "AppError"; }
	int code() const { return code_; }

private:
	int code_;
};

class FatalError : public AppError {
public:
	explicit FatalError(int c) : AppError(c) {}
	virtual const char *what() const throw() { return "FatalError"; }
};

int run_job(int **slot, int *log, int depth) {
	int i;
	int r = 0;
	for (i = 0; i < depth; ++i) {
		try {
			if (i == 0) {
				throw AppError(1);
			} else if (i == 1) {
				throw FatalError(2);
			} else if (i == 2) {
				throw std::out_of_range("range");
			}
			**slot += 1;
		} catch (const AppError &e) {
			*log += e.code();
		} catch (const std::exception &e) {
			*log += static_cast<int>(std::string(e.what()).size());
		}
		r += i;
	}
	return r;
}

int main() {
	int x = 9;
	int y = 10;
	int *p = &x;
	int *q = &y;
	int **pp = &p;
	int **qq = &q;
	std::vector<AppError *> history;
	std::vector<AppError *> *hp = &history;
	int log = 0;
	int *lp = &log;
	int total;

	**pp = **pp + 1;
	**qq = **qq + 2;

	history.push_back(new AppError(3));
	history.push_back(new FatalError(4));

	total = run_job(pp, lp, 4);
	total += run_job(qq, lp, 3);

	if (total > 0 || log > 0) {
		total += *lp;
	} else {
		total += *p + *q;
	}

	{
		std::size_t i;
		for (i = 0; i < hp->size(); ++i) {
			if ((*hp)[i] != 0) {
				total += (*hp)[i]->code();
				delete (*hp)[i];
			}
		}
	}

	switch (total % 4) {
	case 0:
		total += 1;
		break;
	case 1:
		total += 2;
		break;
	case 2:
		total += 3;
		break;
	default:
		total += 4;
		break;
	}

	return 0;
}
