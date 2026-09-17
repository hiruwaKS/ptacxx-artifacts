// <svf-test-suite>@64f017e/src/complex_tests/test-recursiveglobal1.c

char *p;
char *q;

char swap() {
    char * c = p;
    p = q;
    q = c;
}

void recursion(unsigned i) {
    if (i == 0) {
        return;
    }
    swap();
    recursion(i - 1);
}

int main () {
    char a[10];
    char b[10];

    p = a;
    q = b;

    recursion(10);
}
