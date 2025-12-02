#pragma once

#define MAX 10

typedef struct seqlist
{
    int data[MAX];
    int length;
} SList;

void init(SList *p);
void printList(const SList *p);
int insert(SList *p, const int k, const int x);
int erase(SList *p, const int k, int *px);