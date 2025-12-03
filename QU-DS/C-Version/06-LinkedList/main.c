#include "Node.h"
#include <stdio.h>

int main(void)
{
    Node *head;
    init(&head);
    insert(&head, 1, 11);
    insert(&head, 1, 22);
    insert(&head, 2, 33);
    insert(&head, 4, 44);
    insert(&head, 6, 55);
    int x;
    removeNode(&head, 1, &x);
    printList(head);
    printf("x = %d\n", x);
    return 0;
}