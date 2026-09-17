// <svf-test-suite>@64f017e/src/cs_tests/recur4.c

int **x, *y;
int z;
void f(int **p);
int main(){
	x = &y;
	f(x);
}

void f(int **p){
	int k;
	y = &k;
	if (z){
		*p = &z;

		f(p);
	}

}
