// <svf-test-suite>@64f017e/src/complex_tests/test-recursive0.c

#include <stdlib.h>
struct list {
    struct list * prev;
};

struct list * construct (struct list * head) {
    int i = 0;
   if (i > 0) {
       struct list * tmp = malloc(sizeof(struct list));
       head->prev = tmp;
       return construct (tmp);

    }
    return head;
}
int main () {
    struct list * head;
    head = malloc(sizeof(struct list));
    head->prev = 0;

    head = construct (head);
    head = head->prev;
}
