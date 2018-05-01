//bin_tree.h
//bin_tree.h
#pragma once

#include<stddef.h>

typedef char TreeNodeType;

typedef struct TreeNode {
    TreeNodeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

#define SeqStackMaxSize 1000

typedef char SeqStackType;

typedef struct SeqStack {
    SeqStackType data[SeqStackMaxSize];
    size_t size;
} SeqStack;

void TreeInit(TreeNode** root);
void PreOrder(TreeNode* root);     //先序遍历
void InOrder(TreeNode* root);      //中序遍历
void PostOrder(TreeNode* root);    //后序遍历
TreeNode* CreateTreeNode(TreeNodeType value);
TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node);
void TreeDestory(TreeNode** root);
TreeNode* TreeClone(TreeNode* root);
size_t TreeSize(TreeNode* root);
size_t TreeLeafSize(TreeNode* root);
size_t TreeKLevelSize(TreeNode* root, int K);
size_t TreeHeight(TreeNode* root);
TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find);
TreeNode* LChild(TreeNode* node);
TreeNode* RChild(TreeNode* node);
TreeNode* Parent(TreeNode* root, TreeNode* node);
void SeqStackInit(SeqStack* stack);
void SeqStackPush(SeqStack* stack, SeqStackType value);
void SeqStackPop(SeqStack* stack);
int GetTop(SeqStack* stack, SeqStackType* value);
void PreOrderByLoop(TreeNode* root);//非递归的方法实现先序遍历  
void InOrderByLoop(TreeNode* root);//非递归的方法实现中序遍历
void PostOrderByLoop(TreeNode* root);//非递归的方法实现后序遍历
void TreeMirror(TreeNode* root);//二叉树的翻转

//////////////////////////////////////////////////////////////////////////////
///////我是分割线
//////////////////////////////////////////////////////////////////////////////

//bin_tree.c
#include"Bin_Tree.h"
#include<stdlib.h>

TreeNode* CreateTreeNode(TreeNodeType value)
{
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void TreeInit(TreeNode** root)
{
    if (root == NULL) {
        return;
    }
    *root = NULL;
}

void PreOrder(TreeNode* root) 
{
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void InOrder(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    InOrder(root->lchild);
    printf("%c ", root->data);
    InOrder(root->rchild);
}

void PostOrder(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    PostOrder(root->lchild);
    PostOrder(root->rchild);
    printf("%c ", root->data);
}

TreeNode* _TreeCreate(TreeNodeType array[], size_t size, size_t* index, TreeNodeType null_node)
{
    if (index == NULL) {
        return NULL;
    }
    if (*index >= size) {
        //构建完成
        return NULL;
    }
    if (array[*index] == null_node) {
        return NULL;
    }
    TreeNode* new_node = CreateTreeNode(array[*index]);//先创建根节点
    ++(*index);
    new_node->lchild = _TreeCreate(array, size, index, null_node);//创建左子树
    ++(*index);
    new_node->rchild = _TreeCreate(array, size, index, null_node);//创建右子树
    return new_node;
}


TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node)
{
    size_t index = 0; // 表示当前读到了数组的第几个元素
    return _TreeCreate(array, size, &index, null_node);
}

void DestoryNode(TreeNode* ptr)
{
    free(ptr);
}

void TreeDestory(TreeNode** root)
{
    if (root == NULL) {
        return;
    }
    if (*root == NULL) {
        return;
    }
    TreeDestory(&(*root)->lchild);
    TreeDestory(&(*root)->lchild);
    DestoryNode(*root);
    *root = NULL;
}

TreeNode* TreeClone(TreeNode* root)
{
    if (root == NULL) {
        return NULL;
    }
    TreeNode* new_node = CreateTreeNode(root->data);
    new_node->lchild = TreeClone(root->lchild);
    new_node->rchild = TreeClone(root->rchild);
    return new_node;
}

//void _TreeSize(TreeNode* root, size_t *size)
//{
//  if (root == NULL || size == NULL) {
//      return;
//  }
//  ++(*size);
//  _TreeSize(root->lchild, size);
//  _TreeSize(root->rchild, size);
//}

//size_t TreeSize(TreeNode* root)
//{
//  if (root == NULL) {
//      return 0;
//  }
//  size_t size = 0;
//  _TreeSize(root, &size);
//  return size;
//}

size_t TreeSize(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    return 1 + TreeSize(root->lchild) + TreeSize(root->rchild);
}

size_t TreeLeafSize(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL) {
        return 1;
    }
    return TreeLeafSize(root->lchild) + TreeLeafSize(root->rchild);
}

