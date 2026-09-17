// <svf-test-suite>@64f017e/src/basic_c_tests/struct-nested-array1.c

struct InnerArrayStruct {
	int f1[100];
};

struct ArrayStruct {
	int f1;
	char f2;
	struct InnerArrayStruct f3;
	int f4;
};

int main() {
	struct ArrayStruct* p;
	struct ArrayStruct s;
	int* q;

	p = &s;
	q = &s.f3.f1[40];

	return 0;
}
