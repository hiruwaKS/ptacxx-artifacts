// <svf-test-suite>@64f017e/src/basic_c_tests/struct-instance-return.c

struct MyStruct {
	int* f1;
	char f2;
};

int x, y;

struct MyStruct foo() {
	struct MyStruct m;
	m.f1 = &x;
	return m;
}

int main() {
	struct MyStruct m;
	m = foo();

	return 0;
}
