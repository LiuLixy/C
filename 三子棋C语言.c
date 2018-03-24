//game.h

#ifndef __GAME_H__
#define __GAME_H__

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define COL 3
#define ROW 3

void InitBoard(char board[ROW][COL], int row, int col);
void DisplayBoard(char board[ROW][COL], int row, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int row, int col);
char Is_Win(char board[ROW][COL], int row, int col);

#endif //__GAME_H__


//game.c

#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include "game.h"

void InitBoard(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
        if (i < row - 1)
        printf("|---|---|---|\n");
    }
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    printf("电脑走：\n");
    while (1)
    {
        i = rand() % row;
        j = rand() % col;
        if (board[i][j] == ' ')
        {
            board[i][j] = '&';
                break;
        }
    }
}

void PlayerMove(char board[ROW][COL], int row, int col)
{
    int x = 0;
    int y = 0;
    printf("玩家走:\n");
    while (1)
    {
        printf("请输入坐标：>");
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col)
        {
            if (board[x - 1][y - 1] == ' ')
            {
                board[x - 1][y - 1] = 'X';
                break;
            }
            else if (board[x - 1][y - 1] == '&')
            {
                printf("该坐标已被占用！\n");
            }
        }
        else
        {
            printf("坐标非法，请重新输入！\n");
        }
    }
}

int is_full(char board[ROW][COL], int row, int col)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        if (board[i][j] == ' ')
        {
            return 0;
        }
    }
    return 'q';
}

char Is_Win(char board[ROW][COL], int row, int col)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }
    for (i = 0; i < col; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[1][1];
    }
    else if (board[2][0] == board[1][1] && board[1][1] == board[0][2])
    {
        return board[1][1];
    }
    if (is_full(board, row, col))
    {
        return 'q';
    }
    return ' ';
}


//test.c

#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include "game.h"
#include<stdlib.h>
#include<time.h>
#include<windows.h>

void nemu()
{
    printf("***********************************\n");
    printf("*****   1.play       0.exit   *****\n");
    printf("***********************************\n");
}

void game()
{
    char ret = 0;
    char arr[ROW][COL] = { 0 };
    InitBoard(arr, ROW, COL);
    DisplayBoard(arr, ROW, COL);
    do
    {
        PlayerMove(arr, ROW, COL);
        DisplayBoard(arr, ROW, COL);
        ret = Is_Win(arr, ROW, COL);
        if (ret != ' ')
            break;
        Sleep(1000);
        ComputerMove(arr, ROW, COL);
        DisplayBoard(arr, ROW, COL);
        ret = Is_Win(arr, ROW, COL);
    } while (ret == ' ');
    if (ret == 'X')
    {
        printf("恭喜你，你赢了！\n");
    }
    else if (ret == '&')
    {
        printf("很遗憾，你输了！\n");
    }
    else if (ret == 'q')
    {
        printf("平局\n");
    }
}
void test()
{
    srand((unsigned int)time(NULL));
    int input = 0;
    do
    {
        nemu();
        printf("请选择:>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            break;
        default:
            printf("选择错误，请重新输入:>");
        }
    } while (input);
}

int main()
{
    test();
    return 0;
}