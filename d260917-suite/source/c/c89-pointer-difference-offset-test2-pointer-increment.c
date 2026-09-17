// <svf-test-suite>@64f017e/src/complex_tests/test2.c

char * f(char * a) {
   char * b ;

   b = a;
    *(b++) = 1;
   return b;
}

void g(char * a) {
    *a = 0;
    f(a);
}

int main (){
    char a[10];
    char * c;

    f(a);
    g(a);
}
