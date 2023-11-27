// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// General definitions for the memory manager structure functions
struct nodeTree
{
	struct nodeTree *father;
	int processId;
    int freeMemory;
    int quantumProcess;
	struct nodeTree *leftSon;
    struct nodeTree *rightSon;
};

typedef struct nodeTree *treeElement;

treeElement p = NULL;
treeElement q;
treeElement r;

// Defining memory manager functions
void InitializeMemory();
void PrintMemory(treeElement element);
void FragmentMemory(treeElement element);
void DefragmentMemory(treeElement element);

// Main function
int main()
{
    InitializeMemory();
    PrintMemory(p);

    printf("\nFRAGMENTACION\n");
    FragmentMemory(p);
    PrintMemory(p);

    printf("\nFRAGMENTACION\n");
    FragmentMemory(p->leftSon);
    PrintMemory(p);

    printf("\nFRAGMENTACION\n");
    FragmentMemory(p->leftSon->rightSon);
    PrintMemory(p);

    getchar();
    return 0;
}

// Code for the memory manager structure functions
void InitializeMemory()
{
    p = new(struct nodeTree);
    p->father = NULL;
    p->processId = 0;
    p->freeMemory = 8192;
    p->quantumProcess = 0;
    p->leftSon = NULL;
    p->rightSon = NULL;
    q = p;
    r = p;
}

void PrintMemory(treeElement element)
{
	treeElement a;
	a = element;
	
    if(a->leftSon != NULL)
    {
        PrintMemory(a->leftSon);
        PrintMemory(a->rightSon);
    }
    else
    {
        printf("%p <- {This: %p [%d, %d, %d]} -> Left: %p Right: %p\n",a->father, a, a->processId, a->freeMemory, a->quantumProcess, a->leftSon, a->rightSon);
    }
}

void FragmentMemory(treeElement element)
{
    treeElement left = new(struct nodeTree);
    left->father = element;
    left->processId = 0;
    left->freeMemory = element->freeMemory/2;
    left->quantumProcess = 0;
    left->leftSon = NULL;
    left->rightSon = NULL;

    treeElement right = new(struct nodeTree);
    right->father = element;
    right->processId = 0;
    right->freeMemory = element->freeMemory/2;
    right->quantumProcess = 0;
    right->leftSon = NULL;
    right->rightSon = NULL;

    element->leftSon = left;
    element->rightSon = right;
}