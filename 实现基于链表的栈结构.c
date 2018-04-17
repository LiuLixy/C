//LinkStack.c
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<windows.h>

typedef char LinkStackType;

typedef struct LinkStack {
    LinkStackType data;
    struct LinkStack* next;
}LinkStack;

void LinkStackInit(LinkStack** stack);
void LinkStackPrintChar(LinkStack* stack, const char* msg);
LinkStack* LinkStackPush(LinkStack** stack, LinkStackType value);
void LinkStackPop(LinkStack** stack);
void GetTop(LinkStack* stack, LinkStackType* value);
void LinkStackDestory(LinkStack** stack);


//LinkStack.c
#include"LinkStack.h"

void LinkStackPrintChar(LinkStack* stack, const char* msg)
{
    printf("[%s]: \n", msg);
    LinkStack* cur = stack;
    for (; cur != NULL; cur = cur->next) {
        printf("[%c:0x%p] -> ", cur->data, cur);
    }
    printf("[NULL]\n\n");
}

void LinkStackInit(LinkStack** stack) 
{
    if (stack == NULL) {
        return;
    }
    *stack = NULL;
}

LinkStack* CreateNode(LinkStackType value)
{
    LinkStack* cur = (LinkStack*)malloc(sizeof(LinkStack));
    cur->data = value;
    cur->next = NULL;
    return cur;
}

void DestoryNode(LinkStack* to_delete)
{
    free(to_delete);
}

LinkStack* LinkStackPush(LinkStack** stack, LinkStackType value)
{
    if (stack == NULL) {
        return NULL;
    }
    if (*stack == NULL) {
        *stack = CreateNode(value);
        return *stack;
    }
    LinkStack* cur = *stack;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = CreateNode(value);
    return cur->next;
}

void LinkStackPop(LinkStack** stack)
{
    if (stack == NULL){     
        return;
     }
    if (*stack == NULL) {
        return;
    }
    LinkStack* cur = *stack;
    if (cur->next == NULL) {
        DestoryNode(cur);
        *stack = NULL;
        return;
    }
    while (cur->next != NULL) {
        if (cur->next->next == NULL) {
            LinkStack* to_delete = cur->next;
            cur->next = NULL;
            DestoryNode(to_delete);
        }
        else {
            cur = cur->next;
        }
    }
    return;
}

void GetTop(LinkStack* stack, LinkStackType* value)
{
    if (stack == NULL || value == NULL) {
        return;
    }
    LinkStack* cur = stack;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    *value = cur->data;
    return *value;
}

void LinkStackDestory(LinkStack** stack)
{
    if (stack == NULL) {
        return;
    }
    if (*stack == NULL) {
        return;
    }
    LinkStack* cur = *stack;
    while (cur->next != NULL) {
        LinkStack* to_delete = cur;
        cur = cur->next;
        DestoryNode(to_delete);
    }
    DestoryNode(cur);
    *stack = NULL;
}

////////////////////////////////////////
////////////以下是测试代码
////////////////////////////////////////

#define TEST_HEADER printf("\n============%s============\n", __FUNCTION__)

void TestInit()
{
    TEST_HEADER;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPrintChar(stack, "初始化");
}

void TestPush()
{
    TEST_HEADER;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack, 'a');
    LinkStackPush(&stack, 'b');
    LinkStackPush(&stack, 'c');
    LinkStackPush(&stack, 'd');
    LinkStackPrintChar(stack, "入栈四个元素");
}

void TestPop()
{
    TEST_HEADER;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPop(&stack);
    LinkStackPrintChar(stack, "尝试对空栈进行出栈操作");
    LinkStackPush(&stack, 'a');
    LinkStackPush(&stack, 'b');
    LinkStackPush(&stack, 'c');
    LinkStackPush(&stack, 'd');
    LinkStackPrintChar(stack, "入栈四个元素");
    LinkStackPop(&stack);
    LinkStackPop(&stack);
    LinkStackPrintChar(stack, "出栈两个元素");
}

void TestGetTop()
{
    TEST_HEADER;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack, 'a');
    LinkStackPush(&stack, 'b');
    LinkStackPush(&stack, 'c');
    LinkStackPush(&stack, 'd');
    LinkStackPrintChar(stack, "入栈四个元素");
    LinkStackType* value = stack;
    GetTop(stack, value);
    printf("Top expect d, actual %c\n", *value);
}

void TestDestory()
{
    TEST_HEADER;
    LinkStack* stack;
    LinkStackInit(&stack);
    LinkStackPush(&stack, 'a');
    LinkStackPush(&stack, 'b');
    LinkStackPush(&stack, 'c');
    LinkStackPush(&stack, 'd');
    LinkStackPrintChar(stack, "入栈四个元素");
    LinkStackDestory(&stack);
    LinkStackPrintChar(stack, "销毁栈");
}

int main()
{
    TestInit(); 
    TestPush();
    TestPop();
    TestGetTop();
    TestDestory();
    system("pause");
    return 0;
}