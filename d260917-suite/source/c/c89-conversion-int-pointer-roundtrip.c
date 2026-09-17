// <svf-test-suite>@64f017e/src/basic_c_tests/int2pointer.c

struct MyStruct {
	int f1;
	int f2;
};

int main() {
	struct MyStruct ms;
	int *p, *q;
	p = &(ms.f1);

	int addr = (int)p;

	q = (int*)addr + 1;

	return 0;
}
