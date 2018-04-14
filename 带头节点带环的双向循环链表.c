//DLinkList.h
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<windows.h>


typedef char DLinkType;

typedef struct DLinkNode {
    DLinkType data;
    struct DLinkNode* next;
    struct DLinkNode* prev;
}DLinkNode;

void DLinkListInit(DLinkNode** head);//初始化双向循环链表
DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value);//尾插
void DLinkListPopBack(DLinkNode* head); // 尾删
void DLinkListPushFront(DLinkNode* head, DLinkType value);//头插
void DLinkListPopFront(DLinkNode* head);//头删
DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find);//查找指定元素
void DLinkListInsert(DLinkNode* pos, DLinkType value);//对任意指定位置之前插入
void DLinkListInsertAfter(DLinkNode* pos, DLinkType value);//在指定位置的之后插入
void DLinkListErase(DLinkNode* pos);//删除指定位置的元素
void DLinkListRemove(DLinkNode* head, DLinkType value);//删除指定的元素,只删除第一次出现的
void DLinkListRemoveAll(DLinkNode* head, DLinkType value);//删除指定的元素,删除所有出现在链表中的元素
size_t DLinkListsize(DLinkNode* head);//求链表长度
int DLinkListEmpty(DLinkNode* head);//判断链表是否为空
void DLinkListPrintChar(DLinkNode *head, const char* msg);//打印双向循环链表


//DLinkList.c
#include"DLinkList.h"

void DLinkListPrintChar(DLinkNode *head, const char* msg)//打印链表
{
    printf("[%s]: \n", msg);
    printf("[head]");
    DLinkNode* cur = head->next;
    for (; cur != head; cur = cur->next) {
        printf("->[%c:0x%p]", cur->data, cur);
    }
    printf("\n\n");
    DLinkNode* ptr = head->prev;
    for (; ptr != head; ptr = ptr->prev) {
        printf("[%c:Ox%p]->", ptr->data, ptr);
    }
    printf("[head]");
    printf("\n\n");
}


DLinkNode* CreateDNode(DLinkType value)
{
    DLinkNode* cur = (DLinkNode*)malloc(sizeof(DLinkNode));
    cur->data = value;
    cur->next = cur;
    cur->prev = cur;
    return cur;
}

void DestoryDNode(DLinkNode* pos)
{
    free(pos);
}

void DLinkListInit(DLinkNode** head)
{
    if (head == NULL) {
        return;
    }
    *head = NULL;
    *head = (DLinkNode*)malloc(sizeof(DLinkNode));
    (*head)->next = *head;
    (*head)->prev = *head;
}

DLinkNode* DLinkListPushBack(DLinkNode* head, DLinkType value)
{
    if (head == NULL)
    {
        return NULL;
    }
    DLinkNode* new_node = CreateDNode(value);
    DLinkNode* new_node_next = head;
    DLinkNode* new_node_prev = head->prev;

    new_node_prev->next = new_node;
    new_node->prev = new_node_prev;
    new_node_next->prev = new_node;
    new_node->next = new_node_next;
    return new_node;
}

void DLinkListPopBack(DLinkNode* head)
{
    if (head == NULL) {
        return;
    }
    if (head == head->next) {
        return;
    }
    DLinkNode* to_delete = head->prev;
    DLinkNode* to_delete_prev = to_delete->prev;
    DLinkNode* to_delete_next = head;

    to_delete_next->prev = to_delete_prev;
    to_delete_prev->next = to_delete_next;
    DestoryDNode(to_delete);
}

void DLinkListPushFront(DLinkNode* head, DLinkType value)
{
    if (head == NULL) {
        return;
    }
    DLinkNode* new_node = CreateDNode(value);
    DLinkNode* new_node_prev = head;
    DLinkNode* new_node_next = head->next;

    new_node->next = new_node_next;
    new_node->prev = new_node_prev;
    new_node_next->prev = new_node;
    new_node_prev->next = new_node;
}

void DLinkListPopFront(DLinkNode* head)
{
    if (head == NULL) {
        return;
    }
    if (head == head->next) {
        return;
    }
    DLinkNode* to_delete = head->next;
    DLinkNode* to_delete_next = to_delete->next;
    DLinkNode* to_delete_prev = head;

    to_delete_next->prev = to_delete_prev;
    to_delete_prev->next = to_delete_next;
    DestoryDNode(to_delete);
}

DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find)
{
    if (head == NULL) {
        return NULL;
    }
    DLinkNode* cur = head->next;
    for (; cur != head; cur = cur->next) {
        if (cur->data == to_find) {
            return cur;
        }
    }
    return NULL;
}

void DLinkListInsert(DLinkNode* pos, DLinkType value)
{
    if (pos == NULL) {
        //非法输入
        return;
    }
    DLinkNode* new_node = CreateDNode(value);
    DLinkNode* new_node_next = pos;
    DLinkNode* new_node_prev = pos->prev;

    new_node->next = new_node_next;
    new_node->prev = new_node_prev;
    new_node_next->prev = new_node;
    new_node_prev->next = new_node;
}

void DLinkListInsertAfter(DLinkNode* pos, DLinkType value)
{
    if (pos == NULL) {
        return;
    }
    DLinkNode* new_node = CreateDNode(value);
    DLinkNode* new_node_next = pos->next;
    DLinkNode* new_node_prev = pos;

    new_node->next = new_node_next;
    new_node->prev = new_node_prev;
    new_node_next->prev = new_node;
    new_node_prev->next = new_node;
}

