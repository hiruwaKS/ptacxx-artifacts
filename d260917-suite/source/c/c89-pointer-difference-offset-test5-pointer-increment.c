// <svf-test-suite>@64f017e/src/complex_tests/test5.c

char * f(char * a) {
   char * b ;

   b = a;
    *(b++) = 1;
   return b;
}

char * g(char * a) {
    *a = 0;
    return f(a);
}

int main (){
    char a[10];
    char b[20];
    char * c;

    f(a);
    c = f(b);
    g(c);
}
