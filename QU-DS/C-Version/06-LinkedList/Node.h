#pragma once

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void init(Node **phead);
int getLength(const Node *head);
void printList(const Node *head);
int insert(Node **phead, const int k, const int x);
Node *createNode(const int x);
int removeNode(Node **phead, const int k, int *x);