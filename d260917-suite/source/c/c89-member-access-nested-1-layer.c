// <svf-test-suite>@64f017e/src/basic_c_tests/struct-nested-1-layer.c

struct MyStruct2 {
	int * f3;
	int * f4;
};

struct MyStruct1 {
	int *f1;
	struct MyStruct2 f2;
};

int main()
{
	struct MyStruct1 ms;
	struct MyStruct1 *pms1;
	struct MyStruct2 *pms2;
	int a, b, c;
	ms.f1 = &c;
	ms.f2.f3 = &a;
	ms.f2.f4 = &b;
	pms1 = &ms;
	pms2 = &ms.f2;

	return 0;
}
