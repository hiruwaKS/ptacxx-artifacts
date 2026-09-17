// <svf-test-suite>@64f017e/src/fs_tests/global_1.c

int x, y; int *p = &x; int *q = &y;
int **pp = &p; int**qq = &q;

void foo() {

}
void bar() {
     qq = &q;
     q = &x;
}
int main() {
    foo();
    bar();

}
