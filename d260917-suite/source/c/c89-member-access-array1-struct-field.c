// <svf-test-suite>@64f017e/src/fs_tests/array_alias_1.c

struct MyStruct {
	int *f1;
	int *f2;
};

int main() {
	struct MyStruct s[2];
	int x, y;
	s[0].f1 = &x;
	s[1].f2 = &y;

	s[0].f1 = &y;

	return 0;
}
