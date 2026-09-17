// <svf-test-suite>@64f017e/src/mem_leak/malloc9.c

#include <stdlib.h>
struct s_rr_node {
	short xlow; short xhigh; short ylow; short yhigh;
	short ptc_num; short num_edges;
	int *edges;
	short *switches; float R; float C;
};

struct s_rr_node *rr_node;

int* alloc(){

	return malloc(10);
}

int main(){

	int i = 0;
	rr_node = malloc(sizeof(struct s_rr_node) * 10);
	rr_node[i].edges = alloc();
	free(rr_node[i].edges);
	free(rr_node);
	return 0;
}
