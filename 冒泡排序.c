#include<stdio.h>

bubble_sort(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz -1; i++)
	{
		int j = 0;
		for (j = 0; j < sz -1 - i; j++)
		{
			if (arr[j] > arr[j+1])
			{
				int tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
		}
	}
}

void print_arr(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[] = { 22, 54, 48, 31, 49, 46, 99, 83, 55, 9 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	bubble_sort(arr, sz);
	print_arr(arr, sz);
	return 0;
}