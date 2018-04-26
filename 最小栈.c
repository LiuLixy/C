//方法一：使用两个栈，一个data栈保存插入的元素，另一个min栈保存当前栈中的最小元素，
//这样要取最小栈的时候只需要取min栈顶元素即可。
#include<stdio.h>
#include<stdlib.h>

#include"SeqStack.h"

typedef char MinStackType;

typedef struct MinStack {
    SeqStack data; //保存栈中的元素
    SeqStack min;  //保存当前栈的最小元素
}MinStack;

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

void MinStackInit(MinStack* min_stack)
{
    if (min_stack == NULL) {
        return;
    }
    SeqStackInit(&min_stack->data);
    SeqStackInit(&min_stack->min);
}

void MinStackPush(MinStack* min_stack, MinStackType value)
{
    if (min_stack == NULL) {
        return;
    }
    MinStackType tmp;
    int ret = GetTop(&min_stack->min, &tmp);
    if (ret == 0) {
        //空栈
        SeqStackPush(&min_stack->data, value);
        SeqStackPush(&min_stack->min, value);
        return;
    }
    //原来的栈非空，先比较要插入的元素与min栈顶元素的大小
    MinStackType min = value < tmp ? value : tmp;
    SeqStackPush(&min_stack->data, value);
    SeqStackPush(&min_stack->min, min);
}

void MinStackPop(MinStack* min_stack)
{
    if (min_stack == NULL) {
        return;
    }
    SeqStackPop(&min_stack->data);
    SeqStackPop(&min_stack->min);
}

int MinStackMinTop(MinStack* min_stack, MinStackType* value)
{
    if (min_stack == NULL) {
        return 0;
    }
    return GetTop(&min_stack->min, value);
}


//////////////////////////////////
/////////以下是测试代码///////////
//////////////////////////////////


void Test()
{
    MinStack stack;
    MinStackInit(&stack);
    MinStackPush(&stack, 'd');
    MinStackPush(&stack, 'c');
    MinStackPush(&stack, 'b');
    MinStackPush(&stack, 'a');

    char tmp;
    MinStackMinTop(&stack, &tmp);
    printf("tmp expect a, actual %c\n", tmp);
    MinStackPop(&stack);
    MinStackMinTop(&stack, &tmp);
    printf("tmp expect b, actual %c\n", tmp);
    MinStackPop(&stack);
    MinStackMinTop(&stack, &tmp);
    printf("tmp expect c, actual %c\n", tmp);
    MinStackPop(&stack);
    MinStackMinTop(&stack, &tmp);
    printf("tmp expect d, actual %c\n", tmp);
    MinStackPop(&stack);
    return;
}


int main()
{
    Test();
    return 0;
}


//当一个元素入栈时，先将该元素与栈中最小的元素进行比较，将两者中较小的元素随着当前元素入栈，
//这样入栈一个元素实际上是入栈两个元素，栈中最小的元素永远都处于栈顶的位置，进行取最小栈操作时只需取栈顶元素即可。
typedef struct MinStack {
    SeqStack data;
}MinStack;

void MinStackInit(MinStack* stack) 
{
    if (stack == NULL) {
        return;
    }
    SeqStackInit(&stack->data);
}

void MinStackPush(MinStack* stack, MinStackType value)
{
    if (stack == NULL) {
        return;
    }
    MinStackType tmp;
    int ret = GetTop(&stack->data, &tmp);
    if (ret == 0) {
        SeqStackPush(&stack->data, value);
        SeqStackPush(&stack->data, value);
        return;
    }
    MinStackType min = value < tmp ? value : tmp;
    SeqStackPush(&stack->data, value);
    SeqStackPush(&stack->data, min);
    return;
}

void MinStackPop(MinStack* stack)
{
    if (stack == NULL) {
        return;
    }
    SeqStackPop(&stack->data);
    SeqStackPop(&stack->data);
    return;
}

int MinStackMinTop(MinStack* stack, MinStackType* value)
{
    if (stack == NULL || value == NULL) {
        return 0;
    }
    return GetTop(&stack->data, value);
}