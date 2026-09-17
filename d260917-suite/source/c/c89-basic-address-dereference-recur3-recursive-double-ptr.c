// <svf-test-suite>@64f017e/src/cs_tests/recur3.c

int x, *y, z;
void f(int **m);
int main(){

	int **a = &y;

	f(a);

}

void f(int **m){
	if(x){
		*m = &x;

		f(m);
	}
	else{
		*m = &z;

	}

}
