//LinkList.h

#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include<stddef.h>
#include<stdio.h>
#include<windows.h>

typedef char LinkType;

typedef struct LinkNode{
    LinkType data;
    struct LinkNode* next;
}LinkNode;

void LinkListInit(LinkNode** head);//初始化
LinkNode* LinkListPushBack(LinkNode** head, LinkType value);//尾插
void LinkListPopBack(LinkNode** head);//尾删
void LinkListPushFront(LinkNode** head, LinkType value);//头插
void LinkListPopFront(LinkNode** head);//头删
LinkNode* LinkListFind(LinkNode* head, LinkType to_find);//查找元素在链表中的位置
void LinkListInsert(LinkNode** head, LinkNode* pos, LinkType value);//在指定位置之前插入
void LinkListInsertAfter(LinkNode** head, LinkNode* pos, LinkType value);//在指定位置之后插入
void LinkListErase(LinkNode** head, LinkNode* pos); //删除指定位置的元素
void LinkListRomove(LinkNode** head, LinkType to_delete);//删除指定元素
void LinkListRomove2(LinkNode** head, LinkType to_delete);//删除指定元素
void LinkListRomoveAll(LinkNode** head, LinkType value);
int LinkListEmpty(LinkNode* head);//判定链表是否为空，为空返回1，否则返回0
size_t LinkListSize(LinkNode* head);//计算链表的长度

#endif 

//LinkList.c

#include"LinkList.h"

void LinkListPrintChar(LinkNode *head, const char* msg)//打印链表
{
    printf("[%s]: ", msg);
    LinkNode* cur = head;
    for (; cur != NULL; cur = cur->next) {
        printf("[%c:%p] -> ", cur->data, cur);
    }
    printf("[NULL]\n\n");
}

void LinkListInit(LinkNode **head)//初始化链表
{
    if (head == NULL) {
        return;
    }
    *head = NULL;
}

LinkNode* LinkListCreateNode(LinkType value)//创建节点
{
    LinkNode* ptr = (LinkNode*)malloc(sizeof(LinkNode));
    ptr->data = value;
    ptr->next = NULL;
    return ptr;
}

void LinkListDestroyNode(LinkNode* ptr)//销毁，释放内存
{
    free(ptr);
}


LinkNode* LinkListPushBack(LinkNode** head, LinkType value)//尾插
{
    if (head == NULL) {
        //非法输入
        return NULL;
    }
    if (*head == NULL) {
        *head = LinkListCreateNode(value);
        return *head;
    }
    LinkNode* cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = LinkListCreateNode(value);
    return cur->next;
}

void LinkListPopBack(LinkNode** head)//尾删
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        //空链表
        return NULL;
    }
    LinkNode* cur = *head;
    if (cur->next == NULL) {
        //只有一个节点
        LinkListDestroyNode(cur);
        *head = NULL;
        return;
    }
    while (cur->next != NULL) {
        if (cur->next->next == NULL) {
            //找到倒数第二个节点
            LinkNode* to_delete = cur->next;
            cur->next = NULL;
            LinkListDestroyNode(to_delete);
        }
        else {
            cur = cur->next;
        }
    }
    return;
}

void LinkListPushFront(LinkNode** head, LinkType value)//头插
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        *head = LinkListCreateNode(value);
        return;
    }
    LinkNode* new_node = LinkListCreateNode(value);
    new_node->next = *head;
    *head = new_node;
    return;
}

void LinkListPopFront(LinkNode** head)//头删
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        //空链表
        return;
    }
    LinkNode* to_delete = *head;
    *head = (*head)->next;
    LinkListDestroyNode(to_delete);
}

LinkNode* LinkListFind(LinkNode* head, LinkType to_find)
//查找元素在链表中的位置
{
    LinkNode *cur = head;
    for (; cur != NULL; cur = cur->next) {
        if (cur->data == to_find) {
            return cur;
        }
    }
    return NULL;
}

