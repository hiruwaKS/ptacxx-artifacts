// <svf-test-suite>@64f017e/src/objtype_tests/type-copy.c

#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;
int main() {
    Node * head1 = malloc(sizeof(Node));

    Node* head2 = head1;
    head2->data = 1;

    free(head2);
    return 0;
}
