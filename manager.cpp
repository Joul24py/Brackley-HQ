// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

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
void MemoryInput(treeElement element, int id, int memory, int quantum);

// Main function
int main()
{
    // Variables and parameters used in random process generation
    int processProbability = 40;
    int processGenerator, processId = 0, memoryLimit = 1000, memoryGenerator, quantumLimit = 20, quantumGenerator, quantumSystem = 3;
    
    srand(time(NULL));
    
    while(1)
    {
        processGenerator = rand() % 100;
        if(processGenerator <= processProbability)
        {
            processId++;
            //memoryGenerator = rand() % memoryLimit;
            quantumGenerator = rand() % quantumLimit;
            printf("Generado proceso (%d)\n", processGenerator);
            printf("Id: %d\n", processId);
            scanf("%d", &memoryGenerator);
            printf("Memoria: %d\n", memoryGenerator);
            printf("Cuanto: %d\n\n", quantumGenerator);

            MemoryInput(p, processId, memoryGenerator, quantumGenerator);
            PrintMemory(p);
            getchar();
        }
        Sleep(1000);
    }
    
    // Testing the memory functionalities
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

    printf("\nDESFRAGMENTACION\n");
    DefragmentMemory(p->leftSon->rightSon);
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

void DefragmentMemory(treeElement element) // The defragmentation process is done using the common father as the element in the arguments
{
    delete element->rightSon;
    delete element->leftSon;

    element->leftSon = NULL;
    element->rightSon = NULL;
}

void MemoryInput(treeElement element, int id, int memory, int quantum)
{
    treeElement a;
	a = element;

    printf("a\n");
	
    if(a->leftSon != NULL)
    {
        printf("b\n");
        MemoryInput(a->leftSon, id, memory, quantum);
        printf("c\n");
        MemoryInput(a->rightSon, id, memory, quantum);
        printf("d\n");
    }
    else
    {
        printf("e\n");
        printf("%p <- {This: %p [%d, %d, %d]} -> Left: %p Right: %p\n",a->father, a, a->processId, a->freeMemory, a->quantumProcess, a->leftSon, a->rightSon);
        if(memory > a->freeMemory)
        {
            printf("f\n");
            return;
        }
        else
        {
            printf("g\n");
            if(memory > ((a->freeMemory) / 2))
            {
                printf("h\n");
                a->processId = id;
                a->freeMemory = memory;
                a->quantumProcess = quantum;
            }
            else
            {
                printf("i\n");
                FragmentMemory(a);
            }
        }
    }
}