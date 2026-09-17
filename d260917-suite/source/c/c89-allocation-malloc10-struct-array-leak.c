// <svf-test-suite>@64f017e/src/mem_leak/malloc10.c

#include <stdio.h>


#include <stdlib.h>
struct s_rr_node {
	short xlow; short xhigh; short ylow; short yhigh;
	short ptc_num; short num_edges;
	int *edges;
	short *switches; float R; float C;
};

int main(){
	struct s_rr_node *rr_node;
	int i = 0;
	rr_node = malloc(sizeof(struct s_rr_node)*10);
	rr_node[i].edges = malloc(10);
	printf("%p",(void*)rr_node);
	free(rr_node[i].edges);
	free(rr_node);
	return 0;
}
