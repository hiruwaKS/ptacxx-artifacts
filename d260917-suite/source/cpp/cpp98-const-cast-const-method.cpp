// <original>

int gtotal;

struct Store {
	int *data;
	int **refs;
	int size;

	Store(int n) {
		int i;
		size = n;
		data = new int[n];
		refs = new int*[n];
		for (i = 0; i < n; i = i + 1) {
			data[i] = i + 1;
			refs[i] = &data[i];
		}
	}

	~Store() {
		delete [] refs;
		delete [] data;
	}

	int total() const {
		int i;
		int s = 0;
		for (i = 0; i < size; i = i + 1) {
			if (refs[i] != 0) {
				s = s + *refs[i];
			}
		}
		return s;
	}

	void reset(int v) const {
		Store *self;
		int i;
		self = const_cast<Store *>(this);
		for (i = 0; i < self->size; i = i + 1) {
			*self->refs[i] = v;
		}
		if (self->data != 0) {
			*self->data = v + 1;
		}
	}
};

int scan(const Store *s, const Store **ss) {
	int t;
	if (ss != 0 && *ss != 0) {
		t = (*ss)->total();
	} else {
		t = s->total();
	}
	return t;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Store *s;
	Store **ss;
	const Store *cs;
	const Store **css;
	int total;

	x = 5;
	y = 6;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	s = new Store(3);
	ss = &s;
	cs = s;
	css = const_cast<const Store **>(ss);

	s->reset(9);
	total = scan(cs, css);

	**pp = **pp + 1;
	**qq = **qq + 2;
	total = total + **pp + **qq;

	if (total > 0 && x > 0) {
		total = total - 1;
	} else {
		total = total + 1;
	}

	delete *ss;

	gtotal = total;

	return 0;
}
