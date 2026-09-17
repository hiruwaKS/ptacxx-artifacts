// <svf-test-suite>@64f017e/src/fs_tests/pcycle2.c

int main(){

    int **a,**b,**c;
    int k;
    a=&b;
    *a=&c;
    *b=&a;

}
