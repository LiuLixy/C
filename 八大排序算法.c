#include<stdio.h>
#include<assert.h>
#include<windows.h>

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

void AdjustDown(int* arr, int i, int len) {
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
		AdjustDown(arr, i, len);
	}
}

//堆排序
void HeapSort(int* arr, int len) {
	assert(arr);
	int i = 0;
	_HeapSort(arr, len);
	for (i = len - 1; i >= 0; i--) {
		swap(&arr[i], &arr[0]);
		AdjustDown(arr, 0, i);
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

void Merge(int* arr, int* arr2, int beg, int mid, int end) {
	int i = beg;   //指向左半区的指针
	int j = mid + 1;  //指向又半区的指针
	int k = 0;  //指向arr2的指针
	while (i <= mid && j <= end) {
		if (arr[i] > arr[j]) {
			arr2[k++] = arr[j++];
		}
		else {
			arr[k++] = arr[i++];
		}
	}
	while (i <= mid) {
		arr2[k++] = arr[i++];
	}
	while (j != end) {
		arr2[k++] = arr[j++];
	}
	for (i = beg; i <= end; i++) {
		arr[i] = arr2[i];
	}
}


//归并排序(递归)
void MergeSort(int* arr, int* arr2, int beg, int end) {
	assert(arr);
	assert(arr2);
	int mid = 0;
	while (beg < end) {
		mid = (beg + end) / 2;
		MergeSort(arr, arr2, beg, mid);
		MergeSort(arr, arr2, mid+1, end);
		Merge(arr, arr2, beg, mid, end);
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
	int arr2[sizeof(arr)/sizeof(arr[0])] = { 0 };
	MergeSort(arr, arr2, 0, len - 1);
	PrintArr(arr, len, "归并排序结果");
	system("pause");
	return 0;
}