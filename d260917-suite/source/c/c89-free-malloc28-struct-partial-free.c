// <svf-test-suite>@64f017e/src/mem_leak/malloc28.c

#include <stdlib.h>
typedef struct network{

	int* arcs;
	int* stop_arcs;

}network;

struct network* net;

void func(struct network* net){

	int* arc = malloc(10);

	net->arcs = arc;
	net->stop_arcs = malloc(10);

}

int main(){

	struct network* net;
	net = malloc(20);
	func(net);

	free(net->arcs);
	free(net->stop_arcs);
	free(net);

}