void LinkListInsert(LinkNode** head, LinkNode* pos, LinkType value)//在指定位置之前插入
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        *head = LinkListCreateNode(value);
        return;
    }
    if (pos == NULL) {
        LinkListPushBack(head, value);
        return;
    }
    if (*head == pos) {
        LinkListPushFront(head, value);
        return;
    }
    LinkNode* cur = *head;
    while (cur->next != NULL) {
        if (cur->next == pos) {
            //找到pos的前一个位置
            LinkNode* new_node = LinkListCreateNode(value);
            new_node->next = pos;
            cur->next = new_node;
            return;
        }
        else {
            cur = cur->next;
        }
    }
    //pos不存在
    return;
}

void LinkListInsertAfter(LinkNode** head, 
                 LinkNode* pos, LinkType value) //在指定位置之后插入
{
    if (head == NULL) {
        return;
    }
    if (pos == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        *head = LinkListCreateNode(value);
        return;
    }
    LinkNode* new_node = LinkListCreateNode(value);
    new_node->next = pos->next;
    pos->next = new_node;
    //LinkNode* next = pos->next;
    //pos->next = new_node;
    //new_node->next = next;

}

void LinkListErase(LinkNode** head, LinkNode* pos)
//删除指定位置的元素
{
    if (head == NULL || pos == NULL) {
        return;
    }
    if (*head == NULL) {
        return;
    }
    if (*head == pos) {
        LinkNode* to_delete = pos;
        head = (*head)->next;
        LinkListDestroyNode(to_delete);
        return;
    }
    LinkNode* cur = *head;
    while (cur->next != NULL) {
        if (cur->next == pos) {
            cur->next = pos->next;
            LinkListDestroyNode(pos);
            return;
        }
        cur = cur->next;
    }
    return;
}

void LinkListRomove(LinkNode** head, LinkType to_delete)
//删除指定的元素
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        //空链表
        return;
    }
    LinkNode* pos = LinkListFind(*head, to_delete);
    LinkListErase(head, pos);
}

void LinkListRomove2(LinkNode** head, LinkType to_delete_value)//删除指定的元素,只遍历一次链表
{
    if (head == NULL) {
        //非法输入
        return;
    }
    if (*head == NULL) {
        //空链表
        return;
    }
    if ((*head)->data == to_delete_value) {
        LinkNode* to_delete = *head;
        *head = (*head)->next;
        LinkListDestroyNode(to_delete);
        return;
    }
    LinkNode* cur = (*head)->next;
    LinkNode* pre = *head;
    while (cur != NULL) {
        if (cur->data == to_delete_value) {
            pre->next = cur->next;
            LinkListDestroyNode(cur);
            return;
        }
        else {
            pre = pre->next;
            cur = cur->next;
        }
    }
    return;
}

void LinkListRomoveAll(LinkNode** head, LinkType value)
//删除所有出现在链表中的指定的元素
{
    if (head == NULL) {
        //非法输入
        return;
    }
    while (1) {
        LinkNode* pos = LinkListFind(*head, value);
        if (pos == NULL) {
            break;
        }
        LinkListErase(head, pos);
    }
    return;
}

int LinkListEmpty(LinkNode* head)//判断链表是否为空
{
    return head == NULL ? 1 : 0;
}

size_t LinkListSize(LinkNode* head)//计算链表长度
{
    if (head == NULL) {
        return 0;
    }
    size_t count = 0;
    LinkNode* cur = head;
    while (cur != NULL) {
        ++count;
        cur = cur->next;
    }
    return count;
}

//test.c

#include"LinkList.h"

#define TEST_HEADER printf("\n==============%s==============\n", __FUNCTION__)

void TestInit()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    printf("%p, %d\n", &head, head);
}

void TestPushBack()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
}

void TestPopBack()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head, "尝试对空链表尾删");
    LinkListPushBack(&head, 'a');
    LinkListPopBack(&head);
    LinkListPrintChar(head, "尝试对只有一个元素的链表尾删");
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    LinkListPopBack(&head);
    LinkListPopBack(&head);
    LinkListPrintChar(head, "尾删两个元素");
}

