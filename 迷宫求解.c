//SeqStack.h
#pragma once

#include<stdio.h>
#include<stddef.h>
#include<windows.h>

#define MAZE_ROW 6  //行
#define MAZE_COL 6  //列


typedef struct Maze {
	int map[MAZE_ROW][MAZE_COL];
}Maze;

#define FOR_MAZE
#ifdef FOR_MAZE
typedef struct Point {
	int row;
	int col;
}Point;
typedef  Point SeqStackType;
#else
typedef char SeqStackType;
#endif

#define SeqStackMaxSize 1000

typedef struct SeqStack {
	SeqStackType data[SeqStackMaxSize];
	size_t size;
} SeqStack;

void SeqStackInit(SeqStack* stack);//初始化
void SeqStackDestory(SeqStack* stack);//销毁
void SeqStackPush(SeqStack* stack, SeqStackType value);//入栈
void SeqStackPop(SeqStack* stack);//出栈
int GetTop(SeqStack* stack, SeqStackType* value);//取栈顶元素
size_t SeqStackSize(SeqStack* stack);
void SeqStackAssign(SeqStack* from, SeqStack* to);   //赋值
#ifdef FOR_MAZE
void SeqStackDebugPrintPoint(SeqStack* stack, const char* msg);
#endif



//maze.c
//迷宫求解思路：深度优先
#include"SeqStack.h"

void SeqStackInit(SeqStack* stack) {
	if (stack == NULL) {
		return;
	}
	stack->size = 0;
}

void SeqStackDestory(SeqStack* stack) {
	if (stack == NULL) {
		return;
	}
	stack->size = 0;
}

void SeqStackPush(SeqStack* stack, SeqStackType value) {
	if (stack == NULL) {
		return;
	}
	if (stack->size >= SeqStackMaxSize)
		return;
	stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack) {
	if (stack == 0) {
		return;
	}
	if (stack->size == 0)
		return;
	--stack->size;
}

int GetTop(SeqStack* stack, SeqStackType* value) {
	if (stack == NULL || value == NULL) {
		return 0;
	}
	if (stack->size == 0)
		return 0;
	*value = stack->data[stack->size - 1];
	return 1;
}

size_t SeqStackSize(SeqStack* stack) {
	if (stack == NULL) {
		return 0;
	}
	return stack->size;
}

void SeqStackAssign(SeqStack* from, SeqStack* to) {  //复制
	if (from == NULL || to == NULL) {
		return;
	}
	to->size = from->size;
	size_t i = 0;
	for (; i < from->size; ++i) {
		to->data[i] = from->data[i];
	}
}

#ifdef FOR_MAZE
#include<stdio.h>
void SeqStackDebugPrintPoint(SeqStack* stack, const char* msg) {
	if (stack == NULL) {
		printf("stack == NULL\n");
		return;
	}
	printf("\n[%s]\n", msg);
	printf("[栈底]\n");
	size_t i = 0;
	for (; i < stack->size; ++i) {
		printf("(%d, %d)\n", stack->data[i].row, stack->data[i].col);
	}
	printf("[栈顶]\n");
}
#endif

void MazeInit(Maze* maze) {
	if (maze == NULL) {
		return;
	}
	int map[MAZE_ROW][MAZE_COL] = {
		{0, 1, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0},
		{0, 1, 0, 1, 1, 0},
		{0,	1, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0}
	};
	size_t i = 0;
	for (; i < MAZE_ROW; ++i) {
		size_t j = 0;
		for (; j < MAZE_COL; ++j) {
			maze->map[i][j] = map[i][j];
		}
	}
}

void MazeInitMultiExit(Maze* maze) { //多出口地图,找到最短路径
	if (maze == NULL) {
		return;
	}
	int map[MAZE_ROW][MAZE_COL] = {
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 }
	};
	size_t i = 0;
	for (; i < MAZE_ROW; ++i) {
		size_t j = 0;
		for (; j < MAZE_COL; ++j) {
			maze->map[i][j] = map[i][j];
		}
	}
}

