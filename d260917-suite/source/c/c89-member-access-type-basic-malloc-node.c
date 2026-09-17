// <svf-test-suite>@64f017e/src/objtype_tests/type-basic.c

#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;
int main() {
    Node* head1 = malloc(sizeof(Node));
    head1->data = 1;

    free(head1);
    return 0;
}
