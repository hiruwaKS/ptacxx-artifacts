// <svf-test-suite>@64f017e/src/objtype_tests/type-ret.c

#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void* malloc_wrapper() {
    return malloc(sizeof(Node));
}
int main() {
    Node* head1 = malloc_wrapper();
    head1->data = 1;

    free(head1);
    return 0;
}
