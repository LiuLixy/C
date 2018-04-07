#include <stdio.h>
#include <windows.h>
#include <assert.h>

int int_cmp(const void *x, const void *y)
{
	int a = *((int *)x);
	int b = *((int *)y);

	return a > b ? 1 : a < b ? -1 : 0;  //如果a>b,返回1；如果a<b，返回-1；否则返回0；
}

int float_cmp(const void *x, const void *y)
{
	float a = *((float *)x);
	float b = *((float *)y);

	return a > b ? 1 : a < b ? -1 : 0;
}

static void swap(void *x, void *y, int count)
{
	char *a = (char*)x;
	char *b = (char*)y;
	while (count--)
	{
		*a ^= *b;
		*b ^= *a;
		*a ^= *b;
		a++, b++;
	}
}

void bubble_sort(void *arr, int num, int size, int(*cmp)(const void *, const void *))
{
	assert(arr);
	assert(cmp); 

	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < num - 1; i++)
	{
		flag = 0;
		for (j = 0; j < num - 1 - i; j++)
		{
			if (cmp( (char*)arr + j*size, (char*)arr + (j + 1)*size ) > 0)
			{
				flag = 1;
				swap((char*)arr + j*size, (char*)arr + (j + 1)*size, size);
			}
		}
		if (flag == 0)
		{
			return;
		}
	}
}


int main()
{
	int i = 0;
	int arr[] = { 2,3,1,9,8,6,7,5 };
	//float farr[] = { 11.2, 264.66, 1.1, 55648.33 };
	int len = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr, len, sizeof(int), int_cmp);
	for (i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	system("pause");
	return 0;
}