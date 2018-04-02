//convert.h

#ifndef __CONVERT_H__
#define __CONVERT_H__

#include<stdio.h>
#include<stdlib.h>

#define INPUTFILENAME "input.c"  
#define OUTPUTFILENAME "output.c"

typedef enum CONVERT_STATUS{
    NUL_STATUS,
    C_STATUS,
    CPP_STATUS,
    EOF_STATUS
}StatusType;

void CommentConver();
void ConvertWork(FILE *r, FILE *w);  
void DoCStatus(FILE *r, FILE *w);
void DoNullStatus(FILE *r, FILE *w);  
void DoCppStatus(FILE *r, FILE *w);

#endif



//main.c

#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include"convert.h"

StateType status;

void do_NUL_Status(FILE *r, FILE *w)
{
    int f = fgetc(r);
    int s;
    switch (f)
    {
    case '/':
        s = fgetc(r);
        if (s == '*')
        {
            fputc('/', w);
            fputc('/', w);
            state = C_STATUS;
        }
        else if(s == '/')
        {
            fputc('/', w);
            fputc('/', w);
            state = CPP_STATUS;
        }
        else
        {
            ungetc(f, w);
            ungetc(s, w);
        }
        break;
    case EOF:
        fputc(f, w);
        state = EOF_STATUS;
        break;
    default:
        fputc(f, w);
        break;
    }
}

void do_C_Status(FILE *r, FILE *w)
{
    int f = fgetc(r);
    int s = 0;
    switch (f)
    {
    case'*':
        s = fgetc(r);
        if (s == '/')
        {
            int t = fgetc(r);
            state = NUL_STATUS;
            if (t != '\n')
            {
                fputc('\n', w);
                ungetc(t, r);
            }
            else
            {
                fputc(t, w);
            }
        }
        else
        {
            fputc(f, w);
            ungetc(s, r);
        }
        break;
    case '\n':
        fputc(f, w);
        fputc('/', w);
        fputc('/', w);
        break;
    case EOF:   
        fputc(f, w);
        state = EOF_STATUS;
        break;
    default:
        fputc(f, w);
        break;
    }
}

void do_CPP_Status(FILE *r, FILE *w) 
{
    int f = fgetc(r);
    switch (f)
    {
    case'\n':
        fputc(f, w);
        state = NUL_STATUS;
        break;
    case EOF:
        fputc(f, w);
        state = EOF_STATUS;
        break;
    default:
        fputc(f, w);
        break;
    }
}


void ConvertWork(FILE *r, FILE *w)
{
    state = NUL_START;
    while (status != EOF_START)
    {
        switch (status)
        {
        case NUL_STATUS:
            do_NUL_Status(r, w);
            break;
        case C_STATUS:
            do_C_Status(r, w);
            break;
        case CPP_STATUS:
            do_CPP_Status(r, w);
            break;
        default:
            break;
        }
    }
}

void CommentConvert()
{
    FILE *pw = NULL;
    FILE *pr = fopen(INPUTFILENAME, "r");
    if (pr == NULL)
    {
        perror("open file for read");
        exit(EXIT_FAILURE);
    }
    pw = fopen(OUTPUTFILENAME, "w");
    if (pw == NULL)
    {
        fclose(pr);
        perror("open file for write");
        exit(EXIT_FAILURE);
    }
    ConvertWork(pr, pw);
    fclose(pr);
    fclose(pw);
}

//test.c

#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<windows.h>
#include"convert.h"


void test()
{
    CommentConvert();
}

int main()
{
    test();
    system("pause");
    return 0;
}

//测试用例：

// this is maomaochong
/* int i = 0; */

/* int j = 10 */int k = 3;

int n = 20;

/*
int i = 0;
int j = 20;
int k = 250;
*/int q = 9527;

/***/

/* int z = 7748258; */ /*int b=94250;*/

// /*dsklfjdasl;fdsf;ldsfds*/