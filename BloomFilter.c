//BloomFilter.h
#pragma once  
  
#include <stddef.h>  
#include "bitmap.h"  
  
#define HashFuncMaxSize 2  
#define BitMapCapacity 1024  
  
  
// 字符串哈希函数  
typedef size_t(*HashFunc)(const char*);  
  
typedef struct BloomFilter{  
    BitMap bitmap;  
    HashFunc hash_func[HashFuncMaxSize];  
}BloomFilter;  
  
// 初始化布隆过滤器 
void BloomFilterInit(BloomFilter* bf);  
  
// 插入  
void BloomFilterInsert(BloomFilter* bf, const char* str);  
  
int BloomFilterExit(BloomFilter* bf, const char* str);  
  
void BloomFilterDestory(BloomFilter* bf);  
  
// 按照当前的设计是不允许删除的 



/////////////////////////////////
//BloomFilter.c
#include "BloomFilter.h"  
#include "bitmap.h"  
#include <assert.h>  
  
  
// 哈希函数 
size_t hashfunc0(const char* str) {  
    assert(str);  
    size_t hash = 0;  
    size_t ch = 0;  
    while (ch = (size_t) *str++) {  
       hash = hash * 131 + ch;  
     }  
    return hash;  
}  
  
size_t hashfunc1(const char* str) {  
    assert(str);  
    size_t hash = 0;  
    size_t ch = 0;  
    while (ch = (size_t)*str++) {  
        hash = hash * 65599 + ch;  
    }  
    return hash;  
}  
  
//  初始化布隆过滤器  
void BloomFilterInit(BloomFilter* bf) {  
    if (bf == NULL) {  
      return;  
    }  
    // 初始化位图  
    BitMapInit(&bf->bitmap, BitMapCapacity);  
    // 初始化哈希函数
    bf->hash_func[0] = hashfunc0;  
    bf->hash_func[1] = hashfunc1;  
}  
  
int BloomFilterExit(BloomFilter* bf, const char* str) {  
    if (bf == NULL || str == NULL) {  
      return 0;  
    }  
    int i = 0;  
    for (; i < HashFuncMaxSize; ++i) {  
        size_t offset = bf->hash_func[i](str) % BitMapCapacity;  
        int n = BitMapTest(&bf->bitmap, offset);  
        if (n == 0) {  
          return 0;
        }  
    }  
    return 1;  
}  
  
void BloomFilterDestory(BloomFilter* bf) {  
    if (bf == NULL) {  
            return;  
    }  
    BitMapDestory(&bf->bitmap);  
    int i = 0;  
    for (; i < HashFuncMaxSize; ++i) {  
            bf->hash_func[i] = NULL;  
    }  
}  
  
////////////////////////////// 
///////以下为测试代码/////////  
//////////////////////////////

#if 1  
  
#include <stdio.h>  
#include <stdlib.h>  
  
#define TESTHEAD printf("------------%s-------------\n",__FUNCTION__)  
  
void TestInit() {  
    BloomFilter bf;  
    TESTHEAD;  
    BloomFilterInit(&bf);  
    printf("expect 1024, actual:%d\n", bf.bitmap.capacity);  
    printf("expect %p, actual:%p\n", hashfunc0, bf.hash_func[0]);  
    printf("expect %p, actual:%p\n", hashfunc1, bf.hash_func[1]);  
}  
  
void TestInsert() {  
    BloomFilter bf;  
    TESTHEAD;  
    BloomFilterInit(&bf);  
  
    BloomFilterInsert(&bf, "hello");  
    BloomFilterInsert(&bf, "world");  
  
    size_t offset1 = bf.hash_func[0]("hello") % BitMapCapacity;  
    size_t offset2 = bf.hash_func[1]("world") % BitMapCapacity;  
  
    int n1 = BitMapTest(&bf.bitmap, offset1);  
    int n2 = BitMapTest(&bf.bitmap, offset2);  
  
    printf("expect 1, actual:%d\n", n1);  
    printf("expect 1, actual:%d\n", n2);  
}  
  
void TestExit() {  
    BloomFilter bf;  
    TESTHEAD;  
    BloomFilterInit(&bf);  
  
    BloomFilterInsert(&bf, "hello");  
    BloomFilterInsert(&bf, "world");  
  
    int n1 = BloomFilterExit(&bf, "hello");  
    int n2 = BloomFilterExit(&bf, "world");  
    int n3 = BloomFilterExit(&bf, "bit");  
    printf("expect 1, acutal:%d\n", n1);  
    printf("expect 1, acutal:%d\n", n2);  
    printf("expect 0, acutal:%d\n", n3);  
}  
  
int main() {  
    TestInit();  
    TestInsert();  
    TestExit();  
    system("pause");  
    return 0;  
}  
  
#endif  
