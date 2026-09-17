// <svf-test-suite>@64f017e/src/fs_tests/array_alias_4.c

struct MyStruct {
	int * f1;
	int * f2;
};

int main() {
	struct MyStruct s[2];
	int a,b,c,d;
	s[0].f1 = &a, s[0].f2 = &c;

	if (a)
		s[1].f1 = &c;

	return 0;
}
