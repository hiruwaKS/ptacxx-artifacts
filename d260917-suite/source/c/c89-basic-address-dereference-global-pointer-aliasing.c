// <svf-test-suite>@64f017e/src/non_annotated_tests/intra-procedure/ben7.c

int *p,a,b;
void foo(int* p){

    *p=100;

}
int main(){
    int *q,s,c,d;
    q = &s;
    p=q;
    if(a){
	p =&c;
    }
    else{
	p=&d;
    }
    *p = 100;
    foo(p);

    return 0;
}
