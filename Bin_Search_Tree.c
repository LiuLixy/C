//Search_Tree.h

#pragma once

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

typedef char SearchTreeType;

typedef struct SearchTreeNode {
	SearchTreeType key;
	struct SearchTreeNode* lchild;
	struct SearchTreeNode* rchild;
}SearchTreeNode;

void SearchTreeInit(SearchTreeNode** root);

void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key);

SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find);

void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key);


//Search_Tree.c

#include"Search_Tree.h"

void SearchTreeInit(SearchTreeNode** root) {
	if (root == NULL) {
		return;
	}
	*root = NULL;
}

SearchTreeNode* CreateSearchTreeNode(SearchTreeType key) {
	SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
	new_node->key = key;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

void DestorySearchTreeNode(SearchTreeNode* ptr) {
	free(ptr);
}

void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key) {
	if (root == NULL) {
		return;
	}
	SearchTreeNode* new_node = CreateSearchTreeNode(key);
	if (*root == NULL) {
		*root = new_node;
	}
	if (key > (*root)->key) {
		SearchTreeInsert(&(*root)->rchild, key);
	} else if (key < (*root)->key) {
		SearchTreeInsert(&(*root)->lchild, key);
	} else
		return;
}

SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find) {
	if (root == NULL) {
		return NULL;
	}
	SearchTreeNode* cur = root;
	if (to_find > cur->key) {
		return SearchTreeFind(root->rchild, to_find);
	} else if (to_find < cur->key) {
		return SearchTreeFind(root->lchild, to_find);
	} else
		return cur;
}


void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key) {
	if (root == NULL) {
		return;
	}
	if (*root == NULL) {
		return;
	}
	//先找到要删除的节点cur，pre为cur的上一个节点
	SearchTreeNode* cur = *root;
	SearchTreeNode* pre = cur;
	while (1) {
		if (key == cur->key)
			break;
		else if (key > cur->key) {
			pre = cur;
			cur = cur->rchild;
		} else if (key < cur->key) {
			pre = cur;
			cur = cur->lchild;
		}
}
	if (cur != NULL) {
		if (cur->lchild == NULL && cur->rchild == NULL) {
			//要删除的节点没有左右孩子节点
			if (cur == *root) {
				*root = NULL;
				DestorySearchTreeNode(cur);
			}
			if(pre->key > cur->key) {
				pre->lchild = NULL;
			} else
				pre->rchild = NULL;
			DestorySearchTreeNode(cur);
		} else if (cur->lchild != NULL && cur->rchild != NULL) {
			//要删除的节点有左右孩子节点
			SearchTreeNode* ptr = cur->rchild;
			SearchTreeNode* prev = cur;
			while (ptr->lchild != NULL) {
				prev = ptr;
				ptr = ptr->lchild;
			}
			cur->key = ptr->key;
			if (prev == cur) {
				prev->rchild = ptr->rchild;
			} else { 
				prev->lchild = ptr->rchild; 
			}
			DestorySearchTreeNode(ptr);
		}
		else if (cur->lchild != NULL && cur->rchild == NULL) {
			//要删除的节点只有左孩子节点，没有右孩子节点
			if (cur == *root) {
				*root = (*root)->lchild;
				DestorySearchTreeNode(cur);
			}
			SearchTreeNode* to_delete_lchild = cur->lchild;
			cur->key = to_delete_lchild->key;
			cur->lchild = to_delete_lchild->lchild;
			cur->rchild = to_delete_lchild->rchild;
			DestorySearchTreeNode(to_delete_lchild);
		} else {
			//要删除的节点有右孩子节点，没有左孩子节点
			if (cur == *root) {
				*root = (*root)->rchild;
				DestorySearchTreeNode(cur);
			}
			SearchTreeNode* to_delete_rchild = cur->rchild;
			cur->key = to_delete_rchild->key;
			cur->lchild = to_delete_rchild->lchild;
			cur->rchild = to_delete_rchild->rchild;
		}
	}
}


///////////////////////////////////
///////////以下是测试代码//////////
///////////////////////////////////

#include<windows.h>

#define TEST_HEADER printf("\n============%s===========\n", __FUNCTION__)

void PreOrder(SearchTreeNode* root) {
	if (root == NULL) {
		return;
	}
	printf("%c ", root->key);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

void InOrder(SearchTreeNode* root) {
	if (root == NULL) {
		return;
	}
	InOrder(root->lchild);
	printf("%c ", root->key);
	InOrder(root->rchild);
}

void TestInit() {
	TEST_HEADER;
	SearchTreeNode* root;
	SearchTreeInit(&root);
}

void TestInsert() {
	TEST_HEADER;
	SearchTreeNode* root;
	SearchTreeInit(&root);
	SearchTreeInsert(&root, 'd');
	SearchTreeInsert(&root, 'b');
	SearchTreeInsert(&root, 'e');
	SearchTreeInsert(&root, 'a');
	SearchTreeInsert(&root, 'f');
	SearchTreeInsert(&root, 'c');
	SearchTreeInsert(&root, 'g');
	printf("先序遍历结果：");
	PreOrder(root);
	printf("\n");
	printf("中序遍历结果：");
	InOrder(root);
	printf("\n");
}

void TestFind() {
	TEST_HEADER;
	SearchTreeNode* root;
	SearchTreeInit(&root);
	SearchTreeInsert(&root, 'd');
	SearchTreeInsert(&root, 'b');
	SearchTreeInsert(&root, 'e');
	SearchTreeInsert(&root, 'a');
	SearchTreeInsert(&root, 'f');
	SearchTreeInsert(&root, 'c');
	SearchTreeInsert(&root, 'g');
	SearchTreeNode* ret = SearchTreeFind(root, 'c');
	printf("ret expect c, actual %c\n", ret->key);
    ret = SearchTreeFind(root, 'x');
	printf("ret expect NULL, actual 0x%p\n", ret);
}

void TestRemove() {
	TEST_HEADER;
	SearchTreeNode* root;
	SearchTreeInit(&root);
	SearchTreeInsert(&root, 'd');
	SearchTreeInsert(&root, 'b');
	SearchTreeInsert(&root, 'e');
	SearchTreeInsert(&root, 'a');
	SearchTreeInsert(&root, 'f');
	SearchTreeInsert(&root, 'c');
	SearchTreeInsert(&root, 'g');
	
	SearchTreeRemove(&root, 'd');
	InOrder(root);
	printf("\n");
	SearchTreeRemove(&root, 'c');
	InOrder(root);
	printf("\n");
	SearchTreeRemove(&root, 'f');
	InOrder(root);
	printf("\n");
	SearchTreeRemove(&root, 'b');
	InOrder(root);
}

int main() {
	TestInit();
	TestInsert();
	TestFind();
	TestRemove();
	system("pause");
	return 0;
}