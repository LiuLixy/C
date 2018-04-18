#include<stdio.h>

typedef char LinkType;

typedef struct LinkNode {
	LinkType data;
	struct LinkNode* next;
}LinkNode；

void LinkListInit(LinkNode **head) {
	if (head == NULL) {
		return;
	}
	*head = NULL;
}

LinkNode* LinkListCreateNode(LinkType value) {
	LinkNode* ptr = (LinkNode*)malloc(sizeof(LinkNode));
	ptr->data = value;
	ptr->next = NULL;
	return ptr;
}

void LinkListDestroyNode(LinkNode* ptr) {
	//销毁，释放内存
	free(ptr);
}

LinkNode* LinkListPushBack(LinkNode** head, LinkType value) {
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

void LinkListPopBack(LinkNode** head)
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

//从尾到头打印单链表
void LinkListReversePrint(LinkNode* head) {
	if (head == NULL) {
		return;
	}
	if (hear->next != NULL){
		LinkListReversePrint(head->next);
	}
	printf("%c ", head->data);
}



//////////////////////////////
///////以下是测试代码//////////
//////////////////////////////
#define TEST_HEADER printf("\n==============%s==============\n", __FUNCTION__)

void LinkListPrintChar(LinkNode *head, const char* msg)
{
	printf("[%s]: ", msg);
	LinkNode* cur = head;
	for (; cur != NULL; cur = cur->next) {
		printf("[%c:%p] -> ", cur->data, cur);
	}
	printf("[NULL]\n\n");
}

void TestReversePrint()
{
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPrintChar(head, "尾插四个元素");
	LinkListReversePrint(head);
}	

int main()
{
	TestReversePrint();
	return 0;
}