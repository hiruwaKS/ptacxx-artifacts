// <svf-test-suite>@64f017e/src/basic_c_tests/struct-twoflds.c

struct IntChar {
	int f1;
	char f2;
};

struct CharInt {
	char f1;
	int f2;
};

int main() {
	struct IntChar* pint1, *pint2;
	struct IntChar s;
	pint1 = &s;
	pint2 = &s;

	struct CharInt* qint1, *qint2;
	struct CharInt t;
	qint1 = &t;
	qint2 = &t;

	return 0;
}
