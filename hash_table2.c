//hash_table2.h

#pragma once

#include<stddef.h>

#define HashMaxSize 1000

typedef int KeyType;
typedef int ValType;

typedef size_t (*HashFunc)(KeyType key);

typedef struct HashElem {
  KeyType key;
  ValType value;
  struct HashElem* next;
}HashElem;

// 数组的每一个元素是一个不带头节点的链表
// 对于空链表，我们使用 NULL 来表示
typedef  struct HashTable {
  HashElem* data[HashMaxSize];
  size_t size;
  HashFunc hash_func;
}HashTable;

void HashInit(HashTable* ht, HashFunc hash_func);

//约定哈希表中不能包含 key 相同的值。
int HashInsert(HashTable* ht, KeyType key, ValType value);

int HashFind(HashTable* ht, KeyType key, ValType* value);

void HashRemove(HashTable* ht, KeyType key);

size_t HashSize(HashTable* ht);

int HashEmpty(HashTable* ht);

void HashDestory(HashTable* ht);



//hash_table2.c

#include "hash_table2.h"
#include<stdlib.h>

void HashInit(HashTable* ht, HashFunc hash_func) {
  ht->size = 0;
  ht->hash_func = hash_func;
  size_t i = 0;
  for (; i < HashMaxSize; ++i) {
    ht->data[i] = NULL;
  }
}

HashElem* CreateHashElem(KeyType key, ValType value) {
  HashElem* new_node = (HashElem*)malloc(sizeof(HashElem));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  return new_node;
}

HashElem* HashBucketFind(HashElem* head, KeyType key) {
  HashElem* cur = head;
  for (; cur != NULL; cur = cur->next) {
    if (cur->key == key) {
      return cur;
    }
  }
  return NULL;
}

int HashBucketFindCurAndPrev(HashElem* head, KeyType key, 
                HashElem** cur_output, HashElem** prev_output) {
  HashElem* prev = NULL;
  HashElem* cur = head;
  for (; cur != NULL; prev = cur, cur = cur->next) {
    if (cur->key == key) {
      *cur_output = cur;
      *prev_output = prev;
      return 1;
    }
  }
  return 0;
}

int HashInsert(HashTable* ht, KeyType key, ValType value) {
  if (ht == NULL) {
    return 0;
  }
  //1. 根据hash函数，将key转化成对应的数组下标
  size_t offset = ht->hash_func(key);
  //2. 判定当前的key在链表是是否存在
  HashElem* result = HashBucketFind(ht->data[offset], key);
  if (result != NULL) {
    //  a) 如果存在，就认为插入失败
    return 0;
  } else {
    //  b) 如果不存在，就把当前元素头插到链表中
    HashElem* new_node = CreateHashElem(key, value);
    new_node->next = ht->data[offset];
    ht->data[offset] = new_node;
    ++ht->size;
    return 1;
  }
}

int HashFind(HashTable* ht, KeyType key, ValType* value) {
  if (ht == NULL || value == NULL) {
    return 0;
  }
  //1. 根据 key 找到对应的哈希桶
  size_t offset = ht->hash_func(key);
  //2. 对该hash桶进行链表查找
  HashElem* ret = HashBucketFind(ht->data[offset], key);
  //  a) 如果链表上没有找到对应key，查找失败，不存在
  if (ret == NULL) {
    return 0;
  } else {
    //  b) 如果链表上已经存在了对应的key，就把对应节点的value返回出来
    *value = ret->value;
    return 1;
  } 
}

void DestoryHashElem(HashElem* ptr) {
  free(ptr);
}

void HashRemove(HashTable* ht, KeyType key) {
  if (ht == NULL) {
    return;
  }
  //1. 根据key找到对应的哈希桶
  size_t offset = ht->hash_func(key);
  //2. 查找key这个元素是否在哈希桶的链表上
  HashElem* cur = NULL;
  HashElem* prev = NULL;
  int ret = HashBucketFindCurAndPrev(ht->data[offset], key, &cur, &prev);
  if (ret == 0) {
    // a) key没有找到，直接返回
    return;
  } 
  if (cur == ht->data[offset]) {
    // 要删除的节点是链表的头节点
    ht->data[offset] = cur->next;
  } else {
      // 要删除的节点是链表的中间位置
      prev->next = cur->next;
  }
  DestoryHashElem(cur);
  --ht->size;
  return;
}

size_t HashSize(HashTable* ht) {
  if (ht == NULL) {
    return 0;
  }
  return ht->size;
}

int HashEmpty(HashTable* ht) {
  if (ht == NULL) {
    return 1;
  }
  return ht->size == 0 ? 1 : 0;
}

