#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void PrintArr(int* arr, int len, const char* msg) {
	assert(arr);
	printf("%s: ", msg);
	int i = 0;
	for (; i < len; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//冒泡排序
void BubbleSort(int* arr, int len) {
	assert(arr);
	int i = 0;
	for (; i < len; ++i) {
		int j = 0;
		for (; j < len - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

//选择排序
void SelectSort(int* arr, int len) {
	assert(arr);
	int i = 0;
	int min = 0;
	for (; i < len; ++i) {
		min = i;
		int j = i + 1;
		for (; j < len; ++j) {
			if (arr[min] > arr[j]) {
				min = j;
			}	
		}
		if (min != i) {
			swap(&arr[min], &arr[i]);
		}	
	}
}

void AdjustUp(int* arr, int i, int len) {
	assert(arr);
	int j = i * 2 + 1;
	while (j < len) {
		if (j + 1 < len && arr[j] < arr[j + 1]) {
			j++;
		}
		if (arr[i] > arr[j]) {
			break;
		}
		swap(&arr[i], &arr[j]);
		i = j;
		j = i * 2 + 1;
	}
}

void _HeapSort(int* arr, int len) {  //生成小堆
	assert(arr);
	int i = 0;
	for (i = len / 2 - 1; i >= 0; i--) {
		AdjustUp(arr, i, len);
	}
}

//堆排序
void HeapSort(int* arr, int len) {
	assert(arr);
	int i = 0;
	_HeapSort(arr, len);
	for (i = len - 1; i >= 0; i--) {
		swap(&arr[i], &arr[0]);
		AdjustUp(arr, 0, i);
	}
}


//插入排序
void InsertSort(int* arr, int len) {
	assert(arr);
	int i = 0;
	for (i = 1; i < len; ++i) {
		int j = i - 1;
		int tmp = arr[i];
		while (j >= 0 && tmp < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
	}
}

//希尔排序
void ShellSort(int* arr, int len) {
	assert(arr);
	int h = 1;  //最后一次的步长为1

	while (h < len / 3)
		h = 3 * h + 1;
	while (h >= 1) {
		int i = h;
		int j = 0;
		int tmp = 0;
		for (; i < len; ++i) {
			for (j = i; j >= h && (arr[j] < arr[j - h]); j -= h) {
				swap(&arr[j], &arr[j - h]);
			}
		}
		h /= 3;
	}
}

void _MergeArray(int* arr, int left, int mid, int right, int* tmp) {
	assert(arr);
	assert(tmp);
	int cur1 = left;
	int cur2 = mid;
	int tmp_index = left;

	while (cur1 < mid && cur2 < right) {
		//把给定范围的数组分为两半然后进行归并，得到一个有序的数组
		if (arr[cur1] < arr[cur2]) {
			tmp[tmp_index++] = arr[cur1++];
		}
		else {
			tmp[tmp_index++] = arr[cur2++];
		}
	}
	//把当前的接上
	while (cur1 < mid) {
		tmp[tmp_index++] = arr[cur1++];
	}
	while (cur2 < right) {
		tmp[tmp_index++] = arr[cur2++];
	}
	memcpy(arr + left, tmp + left, sizeof(int)* (right - left));
}

void _MergeSort(int* arr, int left, int right, int* tmp) {
	assert(arr);
	assert(tmp);
	if (right - left <= 1) {
		return;
	}
	int mid = left + (right - left) / 2;
	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid, right, tmp);
	//先保证左右区间都是有序之后才能进行合并
	_MergeArray(arr, left, mid, right, tmp);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

//归并排序(递归)
void MergeSort(int* arr, int len) {
	assert(arr);
	int* tmp = (int*)malloc(sizeof(arr) * len);
	_MergeSort(arr, 0, len, tmp);
	free(tmp);
}

//归并排序(非递归)
void MergeSortByLoop(int* arr, int len) {
	assert(arr);
	if (len <= 1) {
		return;
	}
	int* tmp = (int*)malloc(sizeof(int) * len);
	int i = 1;
	for (; i < len; i *= 2) {
		int j = 0;
		for (; j < len; j += 2 * i) {
			int left = j;
			int mid = i + j;
			int right = j + 2 * i;
			if (mid > len) {
				mid = len;
			}
			if (right > len) {
				right = len;
			}
			_MergeArray(arr, left, mid, right, tmp);
		}
	}
	free(tmp);
}

//快速排序
void QuickSort(int* arr, int len, int beg, int end) {
	int i = beg;
	int j = end;
	if (beg < end) {
		i = beg + 1;  //将arr[beg]作为基准值
		j = end;        //arr[end]为数组的最后一个元素
		while (i < j) {	
			if (arr[i] > arr[beg]) {
				swap(&arr[i], &arr[j]);
				j--;
			}
			else {
				i++;
			}
		}
		//循环结束后 i == j
		//此时的数组被分成两个部分，前一部分为arr[beg + 1] ~ arr[i]  
		//                          后一部分为arr[i + 1] ~ arr[end]
		if (arr[i] >= arr[beg]) {
			i--;
		}
		swap(&arr[i], &arr[beg]);

		QuickSort(arr, len, beg, i);
		QuickSort(arr, len, j, end);
	}

}

int main() {
	int arr[] = { 12, 34, 35, 23, 31, 41, 26, 52 };
	int len = sizeof(arr) / sizeof(arr[0]);
	PrintArr(arr, len, "排序前");
	//BubbleSort(arr, len);
	//PrintArr(arr, len, "冒泡排序结果");
	//SelectSort(arr, len);
	//PrintArr(arr, len, "选择排序结果");
	//HeapSort(arr, len);
	//PrintArr(arr, len, "堆排序结果");
	//InsertSort(arr, len);
	//PrintArr(arr, len, "插入排序结果");
	//ShellSort(arr, len);
	//PrintArr(arr, len, "希尔排序结果");
	//MergeSort(arr, len);
	//PrintArr(arr, len, "归并排序结果");
	//QuickSort(arr, len, 0, len - 1);
	//PrintArr(arr, len, "快速排序结果");
	MergeSortByLoop(arr, len);
	PrintArr(arr, len, "非递归归并排序");
	return 0;
}