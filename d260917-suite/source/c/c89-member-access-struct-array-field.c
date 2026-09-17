// <svf-test-suite>@64f017e/src/basic_c_tests/struct-array.c

struct ArrayStruct {
	int f1;
	char f2;
	int f3[100];
	int f4;
};

int main() {
	struct ArrayStruct* p;
	struct ArrayStruct s;
	int* q;

	p = &s;
	q = &s.f3[40];

	return 0;
}
