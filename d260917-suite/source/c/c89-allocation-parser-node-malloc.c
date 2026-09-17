// <svf-test-suite>@64f017e/src/basic_c_tests/spec-parser.c

#include <stdlib.h>

typedef struct X_node_struct X_node;
struct X_node_struct {
    int* string;
    X_node *next;
};

typedef struct Word_struct Word;
struct Word_struct {
    int* string;
    X_node * x;
};

typedef struct clause_struct Clause;
struct clause_struct {
    Clause * next;
};

void * xalloc(int size) {
	return (void *) malloc(1000);
}

Word sentence[250];

void build_clause() {
    Clause *c=NULL, *c1, *c2;

	c1 = (Clause*) xalloc(sizeof (Clause));
	while(c1 != NULL) {
		c2 = c1->next;
		c1->next = c;
		c = c1;
		c1 = c2;
	}

}

void special_string(int i) {
    X_node * e;

	sentence[i].x = (X_node *) xalloc(sizeof(X_node));
	for (e = sentence[i].x; e != NULL; e = e->next) {
	    e->string = sentence[i].string;
	}
}

int main() {
	build_clause();
	special_string(10);
	return 0;
}
