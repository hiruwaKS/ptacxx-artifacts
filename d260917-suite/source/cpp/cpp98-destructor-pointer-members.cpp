// <original>

int gtotal;

struct Buffer {
	int *data;
	int **refs;
	int size;

	Buffer(int n, int *r) {
		int i;
		size = n;
		data = new int[n];
		refs = new int*[n];
		for (i = 0; i < n; i = i + 1) {
			data[i] = i;
			refs[i] = &data[i];
		}
		if (r != 0) {
			*r = *r + n;
		}
	}

	~Buffer() {
		int i;
		for (i = 0; i < size; i = i + 1) {
			if (refs[i] != 0) {
				*refs[i] = *refs[i] + 1;
			}
		}
		delete [] refs;
		delete [] data;
	}

	int sum() {
		int i;
		int s = 0;
		for (i = 0; i < size; i = i + 1) {
			s = s + *refs[i];
		}
		return s;
	}
};

int scan(Buffer **bb, int **pp, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (i % 2 == 0) {
			s = s + (*bb)->sum();
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int x;
	int y;
	int *p;
	int *q;
	int **pp;
	int **qq;
	Buffer *b;
	Buffer **bb;
	int total;

	x = 5;
	y = 7;
	p = &x;
	q = &y;
	pp = &p;
	qq = &q;

	b = new Buffer(4, p);
	bb = &b;

	total = scan(bb, qq, 3);
	total = total + *b->data;
	**pp = **pp + 1;
	**qq = **qq + 2;

	if (total > 0) {
		if (total % 2 == 0) {
			total = total + *q;
		} else {
			total = total + *p;
		}
	} else {
		total = 0;
	}

	gtotal = total;

	delete *bb;

	return 0;
}
