// <original>

int gsum;

struct Reader {
	int *in;
	int **inp;

	Reader(int *a, int **b) {
		in = a;
		inp = b;
	}

	virtual ~Reader() {
		if (in != 0) {
			*in = *in + 1;
		}
	}

	virtual int read() {
		return *in;
	}
};

struct Writer {
	int *out;
	int **outp;

	Writer(int *a, int **b) {
		out = a;
		outp = b;
	}

	virtual ~Writer() {
		if (out != 0) {
			*out = *out + 1;
		}
	}

	virtual int write() {
		return *out;
	}
};

struct Duplex : Reader, Writer {
	int *buf;

	Duplex(int *a, int **b, int *c, int **d, int *e)
		: Reader(a, b), Writer(c, d) {
		buf = e;
	}

	virtual int read() {
		return *buf + *in;
	}
};

int route(Reader **rp, Writer **wp, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		Reader *cur = rp[i];
		Writer *w = dynamic_cast<Writer *>(cur);
		if (w != 0) {
			s = s + w->write();
		} else if (wp[i] != 0) {
			s = s + wp[i]->write();
		} else if (i == 0) {
			s = s + **pp;
		} else {
			s = s + **qq;
		}
	}
	return s;
}

int main() {
	int a;
	int b;
	int c;
	int d;
	int e;
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	Duplex *dp;
	Duplex **dpp;
	Reader *reader;
	Writer *writer;
	Reader *readers[2];
	Writer *writers[2];
	int total;

	a = 1;
	b = 2;
	c = 3;
	d = 4;
	e = 5;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	dp = new Duplex(p, pp, q, qq, r);
	dpp = &dp;
	reader = dp;
	writer = dynamic_cast<Writer *>(reader);
	readers[0] = reader;
	writers[0] = writer;
	readers[1] = new Reader(p, pp);
	writers[1] = new Writer(q, qq);

	**pp = **pp + 4;
	**qq = **qq + d + e;
	*writer->out = *writer->out + 5;
	*reader->in = *reader->in + *dp->buf;

	total = route(readers, writers, pp, qq, 2);

	if (total > 0) {
		total = total + *p;
	} else {
		total = total + *q;
	}

	delete *dpp;
	delete readers[1];
	delete writers[1];

	return 0;
}
