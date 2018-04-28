#include<stdio.h>
#include<stdlib.h>

#include"SeqQueue.h"

typedef char StackType;

typedef struct Stack {
    SeqQueue queue1;
    SeqQueue queue2;
}Stack;

void SeqQueueInit(SeqQueue* q)
{
    if (q == NULL) {
        return;
    }
    q->head = q->tail = 0;
    q->size = 0;
}

void SeqQueuePush(SeqQueue* q, SeqQueueType value)
{
    if (q == NULL) {
        return;
    }
    if (q->size == SeqQueueMaxSize) {
        return;
    }
    q->data[q->tail++] = value;
    q->tail %= SeqQueueMaxSize;
    ++q->size;
}

void SeqQueuePop(SeqQueue* q)
{
    if (q == NULL) {
        return;
    }
    if (q->size == 0) {
        return;
    }
    ++q->head;
    q->head %= SeqQueueMaxSize;
    --q->size;
}

int SeqQueueFront(SeqQueue* q, SeqQueueType* value)
{
    if (q == NULL || value == NULL) {
        return 0;
    }
    if (q->size == 0) {
        return 0;
    }
    *value = q->data[q->head];
    return 1;
}

size_t SeqQueueSize(SeqQueue* q)
{
    if (q == NULL) {
        return (size_t)-1;
    }
    return q->size;
}


void StackInit(Stack* stack)
{
    if (stack == NULL) {
        return;
    }
    SeqQueueInit(&stack->queue1);
    SeqQueueInit(&stack->queue2);
}

void StackPush(Stack* stack, StackType value)
{
    if (stack == NULL) {
        return;
    }
    SeqQueue* entry = SeqQueueSize(&stack->queue1) > 0 ? &stack->queue1 : &stack->queue2;
    SeqQueuePush(entry, value);
}

void StackPop(Stack* stack)
{
    if (stack == NULL) {
        return;
    }
    size_t size1 = SeqQueueSize(&stack->queue1);
    size_t size2 = SeqQueueSize(&stack->queue2); //size1、size2不可能同时不为0。
    if (size1 == 0 && size2 == 0) {
        return;
    }
    SeqQueue* exit = size1 > 0 ? &stack->queue1 : &stack->queue2; //exit用于出栈
    SeqQueue* backup = size1 == 0 ? &stack->queue1 : &stack->queue2;//backup用于备份数据
    while (SeqQueueSize(exit) > 1) {
        StackType tmp;
        SeqQueueFront(exit, &tmp);
        SeqQueuePop(exit);
        SeqQueuePush(backup, tmp);
    }
    SeqQueuePop(exit);
}

int StackTop(Stack* stack, StackType* value)
{
    if (stack == NULL || value == NULL) {
        return 0;
    }
    size_t size1 = SeqQueueSize(&stack->queue1);
    size_t size2 = SeqQueueSize(&stack->queue2);
    if (size1 == 0 && size2 == 0) {
        //空栈，无法取栈顶元素
        return 0;
    }
    SeqQueue* non_empty = size1 > 0 ? &stack->queue1 : &stack->queue2;
    SeqQueue* empty = size2 == 0 ? &stack->queue1 : &stack->queue2;
    StackType tmp;
    while (SeqQueueSize(non_empty) > 0) {
        SeqQueueFront(non_empty, &tmp);
        SeqQueuePop(non_empty);
        SeqQueuePush(empty, tmp);
    }
    *value = tmp;
    return 1;
}


//////////////////////////////////////////
////////////以下是测试代码////////////////
//////////////////////////////////////////

#include<stdio.h>

void Test()
{
    Stack stack;
    StackInit(&stack);
    StackPush(&stack, 'a');
    StackPush(&stack, 'b');
    StackPush(&stack, 'c');
    StackPush(&stack, 'd');

    StackType tmp;
    StackTop(&stack, &tmp);
    printf("tmp expect d, actual %c\n", tmp);
    StackPop(&stack);
    StackTop(&stack, &tmp);
    printf("tmp expect c, actual %c\n", tmp);
    StackPop(&stack);
    StackTop(&stack, &tmp);
    printf("tmp expect b, actual %c\n", tmp);
    StackPop(&stack);
    StackTop(&stack, &tmp);
    printf("tmp expect a, actual %c\n", tmp);
    return;
}

int main()
{
    Test();
    system("pause");
    return 0;
}