void MazeInitMultiExitWithCycle(Maze* maze) { //多出口带环的迷宫
	if (maze == NULL) {
		return;
	}
	int map[MAZE_ROW][MAZE_COL] = {
		{ 0, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0 },
		{ 0, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 1, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0 }
	};
	size_t i = 0;
	for (; i < MAZE_ROW; ++i) {
		size_t j = 0;
		for (; j < MAZE_COL; ++j) {
			maze->map[i][j] = map[i][j];
		}
	}
}

void MazePrint(Maze* maze) {
	if (maze == NULL) {
		return;
	}
	size_t i = 0;
	for (; i < MAZE_ROW; ++i) {
		size_t j = 0;
		for (; j < MAZE_COL; ++j) {
			printf("%2d ", maze->map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int CanStay(Maze* maze, Point cur) {
	if (maze == NULL) {
		return 0;
	}
	//1. 判定点在地图上
	if (cur.row < 0 || cur.row >= MAZE_ROW|| 
		cur.col < 0 || cur.col >= MAZE_COL) {
		return 0;
	}
	//2. 当前点对应的值是1.
	if (maze->map[cur.row][cur.col] == 1) {
		return 1;
	}
	return 0;
}

void Mark(Maze* maze, Point cur) {
	if (maze == NULL) {
		return;
	}
	maze->map[cur.row][cur.col] = 2;
}

int IsExit(Point cur, Point entry) {
	//1. 当前点在地图的边缘上
	//2. 当前点不是入口
	if (cur.row == 0 || cur.col == 0 ||
		cur.row == MAZE_ROW - 1 || cur.col == MAZE_COL - 1) {
		//在边缘上
		if (cur.row == entry.row && cur.col == entry.col) {
			//入口点
			return 0;
		}
		return 1;
	}
	return 0;
}

void _HasPath(Maze* maze, Point cur, Point entry) {
	if (maze == NULL) {
		return;
	}
	//1. 判定当前点是否能落脚(点在地图上且位置的值为1)
	if (!CanStay(maze, cur)) {
		return;
	}
	//2. 标记当前点是走过的点
	Mark(maze, cur);
	//3. 判定当前点是否是出口(落在边缘上且不是入口)
	if (IsExit(cur, entry)) {
		printf("找到了路径！\n");
		return;
	}
	//4. 按照顺时针方向探测周围的邻接点(递归的调用HasPath)
	Point up = cur;
	up.row -= 1;
	_HasPath(maze, up, entry);
	Point right = cur;
	right.col += 1;
	_HasPath(maze, right, entry);
	Point down = cur;
	down.row += 1;
	_HasPath(maze, down, entry);
	Point left = cur;
	left.col -= 1;
	_HasPath(maze, left, entry);
	//5. 如果四个方向都探测过了，就直接返回
	return;
}

//使用递归的方式来查找迷宫上是否存在一条路径
void HasPath(Maze* maze, Point entry) {
	if (maze == NULL) {
		return;
	}
	_HasPath(maze, entry, entry);
}

void HasPathByLoop(Maze* maze, Point entry) {
	if (maze == NULL) {
		return;
	}
	//1. 判定入口点是否能落脚，如果不能，表示非法输入，直接返回
	if (!CanStay(maze, entry)) {
		//入口点非法
		return;
	}
	//2. 标记入口点走过了，把入口点入栈
	Mark(maze, entry);
	SeqStack stack;
	SeqStackInit(&stack);
	SeqStackPush(&stack, entry);
	//3. 进入循环，取栈顶元素为当前点
	Point cur;
	while (GetTop(&stack, &cur)) {
		//4. 判定当前点是否为出口(如果是出口，说明找到路了)
		if (IsExit(cur, entry)) {
			printf("找到了路径！\n");
			return;
		}
		//5. 按照一定顺序判定当前点的四个邻接点是否能落脚
		//6. 如果某一个邻接点能够落脚，标记这个邻接点，
		//   并且把邻接点入栈，并且直接进入下一次循环
		Point up = cur;
		up.row -= 1;
		if (CanStay(maze, up)) {
			Mark(maze, up);
			SeqStackPush(&stack, up);
			continue;
		}
		Point right = cur;
		right.col += 1;
		if (CanStay(maze, right)) {
			Mark(maze, right);
			SeqStackPush(&stack, right);
			continue;
		}
		Point down = cur;
		down.row += 1;
		if (CanStay(maze, down)) {
			Mark(maze, down);
			SeqStackPush(&stack, down);
			continue;
		}
		Point left = cur;
		left.col -= 1;
		if (CanStay(maze, left)) {
			Mark(maze, left);
			SeqStackPush(&stack, left);
			continue;
		}
		//7. 四个方向都探测完毕，把当前点出栈
		SeqStackPop(&stack);
	}
	return;
}

void _GetShortPath(Maze* maze, Point cur, Point entry, 
	              SeqStack* cur_path, SeqStack* short_path) {
	//1. 判定当前点是否能落脚
	if (!CanStay(maze, cur)) {
		return;
	}
	//2. 标记当前点，把当前点push到cur_path
	Mark(maze, cur);
	SeqStackPush(cur_path, cur);
	//3. 判定当前是不是出口，如果是出口
	if (IsExit(cur, entry)) {
		//a). 比较当前的cur_path和short_path的长短
		SeqStackDebugPrintPoint(cur_path, "找到一条路径！");
		if (SeqStackSize(cur_path) < SeqStackSize(short_path) 
			                  || SeqStackSize(short_path) == 0) {
			//b). 如果cur_path比short_path小，
			//    或者short_path为空
			//    用cur_path替换short_path。
			SeqStackAssign(cur_path, short_path);
			printf("当前路径是一条比较短的路径\n");
		}
		//c). 让cur_path出栈，同时返回到上一层的栈帧
		SeqStackPop(cur_path);
		return;
	}
	//4. 按照一定的顺序递归的调用该函数完成邻接点的判定
	Point up = cur;
	up.row -= 1;
	_GetShortPath(maze, up, entry, cur_path, short_path);
	
	Point right = cur;
	right.col += 1;
	_GetShortPath(maze, right, entry, cur_path, short_path);
	
	Point down = cur;
	down.row += 1;
	_GetShortPath(maze, down, entry, cur_path, short_path);
	
	Point left = cur;
	left.col -= 1;
	_GetShortPath(maze, left, entry, cur_path, short_path);
	//5. 回溯到上一个位置，先将cur_path出栈，再return
	SeqStackPop(cur_path);
	return;
}

void GetShortPath(Maze* maze, Point entry) { //递归
	SeqStack short_path;  //相当于擂台
	SeqStack cur_path;  //当前找到的路径
	SeqStackInit(&short_path);
	SeqStackInit(&cur_path);
	_GetShortPath(maze, entry, entry, &cur_path, &short_path);
	SeqStackDebugPrintPoint(&short_path, "最短路径是");
}

int CanStayWithCycle(Maze* maze, Point cur, Point pre) {
	//1. 判定当前点是否在地图上，如果不在就不能落脚
	if (cur.row < 0 || cur.row >= MAZE_ROW ||
		cur.col < 0 || cur.col >= MAZE_COL) {
		return 0;
	}
	//2. 判定当前点的值是否为1
	int cur_value = maze->map[cur.row][cur.col];
	if (cur_value == 1) {
		return 1;
	}
	//3. 判定当前点的值和前一个点的值得大小是否满足 
	//         cur_value - 1 > pre_value 时才能落脚
	if (pre.row >= 0 && pre.row < MAZE_ROW && 
		     pre.col >= 0 && pre.col < MAZE_COL) {
		int pre_value = maze->map[pre.row][pre.col];
		if (cur_value - 1 > pre_value) {
			return 1;
		}
	}
	return 0;
}

void MarkWithCycle(Maze* maze, Point cur, Point pre) {
	if (pre.row < 0 || pre.row >= MAZE_ROW ||
		pre.col < 0 || pre.col >= MAZE_COL) {
		//pre非法
		maze->map[cur.row][cur.col] = 2;
		return;
	}
	int pre_value = maze->map[pre.row][pre.col];
	maze->map[cur.row][cur.col] = pre_value + 1;
}


void _GetShortPathWithCycle(Maze* maze, Point cur, Point pre, Point entry,
	                       SeqStack* cur_path, SeqStack* short_path) {
	//1. 判定当前点是否能落脚(判定落脚方式有变化)
	if (!CanStayWithCycle(maze, cur, pre)) {
		return;
	}
	//2. 如果能落脚，就标记当前点(标记的方式也有变化)，把当前点入栈
	MarkWithCycle(maze, cur, pre);
	SeqStackPush(cur_path, cur);
	//3. 判定当前点是否是出口
	if (IsExit(cur, entry)) {
		//   a). 判定cur_path 和 short_path 的大小
		SeqStackDebugPrintPoint(cur_path, "找到一条路径！");
		if (SeqStackSize(cur_path) < SeqStackSize(short_path)
			|| SeqStackSize(short_path) == 0) {
			//   b). 如果cur_path比较小，就替换short_path
			SeqStackAssign(cur_path, short_path);
		}
		//   c). 出栈，并回溯
		SeqStackPop(cur_path);
		return;
	}
	//4. 如果不是出口，以当前点为基准，探测四个方向，递归的调用该函数
	Point up = cur;
	up.row -= 1;
	_GetShortPathWithCycle(maze, up, cur, entry, cur_path, short_path);

	Point right = cur;
	right.col += 1;
	_GetShortPathWithCycle(maze, right, cur, entry, cur_path, short_path);

	Point down = cur;
	down.row += 1;
	_GetShortPathWithCycle(maze, down, cur, entry, cur_path, short_path);

	Point left = cur;
	left.col -= 1;
	_GetShortPathWithCycle(maze, left, cur, entry, cur_path, short_path);
	//5. 四个方向都探测完了，出栈，并回溯
	SeqStackPop(cur_path);
	return;
}


void GetShortPathWithCycle(Maze* maze, Point entry) {
	SeqStack short_path;  //相当于擂台
	SeqStack cur_path;  //当前找到的路径
	SeqStackInit(&short_path);
	SeqStackInit(&cur_path);
	Point pre = { -1, -1 };
	_GetShortPathWithCycle(maze, entry, pre, entry, &cur_path, &short_path);
	SeqStackDebugPrintPoint(&short_path, "最短路径是");
}


//////////////////////////////////////////
//////////以下是测试代码//////////////////
//////////////////////////////////////////

#define TEST_HEADER printf("\n======%s======\n", __FUNCTION__)

void Test1() {
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	MazePrint(&maze);
}

void Test2() {
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = { 0, 1 };
	HasPath(&maze, entry);
	MazePrint(&maze);
}

void Test3() {
	TEST_HEADER;
	Maze maze;
	MazeInit(&maze);
	Point entry = { 0, 1 };
	HasPathByLoop(&maze, entry);    //非递归
	MazePrint(&maze);
}

void Test4() {
	TEST_HEADER;
	Maze maze;
	MazeInitMultiExit(&maze);
	Point entry = { 0, 1 };
	GetShortPath(&maze, entry);
	MazePrint(&maze);
}

void Test5() {
	TEST_HEADER;
	Maze maze;
	MazeInitMultiExitWithCycle(&maze);
	Point entry = { 0, 1 };
	GetShortPathWithCycle(&maze, entry);
	MazePrint(&maze);
}

int main() {
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	system("pause");
	return 0;
}