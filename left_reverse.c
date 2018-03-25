//实现一个函数，可以左旋字符串中的k个字符。

//例：ABCD1234 左旋一个字符得到 BCD1234A 
//    ABCD1234 左旋两个字符得到 CD1234AB

//方法一：这种方法比较传统，拿出K个字符，再将剩下的统一左移，函数内套用了双循环，时间复杂度较高。

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#pragma warning(disable:4996)

static void left_reverse_core(char arr[], int len)     
{
    int tmp = arr[0];
    int i = 0;
    for (i = 0; i < len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[i] = tmp;
}

void left_reverse(char arr[], int len, int count)   
{
    assert(arr);
    assert(len > 0);
    assert(count > 0);

    count %= len;
    while (count--)
    {
        left_reverse_core(arr, len);
    }
}

int main()
{
    char arr[] = "ABCD1234";
    int len = strlen(arr);
    int count = 0;
    printf("Please Enter: ");
    scanf("%d", &count);
    printf("before: %s\n", arr);
    left_reverse(arr, len, count);
    printf("after:  %s\n", arr);
    system("pause");
    return 0;
}


//方法二：这种方法的效率最高，例如现在需要把ABCD1234左移四个字符，
//先将前四个字符局部逆置得到DCBA1234，再将剩下的字符局部逆置得
//                      到DCBA4321,最后在整体逆置得到1234ABCD。

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#pragma warning(disable:4996)

tatic void reverse(char *start, char *end)
{
    while (start < end)
    {
        *start ^= *end;
        *end ^= *start;
        *start ^= *end;
        start++, end--;
    }
}

void left_reverse(char arr[], int len, int count)
{
    assert(arr);
    assert(len > 0);
    assert(count > 0);

    count %= len;
    reverse(arr, arr+count-1);        //实现0~count-1的局部逆置
    reverse(arr+count, arr+len-1);    //实现count-1~len-1的局部逆置  
    reverse(arr, arr + len-1);      //实现整体逆置


}

int main()
{
    char arr[] = "ABCD1234";
    int len = strlen(arr);
    int count = 0;
    printf("Please Enter: ");
    scanf("%d", &count);
    printf("before: %s\n", arr);
    left_reverse(arr, len, count);
    printf("after:  %s\n", arr);
    system("pause");
    return 0;
}


//方法三：这种方法是利用空间换效率，申请双倍字符串来进行左旋操作。 

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#pragma warning(disable:4996)

void left_reverse(char arr[], int len, int count)  
{
    assert(arr);
    assert(len > 0);
    assert(count > 0);

    count %= len;
    char *mem = (char *)malloc(2 * len + 1);
    if (mem == NULL)//malloc申请地址空间时，如果申请失败就会返回NULL值
    {
        return;
    }
    strcpy(mem, arr);
    strcat(mem, arr);         //ABCD1234ABCD1234
    strncpy(arr, mem + count, len);   //指定长度拷贝
    free(mem);
}

int main()
{
    char arr[] = "ABCD1234";
    int len = strlen(arr);
    int count = 0;
    printf("Please Enter: ");
    scanf("%d", &count);
    printf("before: %s\n", arr);
    left_reverse(arr, len, count);
    printf("after:  %s\n", arr);
    system("pause");
    return 0;
}