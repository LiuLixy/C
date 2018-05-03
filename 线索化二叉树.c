//ThreadTree.h
#pragma once

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

typedef enum Flag{
    CHILD,
    THREAD
}Flag;

typedef char ThreadType;

typedef struct ThreadNode {
    ThreadType data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    //引入两个flag来分别表示左右指针指向的是字数还是线索
    Flag lflag;
    Flag rflag;
}ThreadNode;

ThreadNode* ThreadNodeCreate(ThreadType array[], size_t size, ThreadType invalid);

void PreThreading(ThreadNode* root);

void PreOrderByThreading(ThreadNode* root);

void InThreading(ThreadNode* root);

void InOrderByThreading(ThreadNode* root);

void PostThreading(ThreadNode* root);

//void PostOrderByThreading(ThreadNode* root);

//ThreadTree.c
#include"Thread.h"

ThreadNode* CreateThreadNode(ThreadType value)
{
    ThreadNode* new_node = (ThreadNode*)malloc(sizeof(ThreadNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->lflag = CHILD;
    new_node->rflag = CHILD;
    return new_node;
}

ThreadNode* _ThreadTreeCreate(ThreadType array[], size_t size, size_t* index, ThreadType invalid)
{
    if (index == NULL || *index >= size) {
        return NULL;
    }
    if (array[*index] == invalid) {
        return NULL;
    }
    ThreadNode* root = CreateThreadNode(array[*index]);
    ++(*index);
    root->left = _ThreadTreeCreate(array, size, index, invalid);
    ++(*index);
    root->right = _ThreadTreeCreate(array, size, index, invalid);
    return root;
}

//invalid 表示用哪个特殊字符表示空节点
ThreadNode* ThreadTreeCreate(ThreadType array[], size_t size, ThreadType invalid)
{
    size_t index = 0;
    return _ThreadTreeCreate(array, size, &index, invalid);
}

void _PreThreading(ThreadNode* root, ThreadNode** prev) {
    if (root == NULL || prev == NULL) {
        return;
    }
    //访问根节点, 如果根节点的左子树为空，就把left指针指向前驱，
    //            如果当前子树的根节点的右子树为空，就把前驱的right指针指向根节点
    if (root->left == NULL) {
        root->left = *prev;
        root->lflag = THREAD;
    }
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->rflag = THREAD;
    }
    *prev = root;
    //处理左子树
    if (root->lflag == CHILD) {
        _PreThreading(root->left, prev);
    }
    //处理右子树
    if (root->rflag == CHILD) {
        _PreThreading(root->right, prev);
    }
    return;
}

void PreThreading(ThreadNode* root)
{
    ThreadNode* prev = NULL;
    _PreThreading(root, &prev);
}

void PreOrderByThreading(ThreadNode* root)
{
    if (root == NULL) {
        return;
    }
    ThreadNode* cur = root;
    while (cur != NULL) {
        while (cur->lflag == CHILD) {
            printf("%c ", cur->data);
            cur = cur->left;
        }
        printf("%c ", cur->data);
        //无论cur的right指针指向后继还是指向右子树，都被下面的逻辑覆盖
        cur = cur->right;
    }
}

void _InThreading(ThreadNode* root, ThreadNode** prev)
{
    if (root == NULL || prev == NULL) {
        return;
    }
    if (root->lflag == CHILD) {
        _InThreading(root->left, prev);
    }
    if (root->left == NULL) {
        root->left = *prev;
        root->lflag = THREAD;
    }
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->rflag = THREAD;
    }
    *prev = root;
    if (root->rflag == CHILD) {
        _InThreading(root->right, prev);
    }
}

void InThreading(ThreadNode* root)
{
    ThreadNode* prev = NULL;
    _InThreading(root, &prev);
}

void InOrderByThreading(ThreadNode* root) {
    if (root == NULL) {
        return;
    }
    //定义cur指针指向root，找到最左侧节点，并且在寻找的路径上不能访问
    ThreadNode* cur = root;
    while (cur != NULL && cur->lflag == CHILD) {
        cur = cur->left;
    }
    //进入循环，访问cur节点，如果cur为空，说明遍历完成
    while (cur != NULL) {
        printf("%c ", cur->data);
        //如果cur的right刚好是线索， cur指向 cur->right
        if (cur->rflag == THREAD) {
        cur = cur->right;
        }
        else {
            //如果cur的right是子树，需要让cur指向cur->right这个子树的最左侧节点
            cur = cur->right;
            while (cur != NULL && cur->lflag == CHILD) {
                cur = cur->left;
            }//end while
        }//end if (cur->lflag == THREAD)
    }//end while (cur != NULL)
    printf("\n");
    return;
}

void _PostTreading(ThreadNode* root, ThreadNode** prev)
{
    if (root == NULL || prev == NULL) {
        return;
    }
    //处理左子树
    if (root->lflag == CHILD) {
        _PostThreading(root->left, prev);
    }
    //处理右子树
    if (root->rflag == CHILD) {
        _InThreading(root->right, prev);
    }
    //处理根节点
    if (root->left == NULL) {
        root->left = *prev;
        root->lflag = THREAD;
    }
    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = root;
        (*prev)->rflag = THREAD;
    }
    *prev = root;
}

void PostThreading(ThreadNode* root)
{
    ThreadNode* prev = NULL;
    _PostTreading(root, &prev);
}


///////////////////////////////////
/////////以下是测试代码////////////
///////////////////////////////////

#include<stdio.h>

#define TEST_HEADER printf("\n=============%s=============\n", __FUNCTION__)

void PreOrder(ThreadNode* root)
{
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

void InOrder(ThreadNode* root)
{
    if (root == NULL) {
        return;
    }
    PreOrder(root->left);
    printf("%c ", root->data);
    PreOrder(root->right);
}

void TestCreate()
{
    TEST_HEADER;
    ThreadType array[] = "ABD##EG###C#F##";
    ThreadNode* root = ThreadTreeCreate(array, strlen(array), '#');
    printf("先序遍历结果：");
    PreOrder(root);
    printf("\n");
    printf("中序遍历结果：");
    InOrder(root);
    printf("\n");
    return;
}

void TestPreThreading()
{
    TEST_HEADER;
    ThreadType array[] = "ABD##EG###C#F##";
    ThreadNode* root = ThreadTreeCreate(array, strlen(array), '#');
    PreThreading(root);
    printf("先序遍历结果：");
    PreOrderByThreading(root);
    printf("\n");
    return;
}

void TestInThreading()
{
    TEST_HEADER;
    ThreadType array[] = "ABD##EG###C#F##";
    ThreadNode* root = ThreadTreeCreate(array, strlen(array), '#');
    InThreading(root);
    printf("中序遍历结果：");
    InOrderByThreading(root);
    printf("\n");
    return;
}

int main()
{
    TestCreate();
    TestPreThreading();
    TestInThreading();
    system("pause");
    return 0;
}