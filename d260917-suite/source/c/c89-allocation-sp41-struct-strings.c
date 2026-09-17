// <svf-test-suite>@64f017e/src/mem_leak/sp41.c

#include <string.h>


#include <stdlib.h>
typedef struct _S {
	char *p1;
	char *p2;
} S;

int main(void) {
	S *p;
	char str1[10] = "STRING 1";
	char str2[10] = "STRING 2";

	p = (S*) malloc(sizeof(S));
	if (p == NULL)
		return -1;

	p->p1 = (char *) malloc(sizeof(char) * 10);
	if (p->p1 == NULL) {
		free(p);
		return -1;
	}

	p->p2 = (char *) malloc(sizeof(char) * 10);
	if (p->p2 == NULL) {
		if (p->p1 != NULL)
			free(p->p1);
		free(p);
		return -1;
	}

	strcpy(p->p1, str1);
	strcpy(p->p2, str2);

	free(p->p1);
	free(p->p2);
	free(p);
	return 0;
}
