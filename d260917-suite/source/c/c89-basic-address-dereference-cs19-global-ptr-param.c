// <svf-test-suite>@64f017e/src/cs_tests/cs19.c

int g;
int* obj = &g;
void Zulu(int**p, int *q);

void Xray(){

	int **x,*b,*w,d;
	x = &b;
	w = &d;
	Zulu(x,w);

}

void Zulu(int**p,int *q){

	*p = q;
    *p = obj;
}

int main(){

	Xray();

}
