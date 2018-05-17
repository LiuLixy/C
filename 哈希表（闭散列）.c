//闭散列方式实现哈希表

//Hash.h
#pragma once

#include<stddef.h>
#include<stdio.h>
#include<windows.h>

#define HashMaxSize 1000

typedef enum Stat {
	Empty,
	Valid,
	Invalid  //表示当前元素已被删除
} Stat;

typedef int KeyType;
typedef int ValType;

typedef size_t (*HashFunc)(KeyType key);

typedef struct HashElem {
	KeyType key;
	ValType value;
	Stat stat; // 引入一个 stat 标记来作为是否有效的标记 
} HashElem;

typedef struct HashTable {
	HashElem data[HashMaxSize];
	size_t size;
	HashFunc hash_func;
} HashTable;

void HashInit(HashTable* ht, HashFunc);

int HashInsert(HashTable* ht, KeyType key, ValType value);

// 输入key, 查找对应key的value. 
int HashFind(HashTable* ht, KeyType key, ValType* value);

void HashRemove(HashTable* ht, KeyType key);

int HashEmpty(HashTable* ht);

size_t HashSize(HashTable* ht);

void HashDestroy(HashTable* ht);


//Hash.c
#include"Hash.h"

size_t HashFuncDefault(KeyType key) {
	return key % HashMaxSize;
}

void HashInit(HashTable* ht, HashFunc hash_func) {
	if (ht == NULL) {
		return;
	}
	ht->hash_func = hash_func;
	ht->size = 0;
	size_t i = 0;
	for (; i < HashMaxSize; ++i) {
		ht->data[i].stat = Empty;
	}
	return;
}

int HashInsert(HashTable* ht, KeyType key, ValType value) {
	if (ht == NULL) {
		return 0;
	}
	//设定负载因子为0.8
	if (ht->size >= HashMaxSize * 0.8) {
		//这里认为哈希表满了，不能继续插入
		return 0;
	}
	//先找到key对应的下标
	size_t offset = ht->hash_func(key);
	while (1) {
		if (ht->data[offset].stat == Valid) {
			if (ht->data[offset].key == key) {
				//发现在哈希表中已经存在了相同的元素 key, 认为插入失败
				return 0;
			}
			//出现了哈希冲突，使用线性探测的方式查找下一个元素
			++offset;
			if (offset >= HashMaxSize) {
				offset -= HashMaxSize;
			}
		}
		else {
			//由于负载因子是 0.8， 一定能找到一个空位
			ht->data[offset].key = key;
			ht->data[offset].value = value;
			ht->data[offset].stat = Valid;
			++ht->size;
			return 1;
		}
	}
	return 0;
}

int HashFind(HashTable* ht, KeyType key, ValType* value) {
	if (ht == NULL || value == NULL) {
		return 0;
	}
	//1.通过哈希函数计算数组下标
	size_t offset = ht->hash_func(key);
	//2.从这个数组下标开始，线性的向后查找
	while (1) {
		//  a) 如果找到了某个元素的key是想要的值， 并且状态为Valid，
		//     就认为找到了，就将value赋值给输出参数
		if (ht->data[offset].key == key && ht->data[offset].stat == Valid) {
			*value = ht->data[offset].value;
			return 1;
		}
		else if (ht->data[offset].stat == Empty) {
			//  b) 如果发现当前位置的状态为 Empty，表示该key不存在
			return 0;
		}
		else {
			//  c) 继续尝试查找下一个位置
			++offset;
			if (offset >= HashMaxSize) {
				offset -= HashMaxSize;
			}
		}
	}
	return 0;
}

void HashRemove(HashTable* ht, KeyType key) {
	if (ht == NULL) {
		return;
	}
	//1. 根据key找到对应的数组下标
	size_t offset = ht->hash_func(key);
	//2. 从找到的下标开始依次遍历
	while (1) {
		if (ht->data[offset].key == key && ht->data[offset].stat == Valid) {
			//   a) 如果当前的元素key为要删除的key，并且状态为Valid
			//      就将状态置为Invalid， 并且 --size
			ht->data[offset].stat = Invalid;
			--ht->size;
			return;
		}
		else if (ht->data[offset].stat == Empty) {
			//   b) 如果当前元素的状态为Empty，表示要删除的key没有找到，
			//      不需要进行任何删除操作
			return;
		}
		else {
			//   c) 剩下的情况，就依次的取下一个元素
			++offset;
			if (offset >= HashMaxSize) {
				offset -= HashMaxSize;
			}
		}
	}
}