size_t TreeKLevelSize(TreeNode* root, int K)
{
    if (root == NULL || K < 1) {
        return 0;
    }
    if (K == 1) {
        return 1;
    }
    return TreeKLevelSize(root->lchild, K - 1) + TreeKLevelSize(root->rchild, K - 1);
}

size_t TreeHeight(TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    size_t lheight = TreeHeight(root->lchild);
    size_t rheight = TreeHeight(root->rchild);
    return lheight > rheight ? lheight + 1 : rheight + 1;
}

TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find)
{
    if (root == NULL) {
        return NULL;
    }
    if (root->data == to_find) {
        return root;
    }
    TreeNode* lresult = TreeFind(root->lchild, to_find);
    TreeNode* rresult = TreeFind(root->rchild, to_find);
    return lresult != NULL ? lresult : rresult;
}

TreeNode* LChild(TreeNode* node)//给出一个节点，求左孩子节点
{
    if (node == NULL) {
        return NULL;
    }
    return node->lchild;
}

TreeNode* RChild(TreeNode* node)//给出一个节点，求右孩子节点
{
    if (node == NULL) {
        return NULL;
    }
    return node->rchild;
}

TreeNode* Parent(TreeNode* root, TreeNode* node)
{
    if (root == NULL || node == NULL) {
        return NULL;
    }
    if (root->lchild == node || root->rchild == node) {
        return root;
    }
    TreeNode* lresult = Parent(root->lchild, node);
    TreeNode* rresult = Parent(root->rchild, node);
    return lresult != NULL ? lresult : rresult;
}
void SeqStackInit(SeqStack* stack)
{
    if (stack == NULL) {
        return;
    }
    stack->size = 0;
}

void SeqStackPush(SeqStack* stack, SeqStackType value)
{
    if (stack == NULL) {
        return;
    }
    if (stack->size >= SeqStackMaxSize)
        return;
    stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack)
{
    if (stack == 0) {
        return;
    }
    if (stack->size == 0)
        return;
    --stack->size;
}

int GetTop(SeqStack* stack, SeqStackType* value)
{
    if (stack == NULL) {
        return 0;
    }
    if (stack->size == 0)
        return 0;
    *value = stack->data[stack->size - 1];
    return 1;
}

void PreOrderByLoop(TreeNode* root)//非递归先序遍历树
{
    if (root == NULL) {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack, root);
    while (1) {
        TreeNode* top = NULL;
        GetTop(&stack, &top);
        if (top == NULL) {
            //遍历完成
            break;
        }
        //访问当前栈顶元素
        printf("%c ", top->data);
        //将栈顶元素出栈
        SeqStackPop(&stack);
        //把当前元素的右子树和左子树分别入栈
        if (top->rchild != NULL) {
            SeqStackPush(&stack, top->rchild);
        }
        if (top->lchild != NULL) {
            SeqStackPush(&stack, top->lchild);
        }
    }
    printf("\n");
}

void InOrderByLoop(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    TreeNode* cur = root;
    while (1) {
        //1.从根节点出发，尝试找到当前树的最左侧节点，每次经过一个节点，就把这个节点入栈.
        while (cur != NULL) {
            SeqStackPush(&stack, cur);
            cur = cur->lchild;
        }
        //2.取栈顶元素，访问，并将该元素出栈。
        TreeNode* top = NULL;
        GetTop(&stack, &top);
        if (top == NULL) {
            break;
        }
        printf("%c ", top->data);
        SeqStackPop(&stack);
        //3.处理当前元素的右子树，回到循环开始，再去找右子树的最左侧节点
        cur = top->rchild;
    }
}

