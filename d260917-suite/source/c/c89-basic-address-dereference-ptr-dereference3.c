// <svf-test-suite>@64f017e/src/basic_c_tests/ptr-dereference3.c

void foo(int q){
  int i = 10;
  int k = i;

}
int main(){

int *s,*r,*x,**y,t,z,k;
	s = &t;
	r = &z;
	y = &r;
	s = r;

	x = *y;

	foo(k);
return 0;
}
