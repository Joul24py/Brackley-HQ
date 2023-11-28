// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

// General definitions for the process manager structure functions
struct nodeQueue
{
	struct nodeQueue *previous;
	int processId;
    int freeMemory;
    int quantumProcess;
	struct nodeQueue *next;
};

typedef struct nodeQueue *queueElement;

queueElement p = NULL; // Variable that stores the beginning of the queue (or null of there's no values)
queueElement q; // Variable that helps linking the one before the last node with the last node
queueElement r; // Variable that stores the end of the queue
queueElement s; // Variable that stores the position of the system quantum (on which is going to decrement the process quantum)

// Defining process manager functions
void AddProcess(int id, int memory, int quantum);
void PrintQueue();
void Advance(int quantumSystem);


// Main function
int main()
{
    setlocale(LC_ALL,"");
    srand(time(NULL));

    // Variables and parameters used in random process generation
    /*
        processProbability: Percentage of probability set by the user of generating a process each second (number between 0 and 100)
        processGenerator: Random number generated by the PC that determines if the process is generated in that second or not
        processId: Id of the process generated predetermined by the PC
        memoryLimit: Max memory that can be randomly generated for a process set by the user
        memoryGenerator: Random number generated by the PC that determines the memory of that process
        quantumLimit: Max quantum value that can be randomly generated for a process set by the user
        quantumGenerator: Random number generated by the PC that determines the quantum value of that process
        quantumSystem: The value of the quantum system set by the user
    */
    int processProbability = 40;
    int processGenerator, processId = 0, memoryLimit = 1000, memoryGenerator, quantumLimit = 20, quantumGenerator, quantumSystem = 3;
    
    while(1)
    {
        Advance(quantumSystem);

        processGenerator = rand() % 100;
        if(processGenerator <= processProbability)
        {
            processId++;
            memoryGenerator = rand() % memoryLimit + 1;
            quantumGenerator = rand() % quantumLimit + 1;
            //printf("Generado proceso (%d)\n", processGenerator);
            //printf("Id: %d\n", processId);
            //printf("Memoria: %d\n", memoryGenerator);
            //printf("Cuanto: %d\n\n", quantumGenerator);

            AddProcess(processId, memoryGenerator, quantumGenerator);
        }
        system("CLS");
        PrintQueue();
        Sleep(1500);
    }
}

// Code for the process manager structure functions
void AddProcess(int id, int memory, int quantum)
{
    if(p == NULL)
    {
        // Adding the first element of the stack
        p = new(struct nodeQueue);
        p->previous = p;
        p->processId = id;
        p->freeMemory = memory;
        p->quantumProcess = quantum;
        p->next = p;
        q = p;
        r = p;
    }
    else
    {
        // Adding elements when there is already one element in the queue
        r = new(struct nodeQueue);
        r->previous = q;
        r->processId = id;
        r->freeMemory = memory;
        r->quantumProcess = quantum;
        r->next = p;
        q->next = r;
        q = r;
        p->previous = r;
    }
}

void PrintQueue()
{
    queueElement a;
    a = p;
    if(p == NULL)
    {
        printf("Empty list\n");
    }
    else
    {
        do
        {
            printf("%p <- %p: [%d  %d  %d] -> %p\n", a->previous, a, a->processId, a->freeMemory, a->quantumProcess, a->next);
            a = a->next;
        }
        while (a != p);
    }
}

void Advance(int quantumSystem)
{
    if(p == NULL)
    {
        printf("Empty list\n");
        s = NULL;
    }
    else
    {
        if(s == NULL)
        {
            s = p;
        }

        //printf("Evaluando %p <- %p: [%d  %d  %d] -> %p\n", s->previous, s, s->processId, s->freeMemory, s->quantumProcess, s->next);
        s->quantumProcess = s->quantumProcess - quantumSystem;
        //printf("Evaluado %p <- %p: [%d  %d  %d] -> %p\n", s->previous, s, s->processId, s->freeMemory, s->quantumProcess, s->next);
        //getchar();
        if (s->quantumProcess <= 0)
        {
            // Entering here means this process is done. So here it's deleted from the structure
            if(s->next == s) // Case 1: When it's just one element
            {
                delete s;
                s = NULL;
                p = NULL;
            }
            else // Case 2: When the structure has more than one element
            {
                queueElement a = s; // Auxiliar for deleting elements
                queueElement sBefore = s->previous;
                queueElement sAfter = s->next;

                sBefore->next = sAfter;
                sAfter->previous = sBefore;
                s = s->next;

                if(p == a)
                {
                    p = p->next;
                }

                if(r == a)
                {
                    r = r->previous;
                    q = r;
                }

                delete a;
            }
        }
        else
        {
            if(s != NULL)
            {
                s = s->next;
            }
        }
    }
}