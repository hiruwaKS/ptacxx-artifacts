// <svf-test-suite>@64f017e/src/basic_c_tests/global-call-twoparms.c

struct MyStruct {
	int f1;
	void (*fp)(int**, int**);
};

struct MyStruct global;
int x, y;

void foo(int** pp, int** qq) {
	*pp = &x;
	*qq = &y;
}

void bar(int** pp, int** qq) {
	*pp = &x;
	*qq = &x;
}

void init() {
	global.fp = foo;
}

void init2() {
	global.fp = bar;
}

void run(int** pp, int**qq) {
	(*global.fp)(pp, qq);
}

int main() {
	int *p, *q;
	int **pp, **qq;
	pp = &p;
	qq = &q;
	init();
	run(pp, qq);

}
