// <svf-test-suite>@64f017e/src/mem_leak/sp6.c

#include <stdlib.h>
typedef struct _list {
	    struct _list *next;
} List, *list;

list make_list(int n) {
	  int i;
	  list hd = (list)malloc(sizeof(List));
	  list p = hd;
	  hd->next = 0;

			    return hd;
}

void free_list(list hd) {
	    list p;
		    while (hd != 0) {
		      p = hd->next;
              free(hd);
              hd = p;
            }
}

int main(void) {
    list l = make_list(10);
    free_list(l);
    return 0;
}