void TestPushFront()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushFront(&head, 'a');
    LinkListPushFront(&head, 'b');
    LinkListPushFront(&head, 'c');
    LinkListPushFront(&head, 'd');
    LinkListPrintChar(head, "头插四个元素");
}

void TestPopFront()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head, "尝试对空链表进行头删");
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    LinkListPopFront(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head, "头删两个元素");
    LinkListPopFront(&head);
    LinkListPopFront(&head);
    LinkListPrintChar(head, "再头删两个元素");
}
void TestFind()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkNode*pos_b = LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkNode* pos = LinkListFind(head, 'x');
    printf("pos x expect NULL, actual %p\n", pos);
    pos = LinkListFind(head, 'b');
    printf("pos b expect %p, actual %p\n", pos_b, pos);
}

void TestInsert()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListInsert(&head, head, 'a');
    LinkListPrintChar(head, "对空链表插入");
    LinkListInsert(&head, head, 'b');
    LinkListPrintChar(head, "对链表头部插入");
    LinkListPushBack(&head, 'c');
    LinkNode* pos_d = LinkListPushBack(&head, 'd');
    LinkListInsert(&head, pos_d, 'e');
    LinkListPrintChar(head, "往d之前插入e");
    LinkListInsert(&head, NULL, 'f');
    LinkListPrintChar(head, "往链表尾部插入f");
}

TestInsertAfter()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListInsertAfter(&head, head, 'a');
    LinkListPrintChar(head, "对空链表插入");
    LinkListInsertAfter(&head, head, 'b');
    LinkListPrintChar(head, "对链表头部插入");
    LinkListPushBack(&head, 'c');
    LinkNode* pos_d = LinkListPushBack(&head, 'd');
    LinkListInsertAfter(&head, pos_d, 'e');
    LinkListPrintChar(head, "往d之后插入e");
    LinkListInsertAfter(&head, NULL, 'f');
    LinkListPrintChar(head, "往链表NULL之后插入f");
}

void TestErase()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListErase(&head, NULL);
    LinkListPrintChar(head, "尝试对空链表删除");
    LinkListPushBack(&head, 'a');
    LinkNode* pos_b = LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    LinkListErase(&head, pos_b);
    LinkListPrintChar(head, "删除元素b");
}

void TestRemove()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    LinkListRomove(&head, 'x');
    LinkListPrintChar(head, "尝试删除不存在的元素x");
    LinkListRomove(&head, 'b');
    LinkListPrintChar(head, "删除元素b");

}

void TestRemove2()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    LinkListRomove2(&head, 'x');
    LinkListPrintChar(head, "尝试删除不存在的元素x");
    LinkListRomove2(&head, 'b');
    LinkListPrintChar(head, "删除元素b");
    LinkListRomove2(&head, 'a');
    LinkListPrintChar(head, "删除元素a");

}

void TestRemoveAll()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'b');
    LinkListPrintChar(head, "尾插六个元素");  
    LinkListRomoveAll(&head, 'x');
    LinkListPrintChar(head, "尝试删除不存在的元素x");
    LinkListRomoveAll(&head, 'b');
    LinkListPrintChar(head, "删除元素b");
}

void TestEmpty()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    int ret = LinkListEmpty(head);
    printf("list empty expect 1, actual %d\n", ret);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    ret = LinkListEmpty(head);
    printf("list empty expect 0, actual %d\n", ret);
}

void TestSize()
{
    TEST_HEADER;
    LinkNode* head;
    LinkListInit(&head);
    LinkListPushBack(&head, 'a');
    LinkListPushBack(&head, 'b');
    LinkListPushBack(&head, 'c');
    LinkListPushBack(&head, 'd');
    LinkListPrintChar(head, "尾插四个元素");
    size_t ret = LinkListSize(head);
    printf("list size expect 4, actual %d\n", ret);
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
    TestRemove2();
    TestRemoveAll();
    TestEmpty();
    TestSize();
    system("pause");
    return 0;
}