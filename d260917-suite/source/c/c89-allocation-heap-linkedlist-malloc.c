// <svf-test-suite>@64f017e/src/basic_c_tests/heap-linkedlist.c

#include <stdlib.h>
struct Node {
	int *data;
	struct Node *next;
};

void malloc_list(struct Node *p, int num) {
	int *p_data1=NULL, *p_data2=NULL;
	struct Node *p_next = NULL;
    p->data = NULL;
	while (num!=0) {
		p->data = (int *) malloc(sizeof(int));
		p_data1 = p->data;
	    p_next = (struct Node*) malloc(sizeof(struct Node));
		p->next = p_next;
		p_data2 = p->data;
        num--;
	}

}

int main() {
	struct Node* head = (struct Node*) malloc(sizeof(struct Node));
	int num = 4;
	malloc_list(head, num);

	return 0;
}
