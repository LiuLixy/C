//LinkQueue.h
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef char LinkQueueType;

typedef struct LinkQueueNode {
    LinkQueueType data;
    struct LinkQueueNode* next;
}LinkQueueNode;

typedef struct LinkQueue {
    LinkQueueNode* head;
    LinkQueueNode* tail;
}LinkQueue;

void LinkQueueInit(LinkQueue* q);
void LinkQueuePush(LinkQueue* q, LinkQueueType value);//入队
void LinkQueuePop(LinkQueue* q);//出队列
int LinkQueueFront(LinkQueue* q, LinkQueueType* value);//取队首元素

//LinkQueue.c
#include"LinkQueue.h"

void LinkQueueInit(LinkQueue* q)
{
    if (q == NULL) {
        return;
    }
    q->head = NULL;
    q->tail = NULL;
}

LinkQueueNode* CreateLinkQueueNode(LinkQueueType value)
{
    LinkQueueNode* new_node = (LinkQueueNode*)malloc(sizeof(LinkQueueNode));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void DestoryLinkQueueNode(LinkQueueNode* ptr)
{
    free(ptr);
}

void LinkQueuePush(LinkQueue* q, LinkQueueType value)
{
    if (q == NULL) {
        return;
    }
    LinkQueueNode* new_node = CreateLinkQueueNode(value);
    if (q->head == NULL) {
        q->head = q->tail = new_node;
    }
    q->tail->next = new_node;
    q->tail = q->tail->next;
    return;
}

void LinkQueuePop(LinkQueue* q)
{
    if (q == NULL) {
        return;
    }
    if (q->head == NULL) {
        //空队列
        return;
    }
    if (q->head == q->tail) {
        DestoryLinkQueueNode(q->head);
        q->head = q->tail = NULL;
    }
    LinkQueueNode* to_delete = q->head;
    q->head = to_delete->next;
    DestoryLinkQueueNode(to_delete);
    return;
}

int LinkQueueFront(LinkQueue* q, LinkQueueType* value)
{
    if (q == NULL || value == NULL) {
        return 0;
    }
    if (q->head == NULL) {
        return 0;
    }
    *value = q->head->data;
    return 1;
}


//////////////////////////////
///////以下是测试代码//////////
//////////////////////////////
void Test()
{
    TEST_HEADER;
    LinkQueue q;
    LinkQueueInit(&q);
    LinkQueuePush(&q, 'a');
    LinkQueuePush(&q, 'b');
    LinkQueuePush(&q, 'c');
    LinkQueuePush(&q, 'd');
    LinkQueuePush(&q, 'e');

    LinkQueueType tmp;
    LinkQueueFront(&q, &tmp);
    printf("tmp expect a, actual %c\n", tmp);
    LinkQueuePop(&q);   
    LinkQueueFront(&q, &tmp);
    printf("tmp expect b, actual %c\n", tmp);
    LinkQueuePop(&q);   
    LinkQueueFront(&q, &tmp);
    printf("tmp expect c, actual %c\n", tmp);
    LinkQueuePop(&q);
    LinkQueueFront(&q, &tmp);
    printf("tmp expect d, actual %c\n", tmp);
    LinkQueuePop(&q);   
    LinkQueueFront(&q, &tmp);
    printf("tmp expect e, actual %c\n", tmp);
}



int main()
{
    Test();
    system("pause");
    return 0;
}