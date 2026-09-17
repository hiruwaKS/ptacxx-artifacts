// <svf-test-suite>@64f017e/src/basic_c_tests/global-funptr.c

int x, y;
int* p;

void foo() {
	p = &y;
}

struct MyStruct {
	void (*fp)();
	int* f1;
};

struct MyStruct context = { foo, &x };

int main()
{
	(*context.fp)();
	int* q = p;

	return 0;
}
