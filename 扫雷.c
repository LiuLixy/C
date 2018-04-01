//C语言实现扫雷游戏

//game.h

#ifndef __GAME_H__
#define __GAME_H__

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROWS 12
#define COLS 12
#define COUNT 10

void Init_Board(char mine[ROWS][COLS], char show[ROWS][COLS]);
void Set_Mine(char mine[ROWS][COLS]);
void Display_Board(char show[ROWS][COLS]);
int Get_Mine_Num(char mine[ROWS][COLS], int x, int y);
void Check_Win(char mine[ROWS][COLS], char show[ROWS][COLS]);

#endif //__GAME_H__


//game.c

#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void Init_Board(char mine[ROWS][COLS], char show[ROWS][COLS])
{
    int i = 0;
    int j = 0;
    for (i = 1; i < ROWS - 1; i++)
    {
        for (j = 1; j < COLS - 1; j++)
        {
            mine[i][j] = '0';
        }
    }
    for (i = 1; i < ROWS - 1; i++)
    {
        for (j = 1; j < COLS - 1; j++)
        {
            show[i][j] = '*';
        }
    }
}

void Set_Mine(char mine[ROWS][COLS])
{
    int i = 0;
    int j = 0;
    int ret = COUNT;
    while (ret)
    {
        i = rand() % ROWS - 1;
        j = rand() % COLS - 1;
        if (mine[i][j] == '0')
        {
            mine[i][j] = '1';
            ret--;
        }
    }
}

void Display_Board(char show[ROWS][COLS])
{
    int i = 0;
    int j = 0;
    printf(" ");
    for (i = 1; i < COLS - 1; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");
    for (i = 1; i < ROWS - 1; i++)
    {
        printf("%2d", i);
        for (j = 1; j < COLS - 1; j++)
        {
            printf(" %c ", show[i][j]);
        }
        printf("\n");
    }
}

int Get_Mine_Num(char mine[ROWS][COLS], int x, int y)
{
    int count = 0;
    if (mine[x - 1][y - 1] == '1')
        count++;
    if (mine[x - 1][y] == '1')
        count++;
    if (mine[x - 1][y + 1] == '1')
        count++;
    if (mine[x][y + 1] == '1')
        count++;
    if (mine[x + 1][y + 1] == '1')
        count++;
    if (mine[x + 1][y] == '1')
        count++;
    if (mine[x + 1][y - 1] == '1')
        count++;
    if (mine[x][y - 1] == '1')
        count++;
    return count;
}

void Check_Win(char mine[ROWS][COLS], char show[ROWS][COLS])
{
    int count = 0;
    int x = 0;
    int y = 0;
    while (count != ((ROWS - 2)*(COLS - 2) - COUNT))
    {
        printf("请输入坐标>:");
        scanf("%d%d", &x, &y);
        if (mine[x][y] == '1')
        {
            printf("踩雷了！\n");
            Display_Board(mine);
            return;
        }
        else
        {
            int ret = Get_Mine_Num(mine, x, y);
            show[x][y] = ret + '0';
            Display_Board(show);
            count++;
        }
    }
    printf("恭喜你赢了！\n");
    Display_Board(mine);
}


//test.c

#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"
#include<time.h>

void menu()
{
    printf("***********************************\n");
    printf("****   1.play       0.exit     ****\n");
    printf("***********************************\n");
}

void game()
{
    char mine[ROWS][COLS];
    char show[ROWS][COLS];
    Init_Board(mine, show);
    Set_Mine(mine);
    Display_Board(show);
    Get_Mine_Num(mine, ROWS, COLS);
    Check_Win(mine, show);
}


int main()
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择：>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            break;
        default:
            printf("选择错误，请重新输入\n");
            break;
        }
    } while (input);
    return 0;
}