void PostOrderByLoop(TreeNode* root)
{
    if (root == NULL) {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    TreeNode* cur = root;
    TreeNode* pre = NULL;//保存当前节点的上一个位置
    while (1) {
        while (cur != NULL) {
            SeqStackPush(&stack, cur);
            cur = cur->lchild;
        }
        TreeNode* top = NULL;
        GetTop(&stack, &top);
        if (top == NULL) {
            break;
        }
        //取出栈顶元素之后，需要满足一下两个条件之一，才能访问top
        //   1. top的右子树为空
        //   2. top的右子树已经被访问过了
        //   否则就需要循环处理top的右子树
        if (top->rchild == NULL || top->rchild == pre) {
            printf("%c ", top->data);
            SeqStackPop(&stack);
            pre = top;
        } else {
            cur = top->rchild;
        }
    }
    printf("\n");
}

void TreeMirror(TreeNode* root)//二叉树的翻转
{
    if (root == NULL) {
        return;
    }
    TreeNode* tmp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = tmp;
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}


///////////////////////////////////////////////
/////////////以下是测试代码/////////////////////
///////////////////////////////////////////////

#include <stdio.h>
#include <String.h>

#define TEST_HEADER printf("\n==============%s==============\n", __FUNCTION__)

void TestInit()
{
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
}

void TestPreOrder()
{
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    root = a;

    printf("先序遍历：\n");
    PreOrder(root);
    printf("\n");
}

void TestInOrder()
{
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    root = a;

    printf("中序遍历：\n");
    InOrder(root);
    printf("\n");
}

void TestPostOrder()
{
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    root = a;

    printf("后序遍历：\n");
    PostOrder(root);
    printf("\n");
}

void TestCreate()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    printf("先序遍历结果：");
    PreOrder(root);
    printf("\n");
    printf("先序遍历结果：");
    InOrder(root);
    printf("\n");
    printf("先序遍历结果：");
    PostOrder(root);
    printf("\n");
}

void TestDestory()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    TreeDestory(&root);
    printf("root expect NULL, actual %p\n", root);
}

void TestClone()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    TreeNode* new_root = TreeClone(root);
    printf("root = 0x%p, new_root = 0x%p\n", root, new_root);
    printf("先序遍历结果：");
    PreOrder(new_root);
    printf("\n");
    printf("先序遍历结果：");
    InOrder(new_root);
    printf("\n");
    printf("先序遍历结果：");
    PostOrder(new_root);
    printf("\n");
}

void TestSize()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    printf("size expect 7, actual %lu\n", TreeSize(root));
}

void TestLeafSize()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    printf("LeafSize expect 3, actual %lu\n", TreeLeafSize(root));
}

void TestKLevelSize()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    printf("KLevelSize expect 3, actual %lu\n", TreeKLevelSize(root, 3));
}

void TestHeight()
{

    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    printf("Height expect 4, actual %lu\n", TreeHeight(root));
}

void TestFind()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    TreeNode* b = TreeFind(root, 'b');
    printf("result expect 0x%p, actual 0x%p\n", root->lchild, b);
}

void TestParent()
{
    TEST_HEADER;
    TreeNodeType array[] = "abd##eg###c#f##";//输入的是先序序列
    TreeNode* root = TreeCreate(array, strlen(array), '#');
    TreeNode* b = TreeFind(root, 'b');
    TreeNode* parent = Parent(root, b);
    printf("parent expect a, actual %c\n", parent->data);
}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestCreate();
    TestDestory();
    TestClone();
    TestSize();
    TestLeafSize();
    TestKLevelSize();
    TestHeight();
    TestFind();
    TestParent();
    system("pause");
    return 0;
}