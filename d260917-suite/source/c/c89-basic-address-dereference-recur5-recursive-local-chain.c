// <svf-test-suite>@64f017e/src/cs_tests/recur5.c

int* x, x1;
void f(int **m){
int **n,*y,*k,z,r;
   n = &y;
   y = &z;
   if(z==1){
	*n=&r;

	k = *n;

	f(n);
   }
}

int main(){
	x=&x1;
	f(x);
}
