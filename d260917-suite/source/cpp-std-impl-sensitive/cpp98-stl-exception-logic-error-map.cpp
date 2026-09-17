// <original>

#include <map>
#include <stdexcept>
#include <string>

class KeyError : public std::logic_error {
public:
	explicit KeyError(const std::string &m) : std::logic_error(m) {}
};

class Registry {
public:
	Registry() : count_(0) {}

	void put(const std::string &k, int v) {
		store_[k] = v;
		count_ += 1;
	}

	int get(const std::string &k) const {
		std::map<std::string, int>::const_iterator it = store_.find(k);
		if (it == store_.end()) {
			throw KeyError("missing key");
		}
		return it->second;
	}

	std::size_t size() const {
		return store_.size();
	}

private:
	std::map<std::string, int> store_;
	int count_;
};

int lookup(const Registry *reg, const std::string &key, int *out) {
	try {
		*out = reg->get(key);
	} catch (const std::logic_error &e) {
		*out = -static_cast<int>(std::string(e.what()).size());
	} catch (const std::exception &e) {
		*out = -1;
	}
	return *out;
}

int probe(const Registry *reg, const std::string *keys, int n, int **acc) {
	int i;
	int found = 0;
	for (i = 0; i < n; ++i) {
		try {
			int v = reg->get(keys[i]);
			**acc += v;
			found += 1;
		} catch (const KeyError &e) {
			found -= 1;
		} catch (const std::exception &e) {
			found -= 2;
		}
	}
	return found;
}

int main() {
	int a = 5;
	int b = 6;
	int *p = &a;
	int *q = &b;
	int **pp = &p;
	int **qq = &q;
	Registry reg;
	const Registry *rp = &reg;
	std::string keys[4];
	std::string *kp = keys;
	int value;
	int *out = &value;
	int missing = 0;
	int *missp = &missing;

	reg.put("alpha", 11);
	reg.put("beta", 22);

	keys[0] = "alpha";
	keys[1] = "beta";
	keys[2] = "gamma";
	keys[3] = "delta";

	**pp = **pp + 1;
	**qq = **qq + 2;

	lookup(rp, keys[0], out);
	missing += probe(rp, kp, 4, &missp);

	if (**pp < **qq) {
		*out += *p;
	} else {
		*out += *q;
	}

	switch (missing) {
	case 0:
		*out += 1;
		break;
	case 1:
		*out += 2;
		break;
	default:
		*out += 3;
		break;
	}

	if (rp->size() > 0 && *out != 0) {
		*out = *out - 1;
	}

	return 0;
}
