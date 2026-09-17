// <svf-test-suite>@64f017e/src/complex_tests/test8.c

void f(char ** a) {
   int b[10];
   (*a)++;

   b[10] = 0;
}

int main (){
    char a[10];
    char * c;

    c = a;

    f(&c);
    f(&c);

    *c = 0;
    a[10] = 0;
}
