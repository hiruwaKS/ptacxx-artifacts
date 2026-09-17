// <svf-test-suite>@64f017e/src/cs_tests/cs20.c

int *obj;
int **x,*b,*w,d;
int **z, *a,*y,c;
void Zulu(int**p, int *q);

void Xray(){
	x = &b;
	w = &d;
	Zulu(x,w);

}

void Yank(){
	z = &a;
	y = &c;
	Zulu(z,y);

}

void Zulu(int**p,int *q){
	*q = 100;
	*p = q;

}

int main(){

	Xray();
	Yank();

}
