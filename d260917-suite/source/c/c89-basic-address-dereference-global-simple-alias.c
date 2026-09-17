// <svf-test-suite>@64f017e/src/basic_c_tests/global-simple.c

int a_int = 10;
int* p_int = &a_int;
int** pp_int = &p_int;

int main() {
	int b_int = a_int;
	int* q_int = p_int;
	int** qq_int = pp_int;

	return 0;
}
