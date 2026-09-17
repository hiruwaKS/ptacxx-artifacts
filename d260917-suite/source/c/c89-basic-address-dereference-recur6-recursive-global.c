// <svf-test-suite>@64f017e/src/cs_tests/recur6.c

int y,z;
int *x = &y;

void f();

int main(){
    f();
    *x=100;
}

void f(){

    if(z){
	x=&y;
	f();
	x=&z;
	f();

    }

}
