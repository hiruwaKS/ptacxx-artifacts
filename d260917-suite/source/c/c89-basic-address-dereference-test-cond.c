// <svf-test-suite>@64f017e/src/complex_tests/test-cond.c

char g1;
char g2;

static int cond(void) { return 0; }

void f1(char **p) {

        if (cond()) *p = &g2;
}

char *f2() {
        char *p = &g1;
            f1(&p);
                return p;
}

int main(void) {
        f2();
        return 0;
}
