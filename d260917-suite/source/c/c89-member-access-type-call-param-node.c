// <svf-test-suite>@64f017e/src/objtype_tests/type-call.c

#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void foo(Node* node) {
    node->data = 1;
}

int main() {
    Node* head1 = malloc(sizeof(Node));
    foo(head1);
    free(head1);
    return 0;
}
