// <original>

#include <stdexcept>
#include <string>
#include <vector>

int parse(const std::string *s, int *out) {
	std::size_t i;
	int acc = 0;
	bool any = false;
	if (s == 0) {
		throw std::runtime_error("null string");
	}
	for (i = 0; i < s->size(); ++i) {
		char c = (*s)[i];
		if (c >= '0' && c <= '9') {
			acc = acc * 10 + (c - '0');
			any = true;
		} else if (c == '-') {
			acc = -acc;
		} else {
			break;
		}
	}
	if (!any) {
		throw std::invalid_argument("no digits");
	}
	*out = acc;
	return acc;
}

int convert_all(const std::vector<std::string> *in, int *outs, int **errs) {
	int ok = 0;
	int i;
	for (i = 0; i < static_cast<int>(in->size()); ++i) {
		try {
			parse(&(*in)[i], &outs[i]);
			ok += 1;
		} catch (const std::invalid_argument &e) {
			outs[i] = 0;
			**errs += 1;
		} catch (const std::runtime_error &e) {
			outs[i] = -1;
			**errs += 2;
		}
	}
	return ok;
}

int main() {
	int x = 7;
	int y = 8;
	int *p = &x;
	int *q = &y;
	int **pp = &p;
	int **qq = &q;
	std::vector<std::string> input;
	std::vector<std::string> *vp = &input;
	int results[4];
	int *rp = results;
	int errors = 0;
	int *ep = &errors;
	int ok;

	input.push_back("123");
	input.push_back("45x");
	input.push_back("abc");
	input.push_back("-9");

	**pp = **pp + 1;
	**qq = **qq + 2;

	ok = convert_all(vp, rp, &ep);

	if (ok > 0 && errors > 0) {
		*rp += *p;
	} else if (ok == 0) {
		*rp += *q;
	} else {
		*rp += **pp;
	}

	switch (errors % 3) {
	case 0:
		*rp += 1;
		break;
	case 1:
		*rp += 2;
		break;
	default:
		*rp += 3;
		break;
	}

	return 0;
}
