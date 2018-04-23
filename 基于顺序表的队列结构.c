//SeqQueue.h
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


#define SeqQueueMaxSize 1000

typedef char SeqQueueType;

typedef struct SeqQueue {
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;
    size_t tail;
    size_t size;
}SeqQueue;

void SeqQueueInit(SeqQueue* q);
void SeqQueueDestory(SeqQueue* q);
void SeqQueuePush(SeqQueue* q, SeqQueueType value);
void SeqQueuePop(SeqQueue* q);
int SeqQueueFront(SeqQueue* q, SeqQueueType* value);

//SeqQueue.c
#include"SeqQueue.h"

void SeqQueueInit(SeqQueue* q)
{
    if (q == NULL) {
        return;
    }
    q->head = q->tail = 0;
    q->size = 0;
}

void SeqQueueDestory(SeqQueue* q)
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


////////////////////////////////
/////////以下是测试代码//////////
////////////////////////////////
void Test()
{
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q, 'a');
    SeqQueuePush(&q, 'b');
    SeqQueuePush(&q, 'c');
    SeqQueuePush(&q, 'd');
    SeqQueuePush(&q, 'e');

    char tmp;
    SeqQueueFront(&q, &tmp);
    printf("tmp expect a, actual %c\n", tmp);
    SeqQueuePop(&q);
    SeqQueueFront(&q, &tmp);
    printf("tmp expect b, actual %c\n", tmp);
    SeqQueuePop(&q);
    SeqQueueFront(&q, &tmp);
    printf("tmp expect c, actual %c\n", tmp);
    SeqQueuePop(&q);
    SeqQueueFront(&q, &tmp);
    printf("tmp expect d, actual %c\n", tmp);
    SeqQueuePop(&q);
    SeqQueueFront(&q, &tmp);
    printf("tmp expect e, actual %c\n", tmp);
}

int main()
{
    Test();
    system("pause");
    return 0;
}











