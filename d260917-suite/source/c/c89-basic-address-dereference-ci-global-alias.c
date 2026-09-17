// <svf-test-suite>@64f017e/src/basic_c_tests/CI-global.c

int global;
int *p_global;

void foo() {
	p_global = &global;
}

int main() {
	int *p_local;
	p_local = &global;
	foo();

	return 0;
}
