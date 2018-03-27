//有一个字符数组的内容为:"student a am i",
//请你将数组的内容改为"i am a student".

#include<stdio.h>
#include<ctype.h>

static rstr(char *start, char *end)
{
    while (start < end)
    {
        *start ^= *end;
        *end ^= *start;
        *start ^= *end;
        start++;
        end--;
    }
}
void reverse_str(char str[])
{
    char *p = str;
    char *q = p;
    while (*p)
    {
        if (isspace(*p))
        {
            rstr(q, p - 1);
            p++;
            q = p;
        }
        else
        {
            p++;
        }
    }
    rstr(q, p - 1);
    rstr(str, p - 1);
}

int main()
{
    char arr[] = "student a am i";
    reverse_str(arr);
    printf("%s\n", arr);
}