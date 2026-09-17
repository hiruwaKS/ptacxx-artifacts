// <svf-test-suite>@64f017e/src/complex_tests/test-recursive.c

#include <stdlib.h>
struct list {
    unsigned field;
    struct list * next;
    struct list * prev;
};

struct list * construct (struct list * head, unsigned i) {
    if (i > 0) {
        struct list * tmp = malloc(sizeof(struct list));
        tmp->field = 0;
        tmp->next = head;
        head->prev = tmp;
        tmp->prev = 0;

        return construct (tmp, i - 1);

    }
    return head;
}

int main () {
    struct list * head;

    head = malloc(sizeof(struct list));
    head->field = 0;
    head->next = 0;
    head->prev = 0;

    head = construct (head, 10);
}
