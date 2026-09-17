// <original>

#include <typeinfo>

int gcount;

struct Shape {
	int *x;
	int **xx;

	Shape(int *a, int **b) {
		x = a;
		xx = b;
		gcount = gcount + 1;
	}

	virtual ~Shape() {
		if (x != 0) {
			*x = *x + 1;
		}
	}

	virtual int area() {
		return *x;
	}
};

struct Circle : Shape {
	int *r;

	Circle(int *a, int **b, int *c) : Shape(a, b) {
		r = c;
	}

	virtual int area() {
		return *r * *r;
	}
};

struct Square : Shape {
	int *s;

	Square(int *a, int **b, int *c) : Shape(a, b) {
		s = c;
	}

	virtual int area() {
		return *s + *s;
	}
};

int measure(Shape **sp, int **pp, int **qq, int n) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		Shape *cur = sp[i];
		Circle *cp = dynamic_cast<Circle *>(cur);
		if (cp != 0) {
			s = s + *cp->r;
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
	int *p;
	int *q;
	int *r;
	int **pp;
	int **qq;
	Shape *sp;
	Shape **spp;
	Shape *shapes[2];
	Circle *cp;
	Square *sq;
	int total;

	a = 1;
	b = 2;
	c = 3;
	p = &a;
	q = &b;
	r = &c;
	pp = &p;
	qq = &q;

	sp = new Circle(p, pp, r);
	spp = &sp;
	shapes[0] = sp;
	shapes[1] = new Square(q, qq, r);

	**pp = **pp + 4;
	*r = *r + *sp->x;

	cp = dynamic_cast<Circle *>(*spp);
	if (cp != 0) {
		*cp->r = *cp->r + 1;
	}

	sq = dynamic_cast<Square *>(shapes[0]);
	if (sq != 0) {
		*sq->s = *sq->s + 2;
	} else {
		**qq = **qq + 1;
	}

	total = measure(shapes, pp, qq, 2);
	total = total + *p + *q + *r;

	if (total > 0) {
		total = total - **qq;
	} else {
		total = total + **pp;
	}

	delete shapes[0];
	delete shapes[1];

	return 0;
}
