// <svf-test-suite>@64f017e/src/cs_tests/recur2.c

int* x,y;
void f(int *m){

	int *n;
	if(y==1){
		n=&y;

		f(n);
	}
}

int main(){
	x=&y;
	f(x);
}
