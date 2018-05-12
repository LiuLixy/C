//bitmap.h
#pragma once
#include <stdint.h>
#include <stddef.h>

typedef struct BitMap {
  uint64_t* data;
  size_t capacity; //当前位图表示最大的位
}BitMap;

void BitMapInit(BitMap* bm, size_t capacity);

// 把第 index 位置为1
void BitMapSet(BitMap* bm, size_t index);

// 把第 index 位置为0
void BitMapUnset(BitMap* bm, size_t index);

// 测试 index 位是 1 还是 0，如果是1，返回1，否则返回0
int BitMapTest(BitMap* bm, size_t index);

// 把整个位图所有的位都设为1
void BitMapFill(BitMap* bm);

// 把整个位图所有的位都设为0
void BitMapClear(BitMap* bm);

void BitMapDestory(BitMap* bm);



///////////////////////////////////////////////////////////
//bitmap.c
#include "bitmap.h"
#include <stdlib.h>
#include <string.h>

size_t DataSize(size_t capacity) {
  return capacity / (8 * sizeof(uint64_t)) + 1;
}

void GetOffset(size_t index, size_t* n, size_t* offset) {
  *n = index / (8 * sizeof(u_int64_t));
  *offset = index % (8 * sizeof(uint64_t));
}

//capacity表示的是该位图能保存的最大位是多少
void BitMapInit(BitMap* bm, size_t capacity) {
  if (bm == NULL) {
    return;
  }
  bm->capacity = capacity;
  size_t size = DataSize(capacity);
  bm->data = (uint64_t*)malloc(sizeof(uint64_t) * size);
}

// 拿 65 为例
// 数组中有两个元素， data[0] 和 data[1]
// n = index / sizeof(uint64_t) -> 1
// offset = index % sizeof(uint64_t) -> 1
// data[n] |= 1 << offset;
void BitMapSet(BitMap* bm, size_t index) {
  if (bm == NULL) {
    return;
  }
  if (index >= bm->capacity) {
    return;
  }
  size_t n, offset;
  GetOffset(index, &n, &offset);
  bm->data[n] |= (1ul << offset);
}

void BitMapUnset(BitMap* bm, size_t index) {
  if (bm == NULL) {
    return;
  }
  if (index >= bm->capacity) {
    return;
  }
  size_t n, offset;
  GetOffset(index, &n, &offset);
  bm->data[n] &= ~(1ul << offset);
}

int BitMapTest(BitMap* bm, size_t index) {
  if (bm == NULL) {
    return 0;
  }
  if (index >= bm->capacity) {
    return 0;
  }
  size_t n, offset;
  GetOffset(index, &n, &offset);
  u_int64_t ret = (bm->data[n] & (1ul << offset));
  return ret != 0 ? 1 : 0;
}

void BitMapFill(BitMap* bm) {
  if (bm == NULL) {
    return;
  }
  // 这里的size表示的是一共有多少个字节
  size_t size = sizeof(u_int64_t) * DataSize(bm->capacity);
  memset(bm->data, 0xff, size);
}

void BitMapClear(BitMap* bm) {
  if (bm == NULL) {
    return;
  } 
  memset(bm->data, 0, sizeof(uint64_t) * DataSize(bm->capacity));
}

void BitMapDestory(BitMap* bm) {
  if (bm == NULL) {
    return;
  }
  free(bm->data);
  bm->capacity = 0;
}


//////////////////////////////////
/////////以下是测试代码///////////
//////////////////////////////////

#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n==========%s=========\n", __FUNCTION__)

void TestInit() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 65);
  printf("bm.capacity expect 65, actual %lu\n", bm.capacity);
}

void TestSet() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapSet(&bm, 63);
  size_t i = 0;
  for (; i < bm.capacity / (sizeof(uint64_t) * 8) + 1; ++i) {
    printf("[%lu] %lx", i, bm.data[i]);
  }
}

void TestUnset() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapSet(&bm, 64);
  BitMapUnset(&bm, 64);

  size_t i = 0;
  for (; i < bm.capacity / (8 * sizeof(uint64_t)) + 1; ++i) {
    printf("[%lu] %lx", i, bm.data[i]); 
  }
}

void TestBitMapTest() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapSet(&bm, 63);
  int ret = BitMapTest(&bm, 63);
  printf("ret expect 1, actual %d\n", ret);
}

void TestFill() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapFill(&bm);

  size_t i = 0;
  for (; i < bm.capacity / (8 * sizeof(uint64_t)) + 1; ++i) {
    printf("[%lu] %lx", i, bm.data[i]);
  }
}

void TestClear() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapSet(&bm, 63);
  BitMapSet(&bm, 33);
  BitMapClear(&bm);

  size_t i = 0;
  for (; i < bm.capacity / (8 * sizeof(uint64_t)) + 1; ++i) {
    printf("[%lu] %lx", i, bm.data[i]);
  }
}

void TestDestory() {
  TEST_HEADER;
  BitMap bm;
  BitMapInit(&bm, 127);
  BitMapFill(&bm);
  BitMapDestory(&bm);

  size_t i = 0;
  for (; i < bm.capacity / (8 * sizeof(uint64_t)) + 1; ++i) {
    printf("[%lu] %lx", i, bm.data[i]);
  }
}

int main() {
  TestInit();
  TestSet();
  TestUnset();
  TestBitMapTest();
  TestFill();
  TestClear();
  TestDestory();
  return 0;
}



#endif
