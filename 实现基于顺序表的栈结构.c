//SeqStack.h

#pragma once

#include<stdio.h>
#include<stddef.h>
#include<windows.h>

typedef char SeqStackType;

#define SeqStackMaxSize 1000

typedef struct SeqStack {
	SeqStackType data[SeqStackMaxSize];
	size_t size;
}SeqStack;

void SeqStackInit(SeqStack* stack);
void SeqStackPush(SeqStack* stack, SeqStackType value);
void SeqStackPop(SeqStack* stack);
int SeqStackTop(SeqStack* stack, SeqStackType* value); //取栈顶元素
void SeqStackDestory(SeqStack* stack);      //销毁栈


//SeqStack.c
#include"SeqStack.h"

void SeqStackInit(SeqStack* stack) {
	if (stack == NULL) {
		return;
	}
	stack->size = 0;
}

void SeqStackPush(SeqStack* stack, SeqStackType value) {
	if (stack == NULL) {
		return;
	}
	if (stack->size >= SeqStackMaxSize) {
		return;
	}
	stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack) {
	if (stack == NULL) {
		return;
	}
	if (stack->size <= 0) {
		return;
	}
	--stack->size;
}

int SeqStackTop(SeqStack* stack, SeqStackType* value) {
	if (stack == NULL || value == NULL) {
		return 0;
	}
	if (stack->size == 0) {
		return 0;
	}
	*value = stack->data[stack->size - 1];
	return 1;
}

void SeqStackDestory(SeqStack* stack) {
	if (stack == NULL) {
		return;
	}
	stack->size = 0;
}

void SeqStackPrintChar(SeqStack* stack, const char* msg) {
	printf("[%s]\n", msg);
	size_t i = 0;
	for (; i < stack->size; i++) {
		printf("[%c:0x%p] ", stack->data[i], &stack->data[i]);
	}
	printf("\n");
}

///////////////////////////////////////////
///////////以下是测试代码
///////////////////////////////////////////

#define TEST_HEADER printf("\n==========%s=========\n", __FUNCTION__)

void TestInit() {
	TEST_HEADER;
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPrintChar(&stack, "初始化");
}

void TestPush() {
	TEST_HEADER;
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack, 'a');
	SeqStackPush(&stack, 'b');
	SeqStackPush(&stack, 'c');
	SeqStackPush(&stack, 'd');
	SeqStackPush(&stack, 'e');
	SeqStackPush(&stack, 'f');
	SeqStackPrintChar(&stack, "入栈6个元素");
}

void TestPop() {
	TEST_HEADER;
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack, 'a');
	SeqStackPush(&stack, 'b');
	SeqStackPush(&stack, 'c');
	SeqStackPush(&stack, 'd');
	SeqStackPush(&stack, 'e');
	SeqStackPush(&stack, 'f');
	SeqStackPrintChar(&stack, "入栈6个元素");
	SeqStackPop(&stack);
	SeqStackPop(&stack);
	SeqStackPop(&stack);
	SeqStackPrintChar(&stack, "出栈3个元素");
}

void TestTop() {
	TEST_HEADER;
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack, 'a');
	SeqStackPush(&stack, 'b');
	SeqStackPush(&stack, 'c');
	SeqStackPush(&stack, 'd');
	SeqStackPush(&stack, 'e');
	SeqStackPush(&stack, 'f');
	SeqStackPrintChar(&stack, "入栈6个元素");
	SeqStack* value = stack.data;
	SeqStackTop(&stack, value);
	printf("top expect f, actual %c\n", *value);
}

void TestDestory() {
	TEST_HEADER;
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack, 'a');
	SeqStackPush(&stack, 'b');
	SeqStackPush(&stack, 'c');
	SeqStackPush(&stack, 'd');
	SeqStackPush(&stack, 'e');
	SeqStackPush(&stack, 'f');
	SeqStackPrintChar(&stack, "入栈6个元素");
	SeqStackDestory(&stack);
	SeqStackPrintChar(&stack, "销毁栈");
}

int main() {
	TestInit();
	TestPush();
	TestPop();
	TestTop();
	TestDestory();
	system("pause");
	return 0;
}