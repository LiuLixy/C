//递归的方式实现快排
//快排的思想：分而治之

#include<stdio.h>
#include<windows.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void quicksort(int* arr, int len, int beg, int end) {
	int i = beg;
	int j = end;
	if (beg < end) {   
		i = beg + 1;  //以arr[beg]为基准
		j = end;       
		while (i < j) {
			if (arr[i] > arr[beg]) {
				swap(&arr[i], &arr[j]);
				j--;
			} else {
				i++;
			}
		}
		//跳出循环时 i == j
		//此时数组被分为两个部分，左边为arr[beg + 1] ~ arr[i]  
		//                      右边为arr[i + 1] ~ arr[end]
		if (arr[i] >= arr[beg]) {
			i--;
		}
		swap(&arr[i], &arr[beg]);

		quicksort(arr, len, beg, i);
		quicksort(arr, len, j, end);
	}
	
}

int main() {
	int arr[] = { 11, 56, 43, 22, 75, 86, 95, 45, 27 };
	int i = 0;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (; i < len; ++i) {
		printf("%d  ", arr[i]);
	}
	printf("\n");
	quicksort(arr, len, 0, len - 1);
	for (i = 0; i < len; ++i) {
		printf("%d  ", arr[i]);
	}
	system("pause");
	return 0;
}