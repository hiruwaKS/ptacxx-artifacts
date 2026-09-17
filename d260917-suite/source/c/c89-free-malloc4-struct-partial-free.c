// <svf-test-suite>@64f017e/src/mem_leak/malloc4.c

#include <stdlib.h>
typedef struct network
{
	long feas_tol;
	long pert_val;
	long bigM;
	double optcost;
	int *arcs;
	int *stop;
	int *nodes;
} network_t;

void bar(int* s){
	free(s);
}

void foo(network_t* net){
	int *p = malloc(10);
	int *q = malloc(10);
	net->arcs = p;
	net->stop = q;
	bar(net->arcs);

}

int main(){

	network_t net;
	foo(&net);
	free(net.stop);
	return 0;
}
