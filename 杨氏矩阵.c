#include<stdio.h>
#include<windows.h>
#include<assert.h>
#pragma warning(disable:4996)

int yang_find(int arr[][3], int len, int data)
{
	assert(arr);
	assert(len > 0);

	if (data < (arr[0][0]) || data > (arr[2][2]))
	{
		return 0;
	}
	int i = 0;
	int j = len - 1;
	while (i < len && j >= 0)
	{
		if (data > arr[i][j])
		{
			i++;
		}
		else if (data < arr[i][j])
		{
			j--;
		}
		else
			return 1;
	}
	return 0;
}

int  main()
{
	int arr[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	int data = 0;
	printf("Please Enter: ");
	scanf("%d", &data);
	int len = sizeof(arr[0]) / sizeof(arr[0][0]);
	int ret = yang_find(arr, data, len);
	if (ret == 1)
	{
		printf("找到了\n");
	}
	if (ret == 0)
	{
		printf("没找到\n");
	}
	system("pause");
	return 0;
}