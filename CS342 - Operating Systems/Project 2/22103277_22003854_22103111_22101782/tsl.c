#include <ucontext.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdbool.h>
#include "tsl.h"

#define STACK_SIZE 1024 * 64
#define TSL_ERROR -1
#define TSL_ANY 0
#define TSL_ERROR -1
#define RUNNING 1
#define READY 2
#define TERMINATED 3

#ifndef REG_EIP
#define REG_EIP 14
#endif

#ifndef REG_ESP
#define REG_ESP 7
#endif

typedef struct TCB
{
    int tid;
    struct TCB *next;
    ucontext_t context;
    void (*start_routine)(void *);
    void *arg;
    char stack[STACK_SIZE];
    bool finished;
} TCB;

TCB *ready_queue = NULL;
TCB *current_thread = NULL;
int last_tid = -1;
void stub_function();
static int current_thread_count = 0;
int salg_global; 

int tsl_init(int salg)
{
    srand(time(NULL));
    salg_global = salg; 

    current_thread = (TCB *)malloc(sizeof(TCB));
    if (!current_thread)
        return TSL_ERROR;

    getcontext(&current_thread->context);
    current_thread->tid = ++last_tid;
    current_thread->next = NULL;
    current_thread->finished = false; 
    return 0;                       
}

void remove_finished_thread(TCB *finished_thread)
{
    if (!finished_thread || ready_queue == NULL)
        return;

    if (ready_queue == finished_thread)
    {
        ready_queue = ready_queue->next;
    }
    else
    {
        TCB *prev = ready_queue;
        while (prev->next && prev->next != finished_thread)
        {
            prev = prev->next;
        }
        if (prev->next)
        {
            prev->next = finished_thread->next;
        }
    }
    finished_thread->next = NULL;
}

int tsl_exit()
{
    current_thread->finished = true; 
    remove_finished_thread(current_thread);

    TCB *next = ready_queue;
    if (next == NULL)
    {
        printf("No more threads to run, exiting.\n");
        
    }
    else
    {
        ready_queue = next->next;          
        TCB *temp_current = current_thread; 
        current_thread = next;             
        swapcontext(&temp_current->context, &next->context); 
    }
    if (current_thread->tid != TID_MAIN)
    {
        current_thread_count--;
    }
    return 0; 
}

int tsl_create_thread(void (*start_routine)(void *), void *arg)
{
    if ((current_thread_count) == TSL_MAXTHREADS - 1)
    {
        exit(TSL_ERROR);
    }

    TCB *new_thread = (TCB *)malloc(sizeof(TCB));
    if (!new_thread)
        return TSL_ERROR; 

    getcontext(&new_thread->context); 

    new_thread->context.uc_link = 0;
    new_thread->context.uc_stack.ss_sp = new_thread->stack;
    new_thread->context.uc_stack.ss_size = sizeof(new_thread->stack);
    new_thread->context.uc_stack.ss_flags = 0;
    new_thread->start_routine = start_routine;
    new_thread->arg = arg;
    new_thread->tid = ++last_tid;
    new_thread->next = NULL;      
    new_thread->finished = false; 

    *(int *)(new_thread->context.uc_stack.ss_sp + new_thread->context.uc_stack.ss_size - 4) = (int)arg;
    *(int *)(new_thread->context.uc_stack.ss_sp + new_thread->context.uc_stack.ss_size - 8) = (int)start_routine;
    new_thread->context.uc_mcontext.gregs[REG_EIP] = (greg_t)stub_function;
    new_thread->context.uc_mcontext.gregs[REG_ESP] = (greg_t)(new_thread->stack + STACK_SIZE - 8);

    if (ready_queue == NULL)
    {
        ready_queue = new_thread;
    }
    else
    {
        TCB *iter = ready_queue;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        iter->next = new_thread;
    }
    current_thread_count++;

    return new_thread->tid; 
}
void stub_function()
{
    TCB *thr = current_thread;
    thr->start_routine(thr->arg);
    tsl_exit();
}

TCB* select_random_thread(TCB* exclude) {
    int eligibleCount = 0;
    TCB* iter = ready_queue;
    TCB* eligibleThreads[current_thread_count];

   
    while (iter) {
        if (iter != exclude && !iter->finished) {
            eligibleThreads[eligibleCount++] = iter;
        }
        iter = iter->next;
    }

    
    if (eligibleCount == 0) {
        return NULL;
    }

    int targetIndex = rand() % eligibleCount;

    printf("Randomly selected thread TID: %d\n", eligibleThreads[targetIndex]->tid);
    return eligibleThreads[targetIndex];
}

int tsl_yield(int tid)
{
    if (ready_queue == NULL)
        return -1; 

    TCB *prev = NULL, *next = NULL;

    if (tid == TSL_ANY)
    {
        if (salg_global == ALG_RANDOM)
        {
            next = select_random_thread(current_thread);
        }
        else
        {

            next = (ready_queue != current_thread) ? ready_queue : ready_queue->next;
        }
    }
    else
    {
        for (TCB *iter = ready_queue; iter != NULL; prev = iter, iter = iter->next)
        {
            if (iter->tid == tid)
            {
                next = iter;
                if (prev != NULL)
                    prev->next = next->next; 
                break;
            }
        }
    }

    if (!next || next->finished)
        return -1; 

    if (current_thread && !current_thread->finished)
    {
        current_thread->next = NULL; 

        if (!ready_queue)
        {
            ready_queue = current_thread;
        }
        else
        {
            TCB *iter = ready_queue;
            while (iter->next)
                iter = iter->next;      
            iter->next = current_thread;
        }
    }

    TCB *temp_current = current_thread;
    current_thread = next;   
    ready_queue = next->next;

    if (temp_current != next)
    {                     
        next->next = NULL; 
        swapcontext(&temp_current->context, &current_thread->context);
    }

    return 0;
}

int tsl_join(int tid)
{
    if (tid <= 0)
        return -1; 

    while (1)
    {
        TCB *cursor = ready_queue;

        int found = 0;
        while (cursor != NULL)
        {
            if (cursor->tid == tid)
            {
                found = 1;
                break;
            }
            cursor = cursor->next;
        }

        if (!found)
        {
            return -1; 
        }
        tsl_yield(0);
    }

    return tid; 
}

int tsl_cancel(int tid)
{
 
    TCB **prev = &ready_queue;
    while (*prev != NULL)
    {
        if ((*prev)->tid == tid)
        {
            TCB *to_cancel = *prev;
            *prev = (*prev)->next; 

            free(to_cancel->stack);
            free(to_cancel);
            return 0; 
        }
        prev = &((*prev)->next);
    }
    return -1; 
}

int tsl_gettid()
{
    if (current_thread != NULL)
    {
        return current_thread->tid;
    }
    return -1;
}
