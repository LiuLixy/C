#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef char LinkType;

typedef struct LinkNode {
	LinkType data;
	struct LinkNode* next;
}LinkNode;


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

void LinkListPopBack(LinkNode** head) {
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

size_t LinkListSize(LinkNode* head) {
	if (head == NULL) {
		return 0;
	}
	size_t size = 0;
	LinkNode* cur = head;
	while (cur != NULL) {
		++size;
		cur = cur->next;
	}
	return size;
}

//从尾到头打印单链表
void LinkListReversePrint(LinkNode* head) {
	if (head == NULL) {
		return;
	}
	if (head->next != NULL) {
		LinkListReversePrint(head->next);
	}
	printf("%c ", head->data);
}

//删除一个无头单链表的非尾节点（不能遍历链表）
void LinkListErase(LinkNode** head, LinkNode* pos)
{
	if (head == NULL || pos == NULL) {
		//非法输入
		return;
	}
	if (*head == NULL) {
		//空链表
		return;
	}
	if (pos->next == NULL) {
		return;
	}
	LinkNode* to_delete = pos->next;
	pos->data = to_delete->data;
	pos->next = to_delete->next;
	LinkListDestroyNode(to_delete);
	return;
}

//在无头单链表的一个节点前插入一个节点（不能遍历链表）
void LinkListInsertBefore(LinkNode** head, LinkNode* pos, LinkType value) {
	if (head == NULL) {
		return;
	}
	if (*head == NULL) {
		*head = LinkListCreateNode(value);
		return;
	}
	if (*head == pos) {
		LinkNode* new_node = LinkListCreateNode(value);
		new_node->next = pos;
		*head = new_node;
		return;
	}
	LinkNode* cur = *head;
	while (cur->next != pos && cur->next != NULL) {
		cur = cur->next;
	}
	LinkNode* new_node = LinkListCreateNode(value);
	cur->next = new_node;
	new_node->next = pos;
	return;
}

//单链表实现约瑟夫环(JosephCircle)
LinkNode* JosephCycle(LinkNode* head, size_t food) {
	if (head == NULL) {
		return;
	}
	LinkNode* cur = head;
	while (cur->next != cur) {
		size_t i = 1;
		for (; i < food; i++) {
			cur = cur->next;
		}
		LinkNode* to_delete = cur->next;
		cur->data = to_delete->data;
		cur->next = to_delete->next;
		LinkListDestroyNode(to_delete);
	}
	return cur;
}

//逆置/反转单链表
LinkNode* LinkListReverse(LinkNode** head) {
	if (head == NULL) {
		return NULL;
	}
	if (*head == NULL || (*head)->next == NULL) {
		return head;
	}
	LinkNode* ptr = NULL;
	LinkNode* cur = *head;
	while (cur != NULL) {
		LinkNode* tmp = cur;
		cur = cur->next;
		tmp->next = ptr;
		ptr = tmp;
	}
	return ptr;
}

//单链表排序（冒泡排序）
void LinkListBubbleSort(LinkNode* head) {
	if (head == NULL) {
		return;
	}
	LinkNode* cur = head;
	while (cur != NULL) {
		LinkNode* ptr = head;
		while (ptr != cur) {
			if (ptr->data > ptr->next->data) {
				LinkType tmp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = tmp;
			}
			ptr = ptr->next;
		}
		cur = cur->next;
	}
}

//合并两个有序链表,合并后依然有序
LinkNode* LinkListMerge(LinkNode* head1, LinkNode* head2) {
	if (head1 == NULL) {
		return head2;
	}
	if (head2 == NULL) {
		return head1;
	}
	LinkNode* head = NULL;
	LinkNode* cur1 = head1;
	LinkNode* cur2 = head2;
	if (cur1->data > cur2->data) {
		head = cur2;
		cur2 = cur2->next;
	}
	else if (cur1->data < cur2->data) {
		head = cur1;
		cur1 = cur1->next;
	}
	else {
		head = cur1;
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	LinkNode* cur = head;
	while (cur1 != NULL && cur2 != NULL) {
		if (cur1->data > cur2->data) {
			cur->next = cur2;
			cur2 = cur2->next;
		}
		else if (cur1->data < cur2->data) {
			cur->next = cur1;
			cur1 = cur1->next;
		}
		else {
			cur->next = cur1;
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		cur = cur->next;
	}
	if (cur1 != NULL) {
		cur->next = cur1;
	}
	if (cur2 != NULL) {
		cur->next = cur2;
	}
	return head;
}

//查找链表的中间节点，要求只能遍历一遍链表
LinkNode* FindMidNode(LinkNode* head) {
	if (head == NULL) {
		return;
	}
	LinkNode* fast = head;
	LinkNode* slow = head;
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

//查找单链表的倒数第K个节点，要求只能遍历一遍链表
LinkNode* FindLastKNode(LinkNode* head, size_t k) {
	if (head == NULL) {
		return NULL;
	}
	size_t size = LinkListSize(head);
	if (k < 0 || k > size) {
		return NULL;
	}
	LinkNode* fast = head;
	LinkNode* slow = head;
	while (--k) {
		fast = fast->next;
	}
	while (fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

//判断链表是否带环
LinkNode* HasCycle(LinkNode* head) {
	if (head == NULL) {
		return NULL;
	}
	LinkNode* fast = head;
	LinkNode* slow = head;
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) {
			return slow;
		}
	}
	return NULL;
}

//如果带环求环的长度
size_t GetCycleLen(LinkNode* head) {
	LinkNode* fast = head;
	LinkNode* slow = head;
	while (fast != NULL && fast->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast) {
			LinkNode* cur = slow->next;
			size_t len = 1;
			while (cur != slow) {
				cur = cur->next;
				len++;
			}
			return len;
		}
	}
	return 0;
}


//求环的入口
LinkNode* GetCycleEntry(LinkNode* head) {
	if(head == NULL) {
		return NULL;
	}
	LinkNode* ret = HasCycle(head);
	LinkNode* cur = head;
	if(ret == NULL) {
		return NULl;
	}
	while (cur != ret) {
		cur = cur->next;
		ret = ret->next;
	}
	return ret;
}


///////////////////////////////
///////以下是测试代码///////////
///////////////////////////////
#define TEST_HEADER printf("\n==============%s==============\n", __FUNCTION__)

void LinkListPrintChar(LinkNode *head, const char* msg) {
	printf("[%s]: ", msg);
	LinkNode* cur = head;
	for (; cur != NULL; cur = cur->next) {
		printf("[%c:%p] -> ", cur->data, cur);
	}
	printf("[NULL]\n\n");
}

void TestReversePrint() {
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

void TestErase() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListErase(&head, NULL);
	LinkListPrintChar(head, "尝试对空链表删除");
	LinkNode* pos_a = LinkListPushBack(&head, 'a');
	LinkNode* pos_b = LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPrintChar(head, "尾插四个元素");
	LinkListErase(&head, pos_b);
	LinkListPrintChar(head, "删除元素b");
	LinkListErase(&head, pos_a);
	LinkListPrintChar(head, "删除元素a");
}

void TestInsertBefore() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListInsertBefore(&head, head, 'b');
	LinkListPrintChar(head, "对空链表插入");
	LinkListInsertBefore(&head, head, 'a');
	LinkListPrintChar(head, "往链表头部插入");
	LinkListPushBack(&head, 'c');
	LinkNode* pos_e = LinkListPushBack(&head, 'e');
	LinkListInsertBefore(&head, pos_e, 'd');
	LinkListPrintChar(head, "往e之前插入d");
}

void TestJosephCycle() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkNode* pos_a = LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkNode* pos_g = LinkListPushBack(&head, 'g');
	pos_g->next = pos_a;
	LinkNode* pos = JosephCycle(head, 3);
	printf("%c\n", pos->data);
}

void TestReverse() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkListPrintChar(head, "尾插6个元素");
	LinkNode* ret = LinkListReverse(&head);
	LinkListPrintChar(ret, "逆置后");
}