void HashDestory(HashTable* ht) {
  if (ht == NULL) {
    return;
  }
  // 1. size 置为 0
  ht->size = 0;
  // 2. hash_func 置为 NULL
  ht->hash_func = NULL;
  // 3. 销毁hash桶上的每一个链表
  size_t i = 0;
  for(; i < HashMaxSize; ++i) {
    HashElem* cur = ht->data[i];
    while (cur != NULL) {
      HashElem* to_delete = cur;
      cur = cur->next;
      DestoryHashElem(to_delete);
    }
  }
}


/////////////////////////////////////
/////////以下是测试代码//////////////
/////////////////////////////////////
#if 1

#include<stdio.h>
#define TEST_HEADER printf("\n==============%s=============\n", __FUNCTION__)

void HashPrintInt(HashTable* ht, const char* msg) {
  printf("[%s]\n", msg);
  size_t i = 0;
  for (; i < HashMaxSize; ++i) {
    if (ht->data[i] == NULL) {
      continue;
    }
    printf("[%lu] ", i);
    HashElem* cur = ht->data[i];
    for (; cur != NULL; cur = cur->next) {
      printf("%d:%d; ", cur->key, cur->value);
    } 
    printf("\n");
  }
}

size_t HashFuncDefault(KeyType key) {
  return key % HashMaxSize;
}

void TestInit() {
  TEST_HEADER;
  HashTable ht;
  HashInit(&ht, HashFuncDefault);
  printf("size expect 0, actual %lu\n", ht.size);
  printf("hash_func expect %p, actual %p\n", HashFuncDefault, ht.hash_func);
  size_t i = 0;
  for (; i < HashMaxSize; ++i) {
    if (ht.data[i] != NULL) {
      printf("ht data[%lu] error", i);
    }
  }
}

void TestInsert() {
  TEST_HEADER;
  HashTable ht; 
  HashInit(&ht, HashFuncDefault);
  HashInsert(&ht, 1, 100);
  HashInsert(&ht, 2, 200);
  HashInsert(&ht, 1001, 300);
  HashInsert(&ht, 1002, 400);
  HashInsert(&ht, 1001, 500);
  
  HashPrintInt(&ht, "插入四个元素");
}

void TestFind() {
  TEST_HEADER;
  HashTable ht;
  HashInit(&ht, HashFuncDefault);
  HashInsert(&ht, 1, 100);
  HashInsert(&ht, 2, 200);
  HashInsert(&ht, 1001, 300);
  HashInsert(&ht, 1002, 400);

  int ret = 0;
  int value = 0;
  ret = HashFind(&ht, 1, &value);
  printf("ret expect 1, actual %d\n", ret);
  printf("key 1, expect 100, actual %d\n", value);

  ret = HashFind(&ht, 1001, &value);
  printf("ret expect 1, actual %d\n", ret);
  printf("key 1001, expect 300, actual %d\n", value);

  ret = HashFind(&ht, 1003, &value);
  printf("ret expect 0, actual %d\n", ret);
  //printf("key 1001, expect 300, actual %d\n", value);
}

void TestRemove() {
  TEST_HEADER;
  HashTable ht;
  HashInit(&ht, HashFuncDefault);
  HashInsert(&ht, 1, 100);
  HashInsert(&ht, 2, 200);
  HashInsert(&ht, 1001, 300);
  HashInsert(&ht, 1002, 400);
  
  HashRemove(&ht, 1);
  int ret = 0;
  int value = 0;
  ret = HashFind(&ht, 1, &value);
  printf("ret expect 0, actual %d\n", ret);
  ret = HashFind(&ht, 1001, &value);
  printf("ret expect 1, actual %d\n", ret);
  printf("value expect 300, actual %d\n", value);
  
  HashRemove(&ht, 1001);
  ret = HashFind(&ht, 1001, &value);
  printf("ret expect 0, actual %d\n", ret);
}

void TestSize() {
  TEST_HEADER;
  HashTable ht;
  HashInit(&ht, HashFuncDefault);
  HashInsert(&ht, 1, 100);
  HashInsert(&ht, 2, 200);
  HashInsert(&ht, 1001, 300);
  HashInsert(&ht, 1002, 400);

  int ret = HashSize(&ht);
  printf("size expect 4, actual %d\n", ret);
  HashRemove(&ht, 1);
  HashRemove(&ht, 2);
  ret = HashSize(&ht); 
  printf("size expect 2, actual %d\n", ret);
}

void TestDestory() {
  TEST_HEADER;
  HashTable ht;
  HashInit(&ht, HashFuncDefault);
  HashInsert(&ht, 1, 100);
  HashInsert(&ht, 2, 200);
  HashInsert(&ht, 1001, 300);
  HashInsert(&ht, 1002, 400);
  HashDestory(&ht);
  int ret = HashEmpty(&ht);
  printf("ret expect 1, actual %d\n", ret);
}

int main() {
  TestInit();
  TestInsert();
  TestFind();
  TestRemove();
  TestSize();
  TestDestory();
  return 0;
}

#endif
