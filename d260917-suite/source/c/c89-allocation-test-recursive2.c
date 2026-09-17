// <svf-test-suite>@64f017e/src/complex_tests/test-recursive2.c

#include <stdlib.h>
struct list {
    unsigned field;
    struct list * next;
    struct list * prev;
};

struct list * construct1(struct list * head, unsigned);
struct list * construct (struct list * head, unsigned i) {
    if (i > 0) {
        struct list * tmp = malloc(sizeof(struct list));
        tmp->field = 0;
        tmp->next = head;
        head->prev = tmp;
        tmp->prev = 0;

        return construct (tmp, i - 1);

    }
    return construct1(head, 0);
}

struct list * construct1 (struct list * head, unsigned i) {
    if ( i > 0) {
        struct list * list = construct (head, i-1);

        head->next = list;

    }
    return head;
}

struct list * walklist (struct list * input) {
    static int depth = 0;
    struct list * head = input;
    struct list * curr;
    int guard;
    if (input == 0)
        return 0;
    if (depth > 16)
        return input;
    depth++;

    guard = 0;
    while (head->prev != 0 && guard++ < 1000)
        head = head->prev;

    guard = 0;
    while (head->next && guard++ < 1000) {
        curr = head;
        curr->field ++;

        if (curr->field > 5)
            head = head->next;
        else
            head = head->prev;
        if (head == 0)
            break;
        head->prev = walklist (head);
        head->next = curr;
    }
    depth--;
    return head;
}

int main () {
    struct list * head;

    head = malloc(sizeof(struct list));
    head->field = 0;
    head->next = 0;
    head->prev = 0;

    head = construct (head, 10);
    head = walklist (head);
}
