//heap.h
#pragma once

#include<stddef.h>

#define HeapMaxSize 1000
typedef int HeapType;

typedef int(*Compare)(HeapType a, HeapType b);

typedef struct Heap {
    HeapType data[HeapMaxSize];
    size_t size;
    Compare cmp;
}Heap;

void HeapInit(Heap* heap, Compare compare);

void HeapInsert(Heap* heap, HeapType value);

// 取堆顶元素 
int HeapRoot(Heap* heap, HeapType* value);

// 删除堆顶元素 
void HeapErase(Heap* heap);

int HeapEmpty(Heap* heap);

size_t HeapSize(Heap* heap);

void HeapDestroy(Heap* heap);


////////////////////////////////////////////////////////////


//heap.c
#include"heap.h"

int Less(HeapType a, HeapType b)
{
    return a < b;
}

void HeapInit(Heap* heap, Compare compare)
{
    if (heap == NULL ||compare == NULL) {
        return;
    }
    heap->size = 0;
    heap->cmp = compare;
    return;
}

void Swap(HeapType* a, HeapType* b)
{
    HeapType tmp = *a;
    *a = *b;
    *b = tmp;
}

void AdjustUp(HeapType data[], size_t size, Compare cmp, size_t index) 
{
    if (index >= size) {
        return;
    }
    //1.先找到当前节点对应的父节点
    size_t child = index;
    size_t parent = (child - 1) / 2;
    while (child > 0) {
        //2.比较父节点和子节点的大小关系，如果子节点值比父节点小，交换父子节点的值
        //                                如果子节点的值比父节点大，说明调整完成
        if (cmp(data[child], data[parent])) {
            Swap(&data[child], &data[parent]);
        } else {
            break;
        }
    }
    //3.将当前的父节点作为新的子节点，再去找子节点的父节点，循环进行比较和交换
    child = parent;
    parent = (child - 1) / 2;
    //4.子节点下标等于0，循环结束
}

void AdjustDown(HeapType data[], size_t size, Compare cmp, size_t index)
{
    //1.设定一个 parent 指向开始的位置，找到对应的子树节点
    size_t parent = index;
    //2.设定一个 child 指向 parent 的左子树
    size_t child = 2 * parent + 1;
    while (child < size) {
        //3.判定 child 和 child + 1 的大小关系
        //      如果 child + 1 的值比 child 小，就让child = child + 1
        if (child + 1 < size && cmp(data[child + 1], data[child])) {
            child = child + 1;
        }
        //4.如果 parent 比 child 的值大，就需要进行交换，否则说明已经调整完成了
        if (cmp(data[child], data[parent])) {
            Swap(&data[child], &data[parent]);
        } else {
            break;
        }
        //5.parent 赋值成 child， child 在重新赋值成 parent 的左孩子节点
        parent = child;
        child = parent * 2 + 1;
    }
    return;
}

void HeapInsert(Heap* heap, HeapType value)
{
    if (heap == NULL) {
        return;
    }
    if (heap->size >= HeapMaxSize) {
        return;
    }
    heap->data[heap->size++] = value;
    AdjustUp(heap->data, heap->size, heap->cmp, heap->size - 1);
}

int HeapRoot(Heap* heap, HeapType* value)
{
    if (heap == NULL) {
        return 0;
    }
    if (heap->size == 0) {
        return 0;
    }
    *value = heap->data[0];
    return 1;
}

void HeapErase(Heap* heap)
{
    if (heap == NULL) {
        return;
    }
    if (heap->size == 0) {
        return;
    }
    Swap(&heap->data[0], &heap->data[heap->size - 1]);
    --heap->size;
    AdjustDown(heap->data, heap->size, heap->cmp, 0);
}

int HeapEmpty(Heap* heap)
{
    if (heap == NULL) {
        return 0;
    }
    return heap->size == 0 ? 1 : 0;
}

size_t HeapSize(Heap* heap)
{
    if (heap == NULL) {
        return 0;
    }
    return heap->size;
}

void HeapDestroy(Heap* heap)
{
    if (heap == NULL) {
        return;
    }
    heap->size = 0;
    return;
}


/////////////////////////////////////////
////////////以下是测试代码///////////////
/////////////////////////////////////////

#include<stdio.h>

#define TEST_HEADER printf("\n==============%s===============\n", __FUNCTION__)

void HeapPrintChar(Heap* heap, const char* msg)
{
    printf("%s\n", msg);
    size_t i = 0;
    for (; i < heap->size; ++i) {
        printf("[%lu]: %d ", i, heap->data[i]);
    }
    printf("\n");
}

void TestInit()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    printf("heap->size expect 0, actual %lu\n", heap.size);
    printf("heap->cmp expect %p, actual %p\n", Less, heap.cmp);
}

void TestInsert()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");
}

void TestRoot()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");
    HeapType value = 0;
    int ret = HeapRoot(&heap, &value);
    printf("ret expect 1, actual %d\n", ret);
    printf("value expect 5, actual %d\n", value);
}

void TestErase()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");

    HeapErase(&heap);
    HeapPrintChar(&heap, "删除堆顶元素");
}

void TestEmpty()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");

    int ret = HeapEmpty(&heap);
    printf("ret expect 0, actual %d\n", ret);
}

void TestSize()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");

    size_t size = HeapSize(&heap);
    printf("size expect 9, actual %lu\n", size);
}

void TestDestory()
{
    TEST_HEADER;
    Heap heap;
    HeapInit(&heap, Less);
    HeapInsert(&heap, 5);
    HeapInsert(&heap, 8);
    HeapInsert(&heap, 43);
    HeapInsert(&heap, 55);
    HeapInsert(&heap, 29);
    HeapInsert(&heap, 96);
    HeapInsert(&heap, 244);
    HeapInsert(&heap, 642);
    HeapInsert(&heap, 445);
    HeapPrintChar(&heap, "插入九个元素");
    HeapDestroy(&heap);
    HeapPrintChar(&heap, "销毁堆");
}

int main()
{
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestEmpty();
    TestSize();
    TestDestory();
    system("pause");
    return 0;
}