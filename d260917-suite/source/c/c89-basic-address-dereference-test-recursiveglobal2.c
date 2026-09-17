// <svf-test-suite>@64f017e/src/complex_tests/test-recursiveglobal2.c

char *p;
char *q;

void recursion (unsigned);
void swap(unsigned);

void swap(unsigned i) {
    char * c = p;
    p = q;
    q = c;

    recursion (i - 1);
}

void recursion(unsigned i) {
    if (i == 0) {
        return;
    }
    swap(i);
}

int main () {
    char a[10];
    char b[10];

    p = a;
    q = b;

    recursion(10);
}
