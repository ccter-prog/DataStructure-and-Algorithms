#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

void init(Node **phead)
{
    *phead = NULL;
}

int getLength(const Node *head)
{
    int ret = 0;
    while (head)
    {
        ret++;
        head = head -> next;
    }
    return ret;
}

void printList(const Node *head)
{
    while (head)
    {
        printf("%d\n", head -> data);
        head = head -> next;
    }
}

int insert(Node **phead, const int k, const int x)
{
    int ret = 0;
    int count = 1;
    Node *p;
    p = *phead;
    if (!p)
    {
        *phead = createNode(x);
        ret = 1;
    }
    else
    {
        if (count == k)
        {
            Node *temp = createNode(x);
            temp -> next = *phead;
            *phead = temp;
            ret = 1;
        }
        else
        {
            while (p && count < k - 1)
            {
                p = p -> next;
                count++;
            }
            if (p)
            {
                Node *temp = createNode(x);
                if (p -> next)
                {
                    temp -> next = p -> next;
                    p -> next = temp;
                }
                else
                {
                    p -> next = temp;
                }
                ret = 1;
            }
        }
    }
    return ret;
}

Node *createNode(const int x)
{
    Node *ret = (Node *)malloc(sizeof(Node));
    ret -> data = x;
    ret -> next = NULL;
    return ret;
}

int removeNode(Node **phead, const int k, int *x)
{
    int ret = 0;
    int count = 1;
    if (*phead && k == count)
    {
        Node *temp = *phead;
        *phead = temp -> next;  // 如果只有头节点的话那么头指针自然就是空指针，否则的话进入下一个节点
        *x = temp -> data;
        free(temp);
        ret = 1;
    }
    else if (*phead)
    {
        Node *temp = *phead;
        while (temp && count < k - 1)
        {
            temp = temp -> next;
            count++;
        }
        if (temp && temp -> next)
        {
            Node *t = temp -> next;
            temp -> next = t -> next;
            *x = t -> data;
            free(t);
            ret = 1;
        }
    }
    return ret;
}