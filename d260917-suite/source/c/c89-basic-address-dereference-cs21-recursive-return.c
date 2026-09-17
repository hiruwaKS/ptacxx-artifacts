// <svf-test-suite>@64f017e/src/cs_tests/cs21.c

int a;
static int depth = 0;
int *foo(int *x){
   int*z = x;
   int* y;
   if(x && depth < 5){
    depth++;
    y = foo(z);
   }
   else
    y = x;

    return y;

}

int main(){
 int*p;
 p = &a;

 foo(p);

 return 0;
}
