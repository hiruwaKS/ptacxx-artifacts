// <svf-test-suite>@64f017e/src/complex_tests/test-linklist1.c

#include <stdlib.h>

struct list {
    int flag;
    struct list * next;
    struct list * prev;
};

struct list * construct (unsigned idx) {
    struct list * head;
    unsigned i = 0;
    head = malloc(sizeof(struct list));
    head->next = 0;
    head->prev = 0;
    head->flag = -1;
    for (i =0; i<idx; i++){
        struct list * cur = malloc(sizeof(struct list));
        cur->flag = idx;
        cur->next = head;
        cur->prev = 0;
        head->prev = cur;
        head = cur;
    }
    return head;
}

struct list * randomwalk (struct list * head) {
    struct list * cur = head;
    int guard = 0;

    while (cur != 0 && cur->flag != 0 && guard < 1000) {
        if (cur->flag > 3) {
            if (cur->prev == 0)
                break;
            cur = cur->prev;
        }
        else {
            cur = cur->next;
        }
        guard++;
    }
    return cur;
}

int main () {
    struct list * head;
    struct list * head1;
    head = construct (10);

    head1 = randomwalk (head);
}