void TestBubbleSort() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'd');
	LinkListPrintChar(head, "排序前");
	LinkListBubbleSort(head);
	LinkListPrintChar(head, "排序后");
}

void TestMerge()
{
	TEST_HEADER;
	LinkNode* head1;
	LinkListInit(&head1);
	LinkListPushBack(&head1, 'a');
	LinkListPushBack(&head1, 'c');
	LinkListPushBack(&head1, 'd');
	LinkListPushBack(&head1, 'g');
	LinkListPushBack(&head1, 'j');
	LinkListPrintChar(head1, "head1");
	LinkNode* head2;
	LinkListInit(&head2);
	LinkListPushBack(&head2, 'a');
	LinkListPushBack(&head2, 'b');
	LinkListPushBack(&head2, 'd');
	LinkListPushBack(&head2, 'f');
	LinkListPushBack(&head2, 'h');
	LinkListPushBack(&head2, 'j');
	LinkListPrintChar(head2, "head2");
	LinkNode* head;
	LinkListInit(&head);
	head = LinkListMerge(head1, head2);
	LinkListPrintChar(head, "合并后");
}

void TestFindMid() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkListPushBack(&head, 'g');
	LinkListPrintChar(head, "尾插7个元素");
	LinkNode* ret = FindMidNode(&head);
	printf("ret expect d, actual %c\n", ret->data);
}

void TestFindLastKNode() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkListPushBack(&head, 'g');
	LinkListPrintChar(head, "尾插7个元素");
	LinkNode* ret = FindLastKNode(&head, 2);
	printf("ret expect f, expect %c\n", ret->data);
}

void TestHasCycle() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkNode* pos_c = LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkNode* pos_g = LinkListPushBack(&head, 'g');
	LinkNode* ret = HasCycle(head);
	printf("HasCycle expect 0, actual %d\n", ret);
	pos_g->next = pos_c;
    ret = HasCycle(head);
	printf("HasCycle expect 1, actual %d\n", ret->data);
}

void TestGetCycleLen() {
	TEST_HEADER;
	LinkNode* head;
	LinkListInit(&head);
	LinkListPushBack(&head, 'a');
	LinkListPushBack(&head, 'b');
	LinkListPushBack(&head, 'c');
	LinkListPushBack(&head, 'd');
	LinkListPushBack(&head, 'e');
	LinkListPushBack(&head, 'f');
	LinkNode* pos_g = LinkListPushBack(&head, 'g');
	pos_g->next = head;
	size_t ret = GetCycleLen(head);
	printf("Cyclelen expect 7, actual %lu\n", ret);
}

int main() {
	TestErase();
	TestReversePrint();
	TestInsertBefore();
	TestJosephCycle();
	TestReverse();
	TestBubbleSort();
	TestMerge();
	TestFindMid();
	TestFindLastKNode();
	TestHasCycle();
	TestGetCycleLen();
	system("pause");
	return 0;
}