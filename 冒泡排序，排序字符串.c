#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<windows.h>

int sort_string(char (*arr)[7], int count)
{
	assert(arr);

	int i = 0;
	int j = 0;
	int flag = 0;
	for (; i < count - 1; i++)
	{
		for (j = 0; j < count - 1 - i; j++)
		{
			if (strcmp(arr[j], arr[j+1]) > 0)
			{
				flag = 1;
				char buf[64];
				strcpy(buf, arr[j]);
				strcpy(arr[j], arr[j + 1]);
				strcpy(arr[j + 1], buf);
			}
		}
		if (flag == 0)
		{
			return;
		}
	}
}

void show_string(char arr[][7], int num)
{
	int i = 0;
	for (; i < num; i++)
	{
		printf("%s\n", arr[i]);
	}
	printf("*****************\n");
}

int main(int argc, char *argv[])
{
	char arr[][7] = {"aaaaaa", "ffffff","bbbbbb", "eeeeee", "dddddd", "cccccc"};
	int len = sizeof(arr) / sizeof(arr[0]);
	show_string(arr, len);
	sort_string(arr, len);
	show_string(arr, len);
	system("pause");
	return 0;
}