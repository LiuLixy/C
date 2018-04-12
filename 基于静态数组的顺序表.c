//实现基于静态数组的顺序表的以下操作：
// 1. 初始化
// 2. 尾插
// 3. 尾删
// 4. 头插
// 5. 头删
// 6. 读任意位置元素 
// 7. 修改任意位置元素 
// 8. 查找指定元素值的下标 
// 9. 在任意位置插入元素 
//10. 删除任意元素（如果该元素多次出现，则删除第一次出现的该元素） 
//11. 删除任意元素（如果该元素多次出现，则删除所有）


//Seqlist.h

#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<assert.h>

#define SeqMaxLenth 1000

typedef char SeqListType;   //类型重定义
typedef struct SeqList{
    SeqListType SeqListArr[SeqMaxLenth];
    size_t size;
}SeqList;

void SeqListInit(SeqList *seq);    //初始化
void SeqListPushBack(SeqList *seq, SeqListType value);   //尾插  
void SeqListPopBack(SeqList *seq);   //尾删  
void SeqListPushStart(SeqList *seq, SeqListType value);//头插
void SeqListPopStart(SeqList *seq);      //头删
SeqListType SeqListGet(SeqList *seq, size_t pos);   //读取任意位置
void SeqListSetList(SeqList* seq, size_t pos, SeqListType value);  //修改任意位置
size_t SeqListGetPos(SeqList *seq, SeqListType value);   //查找指定元素的下标
void SeqListInsert(SeqList *seq, size_t pos, SeqListType value);  //指定位置插入
void SeqListErase(SeqList *seq, size_t pos);   //指定下标删除
void SeqListRemove(SeqList *seq, SeqListType value);    //指定元素删除,删除第一次出现的元素
void SeqListRemoveAll(SeqList *seq, SeqListType value);  //删除所有出现在顺序表中的指定元素
void SeqListPrint(SeqList *seq);  //打印顺序表



//SeqList.c

#include "SeqList.h"

//初始化
void SeqListInit(SeqList *seq)
{
    assert(seq);
    seq->size = 0;
}

//尾插
void SeqListPushBack(SeqList *seq, SeqListType value)
{
    assert(seq);

    if (seq->size >= SeqMaxLenth){
        return;
    }
    else{
        seq->SeqListArr[seq->size] = value; 
        seq->size++;
    }
}

//尾删
void SeqListPopBack(SeqList *seq)
{
    assert(seq);

    if (seq->size == 0)
        return;
    else
        seq->size--;
}

//头插
void SeqListPushStart(SeqList *seq, SeqListType value)
{
    assert(seq);

    if (seq->size >= SeqMaxLenth) {
        return;
    }
    SeqListType i = seq->size - 1;
    for (; i >= 0; --i){
     seq->SeqListArr[i + 1] = seq->SeqListArr[i];//将顺序表中的所有元素后移一位
    }
    seq->SeqListArr[0] = value;
    ++seq->size;
}

//头删
void SeqListPopStart(SeqList *seq)
{
    assert(seq);

    if (seq->size == 0)
        return;
    size_t i = 0;
    for (; i < seq->size - 1; i++) {
        seq->SeqListArr[i] = seq->SeqListArr[i + 1];
    }
    seq->size--;
}

//读取下标为pos的元素
SeqListType SeqListGet(SeqList *seq, size_t pos)
{
    assert(seq);

    if (pos > seq->size - 1)
        return -1;
    else
        return seq->SeqListArr[pos];
}

//修改下标为pos的元素
void SeqListSetList(SeqList* seq, size_t pos, SeqListType value)
{
    assert(seq);
    if (pos > seq->size - 1)
        return ;
    else
        seq->SeqListArr[pos] = value;
}

//查找指定元素的下标
size_t SeqListGetPos(SeqList *seq, SeqListType value)
{
    assert(seq);

    size_t i = 0;
    for (; i < seq->size; i++) {
        if (seq->SeqListArr[i] == value)
            return i;
    }
    return "找不到";
}

//在任意位置插入元素
void SeqListInsert(SeqList *seq, size_t pos, SeqListType value)
{
    assert(seq);

    if (seq->size >= SeqMaxLenth)
        return;
    else if (pos > seq->size - 1){
        return;
    }
    else {
        SeqListType i = seq->size;
        for (; i >= pos; i--) {
            seq->SeqListArr[i+1] = seq->SeqListArr[i];
        }
        seq->SeqListArr[pos] = value;
    }
    ++seq->size;
}

