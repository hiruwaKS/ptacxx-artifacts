// <svf-test-suite>@64f017e/src/fs_tests/struct_1.c

struct MyStruct {
	int *f1;
	int *f2;
};

int main() {
	struct MyStruct s1, s2;
	int x, y;
	s1.f1 = &x;
	s1.f2 = &y;
	s2.f1 = &y;
	s2.f2 = &x;

	s1.f1 = &y;

	return 0;
}