void DLinkListErase(DLinkNode* pos)
{
    if (pos == NULL) {
        return;
    }
        DLinkNode* to_delete = pos;
        DLinkNode* to_delete_next = pos->next;
        DLinkNode* to_delete_prev = pos->prev;  

        to_delete_prev->next = to_delete_next;
        to_delete_next->prev = to_delete_prev;
        DestoryDNode(to_delete);
}

void DLinkListRemove(DLinkNode* head, DLinkType value)
{
    if (head == NULL) {
        return;
    }
    DLinkNode* cur = head->next;
    for (; cur != head; cur = cur->next) {
        if (cur->data == value) {
            DLinkListErase(cur);
            break;
        }
    }
    return;
}

void DLinkListRemoveAll(DLinkNode* head, DLinkType value)
{
    if (head == NULL) {
        return;
    }
    DLinkNode* cur = head;
    while (cur != head->prev) {
        if (cur->next->data == value) {
            DLinkNode* to_delete = cur->next;
            DLinkNode* to_delete_next = to_delete->next;
            DLinkNode* to_delete_prev = to_delete->prev;

            to_delete_next->prev = to_delete_prev;
            to_delete_prev->next = to_delete_next;
            DestoryDNode(to_delete);
        }
        else
            cur = cur->next;
    }
}

size_t DLinkListsize(DLinkNode* head)
{
    if (head == NULL) {
        return (size_t)-1;
    }
    size_t count = 0;
    DLinkNode* cur = head->next;
    while (cur != head) {
        count++;
        cur = cur->next;
    }
    return count;
}

int DLinkListEmpty(DLinkNode* head)
{
    if (head == NULL) {
        return -1;
    }
    return (head == head->next || head == head->prev);
}


//以下是测试代码
//test.c
#include"DLinkList.h"

#define TEST_HEADER printf("\n==============%s==============\n", __FUNCTION__)

void TestInit()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPrintChar(head, "初始化");
}

void TestPushBack()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插五个元素");
}

void TestPopBack()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPopBack(head);
    DLinkListPrintChar(head, "尝试对空链表删除");
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插五个元素");
    DLinkListPopBack(head);
    DLinkListPrintChar(head, "尝试尾删一个元素");
    DLinkListPopBack(head);
    DLinkListPopBack(head);
    DLinkListPrintChar(head, "尝试尾删两个元素");
}

void TestPushFront()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushFront(head, 'a');
    DLinkListPushFront(head, 'b');
    DLinkListPushFront(head, 'c');
    DLinkListPushFront(head, 'd');
    DLinkListPushFront(head, 'e');
    DLinkListPrintChar(head, "头插五个元素");
}

void TestPopFront()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPopFront(head);
    DLinkListPrintChar(head, "尝试对空链表删除");
    DLinkListPushFront(head, 'a');
    DLinkListPushFront(head, 'b');
    DLinkListPushFront(head, 'c');
    DLinkListPushFront(head, 'd');
    DLinkListPushFront(head, 'e');
    DLinkListPrintChar(head, "头插五个元素");
    DLinkListPopFront(head);
    DLinkListPrintChar(head, "尝试删除一个元素");
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkListPopFront(head);
    DLinkListPrintChar(head, "尝试删除三个元素");
}

void TestFind()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkNode* pos_b = DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插五个元素");
    DLinkListFind(head, 'x');
    DLinkListPrintChar(head, "查找不存在的元素x");
    DLinkNode* ret = DLinkListFind(head, 'b');
    DLinkListPrintChar(head, "查找存在的元素b");
    printf("0x%p\n", ret);
}

void TestInsert()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListInsert(head, 'a');
    DLinkListPrintChar(head, "对空链表的头结点之前插入");
    DLinkNode* pos_b = DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插四个元素");
    DLinkListInsert(pos_b, 'x');
    DLinkListPrintChar(head, "在b之前插入x");
}

void TestInsertAfter()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListInsertAfter(head, 'a');
    DLinkListPrintChar(head, "在空链表的头结点之后插入a");
    DLinkNode* pos_b = DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插四个元素");
    DLinkListInsertAfter(pos_b, 'x');
    DLinkListPrintChar(head, "在b之后插入x");
}

void TestErase()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkNode* pos_b = DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插五个元素");
    DLinkListErase(pos_b);
    DLinkListPrintChar(head, "尝试删除b元素");
}

void TestRemove()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插五个元素");
    DLinkListRemove(head, 'a');
    DLinkListPrintChar(head, "尝试删除元素a");

}

void TestRemoveAll()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPushBack(head, 'a');
    DLinkListPrintChar(head, "尾插九个元素");
    DLinkListRemoveAll(head, 'a');
    DLinkListPrintChar(head, "尝试删除元素a");
}

void TestSize()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPushBack(head, 'e');
    DLinkListPrintChar(head, "尾插八个元素");
    size_t ret = DLinkListsize(head);
    printf("ret expect 8, actual %lu\n", ret);
}

void TestEmpty()
{
    TEST_HEADER;
    DLinkNode* head;
    DLinkListInit(&head);
    int ret = DLinkListEmpty(head);
    printf("ret expect 1, actual %d\n", ret);
    DLinkListPushBack(head, 'a');
    DLinkListPushBack(head, 'b');
    DLinkListPushBack(head, 'c');
    DLinkListPushBack(head, 'd');
    DLinkListPrintChar(head, "尾插四个元素");
    ret = DLinkListEmpty(head);
    printf("ret expect 0, actual %d\n", ret);
}

int main()
{
    TestInit();
    TestPushBack();
    TestPopBack();
    TestPushFront();
    TestPopFront();
    TestFind();
    TestInsert();
    TestInsertAfter();
    TestErase();
    TestRemove();
    TestRemoveAll();
    TestSize();
    TestEmpty();
    system("pause");
    return 0;
}