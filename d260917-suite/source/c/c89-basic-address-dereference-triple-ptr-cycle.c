// <svf-test-suite>@64f017e/src/fs_tests/pcycle1.c

int main(){
    int ***m,**n,*z,*y,z1,y1;

    m=&n;
    n=&z;
    *m=&y;

    z=&z1;
    y=&y1;
    ***m=10;
    z=**m;

}
