// <svf-test-suite>@64f017e/src/complex_tests/test-globalstruct.c

int g1;
int g2;

const struct {
    int *p1;
    int *p2;
} obj = { &g1, &g2 };

int f() {
    int *p = obj.p1;
    return *p;
}

int main(void) {
    f();
    return 0;
}
