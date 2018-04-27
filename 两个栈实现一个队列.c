#include<stdio.h>
#include<stdlib.h>

#include"SeqStack.h"

void SeqStackInit(SeqStack* stack)
{
    if (stack == NULL) {
        return;
    }
    stack->size = 0;
}

void SeqStackPush(SeqStack* stack, SeqStackType value)
{
    if (stack == NULL) {
        return;
    }
    if (stack->size >= SeqStackMaxSize)
        return;
    stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack)
{
    if (stack == 0) {
        return;
    }
    if (stack->size == 0)
        return;
    --stack->size;
}

int GetTop(SeqStack* stack, SeqStackType* value)
{
    if (stack == NULL || value == NULL) {
        return 0;
    }
    if (stack->size == 0)
        return 0;
    *value = stack->data[stack->size - 1];
    return 1;
}
typedef char QueueType;

typedef struct Queue {
    SeqStack entry;
    SeqStack exit;
}Queue;

void QueueInit(Queue* q)
{
    if (q == NULL) {
        return;
    }
    SeqStackInit(&q->entry);
    SeqStackInit(&q->exit);
}

void QueuePush(Queue* q, QueueType value)
{
    if (q == NULL) {
        return;
    }
    QueueType tmp;
    while (GetTop(&q->exit, &tmp)) {
        //如果exit栈不为空，就将exit栈中的元素出栈，再入栈到entry栈中
        SeqStackPop(&q->exit);
        SeqStackPush(&q->entry, tmp);
    }
    SeqStackPush(&q->entry, value);
}

void QueuePop(Queue* q)
{
    if (q == NULL) {
        return;
    }
    QueueType tmp;
    while (GetTop(&q->entry, &tmp)) {
        SeqStackPop(&q->entry);
        SeqStackPush(&q->exit, tmp);
    }
    SeqStackPop(&q->exit);
}

int QueueFront(Queue* q, QueueType* value)
{
    if (q == NULL || value == NULL) {
        return 0;
    }
    QueueType tmp;
    while (GetTop(&q->entry, &tmp)) {
        SeqStackPop(&q->entry);
        SeqStackPush(&q->exit, tmp);
    }
    int ret = GetTop(&q->exit, value);
    return ret;
}

//////////////////////////////
////////以下是测试代码////////
//////////////////////////////


#include<stdio.h>

void Test()
{
    Queue q;
    QueueInit(&q);
    QueuePush(&q, 'a');
    QueuePush(&q, 'b');
    QueuePush(&q, 'c');
    QueuePush(&q, 'd');

    QueueType tmp;
    QueueFront(&q, &tmp);
    printf("tmp expect a, actual %c\n", tmp);
    QueuePop(&q);
    QueueFront(&q, &tmp);
    printf("tmp expect b, actual %c\n", tmp);
    QueuePop(&q);
    QueueFront(&q, &tmp);
    printf("tmp expect c, actual %c\n", tmp);
    QueuePop(&q);
    QueueFront(&q, &tmp);
    printf("tmp expect d, actual %c\n", tmp);
    return;
}

int main()
{
    Test();
    system("pause");
    return 0;
}