// <svf-test-suite>@64f017e/src/basic_c_tests/struct-field-multi-dereference.c

struct MyStruct {
	int * f1;
	struct MyStruct *f2;
};

int main() {
	struct MyStruct *p, *q;
	struct MyStruct ms1, ms2;
	int x;
	p = &ms1;
	q = &ms1;
	ms1.f2 = &ms2;
	p->f2->f1 = &x;

	return 0;
}
