// <original>

struct Shape {
	int *px;
	int **ppy;

	Shape(int *x, int **y) {
		px = x;
		ppy = y;
	}

	virtual int area() {
		return *px;
	}

	virtual int scale(int f) {
		return *px * f;
	}
};

struct Square : Shape {
	int *side;

	Square(int *x, int **y, int *s) : Shape(x, y) {
		side = s;
	}

	virtual int area() {
		return *side * *side;
	}

	virtual int scale(int f) {
		return *side * f + **ppy;
	}
};

struct Rect : Shape {
	int *w;
	int *h;

	Rect(int *x, int **y, int *a, int *b) : Shape(x, y) {
		w = a;
		h = b;
	}

	virtual int area() {
		return *w * *h;
	}
};

int total_area(Shape **shapes, int n, int **pp) {
	int i;
	int s = 0;
	for (i = 0; i < n; i = i + 1) {
		if (shapes[i] != 0) {
			s = s + shapes[i]->area();
		} else {
			s = s + **pp;
		}
	}
	return s;
}

int main() {
	int x = 2;
	int y = 3;
	int a = 4;
	int b = 5;
	int *p = &x;
	int *q = &y;
	int *r = &a;
	int *t = &b;
	int **pp = &p;
	int **qq = &q;
	Square sq(p, pp, r);
	Rect rc(q, qq, r, t);
	Shape *s1 = &sq;
	Shape *s2 = &rc;
	Shape *shapes[3];
	int total;

	shapes[0] = s1;
	shapes[1] = s2;
	shapes[2] = 0;

	**pp = **pp + 1;
	*s2->px = *s2->px + 2;

	total = total_area(shapes, 3, qq);
	total = total + s1->scale(2) + s2->area();

	if (total > 0) {
		total = total + **pp;
	} else {
		total = total - **qq;
	}

	return 0;
}