//指定下标删除元素
void SeqListErase(SeqList *seq, size_t pos)
{
    assert(seq);

    if (pos > seq->size)
        return;
    else{
        while (pos < seq->size) {
            seq->SeqListArr[pos] = seq->SeqListArr[pos + 1];
            pos++;
        }
    }
    --seq->size;
}

//指定元素删除，如果该元素多次出现，只删除第一次出现的该元素
void SeqListRemove(SeqList *seq, SeqListType value)
{
    assert(seq);

    SeqListType i = 0;
    for (; i < seq->size; i++) {
        if (seq->SeqListArr[i] == value) {
            for (; i < seq->size; ++i) {
                seq->SeqListArr[i] = seq->SeqListArr[i + 1];
            }
            --seq->size;
        }
        else
            return"找不到该元素";
    }
}

//指定元素删除，如果该元素多次出现，删除所有
void SeqListRemoveAll(SeqList *seq, SeqListType value)
{
    assert(seq);

    SeqListType i = 0;
    SeqListType k = 0;
    for (; i < seq->size; i++) {
        if (seq->SeqListArr[i] != value) {
            seq->SeqListArr[k] = seq->SeqListArr[i];
            k++;
        }
    }
    seq->size = k;
}

//打印顺序表
void SeqListPrint(SeqList *seq)
{
    assert(seq);
    printf("size = %ld\n\n", seq->size);
    size_t i = 0;
    for (; i < seq->size; i++)
    {
        printf("[%p:][%c]\n", &seq->SeqListArr[i], seq->SeqListArr[i]);
    }
    printf("\n");
}


//test.c

#include"SeqList.h"

void TestSeqListInit()  
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPrint(&seq);
}

void TestSeqListPushBack()
{
    SeqList seq;
    SeqListInit(&seq);
    printf("尾插前\n");
    SeqListPrint(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("在尾部依次插入'abcdef'后\n");
    SeqListPrint(&seq);
}

void TestSeqListPopBack()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("尾删前\n");
    SeqListPrint(&seq);
    SeqListPopBack(&seq);
    printf("尾删后\n");
    SeqListPrint(&seq);
}

void TestSeqListPushStart()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("头插前\n");
    SeqListPrint(&seq);
    SeqListPushStart(&seq, 'z');
    printf("头插入'z'后\n");
    SeqListPrint(&seq);
}

void TestSeqListPopStart()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("头删前\n");
    SeqListPrint(&seq);
    SeqListPopStart(&seq);
    printf("头删后\n");
    SeqListPrint(&seq);
}

SeqListType TestSeqListGet()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    SeqListPrint(&seq);
    printf("寻找下标为1的元素:");
    printf("[%c]\n\n", SeqListGet(&seq, 1));
}

void TestSeqListSetList()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("修改前\n");
    SeqListPrint(&seq);
    SeqListSetList(&seq, 2, 'g');
    printf("将下标为2的元素修改为'g'后\n");
    SeqListPrint(&seq);
}

void TestSeqListGetPos()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("查找不存在的元素x\n");
    printf("%s\n", SeqListGetPos(&seq, 'x'));
    printf("查找存在的元素b\n");
    printf("下标为：%d\n", SeqListGetPos(&seq, 'b'));
}

void TestSeqListInsert()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("插入前\n");
    SeqListPrint(&seq);
    SeqListInsert(&seq, 2, 'g');
    printf("在下标为2处插入元素'g'后\n");
    SeqListPrint(&seq);
}

void TestSeqListErase()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("删除前\n");
    SeqListPrint(&seq);
    SeqListErase(&seq, 1);
    printf("删除后\n");
    SeqListPrint(&seq);
}

void TestSeqListRemove()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("删除前\n");
    SeqListPrint(&seq);
    SeqListRemove(&seq, 'c');
    printf("删除后\n");
    SeqListPrint(&seq);
}

void TestSeqListRemoveAll()
{
    SeqList seq;
    SeqListInit(&seq);
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'a');
    SeqListPushBack(&seq, 'b');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'c');
    SeqListPushBack(&seq, 'd');
    SeqListPushBack(&seq, 'e');
    SeqListPushBack(&seq, 'f');
    printf("删除前\n");
    SeqListPrint(&seq);
    SeqListRemoveAll(&seq, 'c');
    printf("删除后\n");
    SeqListPrint(&seq);
}


int main()
{
    TestSeqListInit();
    TestSeqListPushBack();
    TestSeqListPopBack();
    TestSeqListPushStart();
    TestSeqListPopStart();
    TestSeqListGet();
    TestSeqListSetList();
    TestSeqListGetPos();
    TestSeqListInsert();
    TestSeqListErase();
    TestSeqListRemove();
    TestSeqListRemoveAll();
    system("pause");
    return 0;
}