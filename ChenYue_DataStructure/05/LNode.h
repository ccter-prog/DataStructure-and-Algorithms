#ifndef LNode_H
#define LNode_H

struct LNode
{
    int Data[10];
    int Last;
};

typedef struct LNode *List;

List MakeEmpty();
int Find(const int X, List PtrL);
int insert(List PtrL, int num);
void del(List PtrL);

#endif