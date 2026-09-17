// <svf-test-suite>@64f017e/src/complex_tests/swap-global.c

char * p1, * p2;
void swap(char **a, char **b) {
   char * c;
   c = *a;
   *a = * b;
   *b = c;
}

int main (){
    char b[20];
    char a[20];
    char * pa, *pb;

    p1 = a;
    p2 = b;

    swap (&p1, &p2);
    pa = p1;
    pb = p2;
}