int HashEmpty(HashTable* ht) {
	if (ht == NULL) {
		return 1;
	}
	return ht->size == 0 ? 1 : 0;
}

size_t HashSize(HashTable* ht) {
	if (ht == NULL) {
		return 0;
	}
	return ht->size;
}

void HashDestroy(HashTable* ht) {
	size_t i = 0;
	for (; i < HashMaxSize; ++i) {
		ht->data[i].stat = Empty;
	}
	ht->size = 0;
	ht->hash_func = NULL;
	return;
}

////////////////////////////////////////
///////////以下是测试代码///////////////
////////////////////////////////////////

#define TEST_HEADER printf("\n============%s=============\n", __FUNCTION__)

void HashPrintInt(HashTable* ht, const char* msg) {
	printf("[%s]\n", msg);
	size_t i = 0;
	for (; i < HashMaxSize; ++i) {
		if (ht->data[i].stat != Empty) {
			printf("[%lu] key=%d, value=%d, stat = %d\n", i, ht->data[i].key, 
				ht->data[i].value, ht->data[i].stat);
		}
	}
}

void TestInit() {
	TEST_HEADER;
	HashTable ht;
	HashInit(&ht, HashFuncDefault);
	printf("ht->size expect 0, actual %lu\n", ht.size);
	printf("ht->hash_func expect %p, actual %p\n", HashFuncDefault, ht.hash_func);
	size_t i = 0;
	for (; i < HashMaxSize; ++i) {
		if (ht.data[i].stat != Empty) {
			printf("pos [%lu] elem error!\n", i);
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
	//HashPrintInt(&ht, "插入四个元素");
	//printf("\n");

	int value = 0;
	int ret = HashFind(&ht, 1, &value);
	printf("ret expect 1, actual %d\n", ret);
	printf("value expect 100, actual %d\n", value);

	printf("\n");
	ret = HashFind(&ht, 1001, &value);
	printf("ret expect 1, actual %d\n", ret);
	printf("value expect 300, actual %d\n", value);

	printf("\n");
	ret = HashFind(&ht, 1005, &value);
	printf("ret expect 0, actual %d\n", ret);
	//printf("value expect 100, actual %d\n", value);
}

void TestRemove() {
	TEST_HEADER;
	HashTable ht;
	HashInit(&ht, HashFuncDefault);

	HashInsert(&ht, 1, 100);
	HashInsert(&ht, 2, 200);
	HashInsert(&ht, 1001, 300);
	HashInsert(&ht, 1002, 400);
	//HashPrintInt(&ht, "插入四个元素");
	
	HashRemove(&ht, 1);
	HashPrintInt(&ht, "删除 key 为1的元素");
	int ret = 0;
	int value = 0;
	ret = HashFind(&ht, 1, &value);
	printf("ret expect 0, actual %d\n", ret);

	ret = HashFind(&ht, 1001, &value);
	printf("ret expect 1, actual %d\n", ret);
	printf("value expect 300, actual %d\n", value);
}


void TestCountNum() {
	TEST_HEADER;
	int array[] = { 1, 1, 1, 2, 2, 3, 4, 4, 5 };
	HashTable ht;
	HashInit(&ht, HashFuncDefault);
	size_t i = 0;
	for (; i < sizeof(array) / sizeof(array[0]); ++i) {
		int value = 0;
		int ret = HashFind(&ht, array[i], &value);
		if (ret == 0) {
			//没找到
			HashInsert(&ht, array[i], 1);
		}
		else {
			//该元素已经存在
			HashRemove(&ht, array[i]);
			HashInsert(&ht, array[i], value + 1);
		}
	}
	HashPrintInt(&ht, "统计的最终结果为");
}

int main() {
	TestInit();
	TestInsert();
	TestFind();
	TestRemove();
	TestCountNum();
	system("pause");
	return 0;
}