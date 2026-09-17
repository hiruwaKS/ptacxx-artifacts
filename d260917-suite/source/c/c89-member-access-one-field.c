// <svf-test-suite>@64f017e/src/basic_c_tests/struct-onefld.c

struct IntStruct {
	int f1;
};

struct CharStruct {
	char f1;
};

int main() {
	struct IntStruct* pint1, *pint2;
	struct IntStruct s;
	pint1 = &s;
	pint2 = &s;

	struct CharStruct* qint1, *qint2;
	struct CharStruct t;
	qint1 = &t;
	qint2 = &t;

	return 0;
}
