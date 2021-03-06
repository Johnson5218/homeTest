#pragma once

#include <stdio.h>


// 插入排序
// 稳定
// 最差	O(n)	完全有序/O(n^2)/O(n^2)
// 空间			O(1)
void InsertSort(int array[], int size)
{
	int key;
	int i, j;
	for (i = 1; i < size; i++) {
		key = array[i];
		for (j = i - 1; j >= 0; j--) {
			if (key >= array[j]) {
				break;
			}
			else {
				array[j + 1] = array[j];
			}
		}

		array[j + 1] = key;
	}
}

void __InsertSort(int array[], int size, int gap)
{
	for (int g = 0; g < gap; g++) {
		int key;
		int i, j;
		for (i = gap + g; i < size; i += gap) {
			key = array[i];
			for (j = i - gap; j >= 0; j -= gap) {
				if (key >= array[j]) {
					break;
				}
				else {
					array[j + gap] = array[j];
				}
			}

			array[j + gap] = key;
		}
	}
}
#if 0
void __InsertSort(int array[], int size, int gap)
{
	int key;
	int i, j;
	for (i = gap; i < size; i++) {
		key = array[i];
		for (j = i - gap; j >= 0; j -= gap) {
			if (key >= array[j]) {
				break;
			}
			else {
				array[j + gap] = array[j];
			}
		}

		array[j + gap] = key;
	}
}
#endif

// 1. 不稳定
// 2. 最好/平均/最差	O(n)/O(n^1.2~1.3)/O(n^2)
// 3. 空间复杂度		O(1)
void ShellSort(int array[], int size)
{
	int gap = size;
	// gap 动态变化
	while (1) {
		gap = gap / 3 + 1;
		__InsertSort(array, size, gap);
		if (gap == 1) {
			break;
		}
	}
}


void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

// 不稳定
// 时间复杂度	O(n^2)
// 空间复杂度	O(1)
void SelectSort(int array[], int size)
{
	for (int i = size; i > 1; i--) {
		int max = 0;
		for (int j = 1; j < i; j++) {
			if (array[j] > array[max]) {
				max = j;
			}
		}

		Swap(array + max, array + i - 1);
	}
}

void SelectSortOP(int array[], int size)
{
	int left = 0, right = size - 1;
	while (left < right) {
		int min = left, max = left;
		for (int j = left + 1; j <= right; j++) {
			if (array[j] > array[max]) {
				max = j;
			}

			if (array[j] < array[min]) {
				min = j;
			}
		}
		Swap(array + left, array + min);
		if (max == left) {
			max = min;
		}
		Swap(array + right, array + max);

		left++; right--;
	}
}

void AdjustDown(int array[], int size, int root)
{
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	// 叶子	|| 满足堆的性质
	// 没有左右孩子
	// 因为完全二叉树，没有左孩子
	// 左孩子下标越界
	if (left >= size) {
		return;
	}

	// 找到左右孩子中谁是最大的（可能没有右孩子）
	int max = left;
	if (right < size && array[right] > array[left]) {
		max = right;
	}

	// 根据 [root] >= [最大的孩子]，调整结束
	// 否则，交换 [root] [最大的孩子]
	// 继续对 [最大的孩子] 进行向下调整的过程
	if (array[root] >= array[max]) {
		return;
	}

	Swap(array + root, array + max);
	AdjustDown(array, size, max);
}

void CreateHeap(int array[], int size)
{
	// 从最后一个非叶子结点 -> 0
	// 最后一个结点的双亲结点
	// [size - 1]	(child - 1)/2
	// 不断的进行向下调整

	for (int i = size / 2 - 1; i >= 0; i--) {
		AdjustDown(array, size, i);
	}
}

// 不稳定
// 时间复杂度	O(N*logN)
// 空间复杂度	O(1)
void HeapSort(int array[], int size)
{
	// 1. 建大堆（升序）	
	CreateHeap(array, size);

	for (int i = 0; i < size; i++) {
		Swap(&array[0], &array[size - 1 - i]);
		AdjustDown(array, size - i - 1, 0);
	}
}

// 冒泡排序
// 稳定
// 最好/平均/最差		O(n) 已经有序/O(n^2)/O(n^2)
// 空间复杂度			O(1)
void BubbleSort(int array[], int size)
{
	for (int i = 0; i < size - 1; i++) {
		int isSorted = 1;
		for (int j = 0; j < size - 1 - i; j++) {
			if (array[j] > array[j + 1]) {
				Swap(array + j, array + j + 1);
				isSorted = 0;
			}
		}

		if (isSorted == 1) {
			break;
		}
	}
}



void PrintArray(int array[], int size)
{
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int Partition_01(int array[], int left, int right)
{
	int begin = left;	// 不是 0
	int end = right;	// 不是 right - 1

	while (begin < end) {
		// 如果基准值在最右边，想先动 begin
		// array[begin] 要 <= 不能 <
		while (begin < end && array[begin] <= array[right]) {
			begin++;
		}

		while (begin < end && array[end] >= array[right]) {
			end--;
		}

		Swap(array + begin, array + end);
	}

	Swap(array + begin, array + right);

	return begin;
}

int Partition_02(int array[], int left, int right)
{
	int begin = left;	// 不是 0
	int end = right;	// 不是 right - 1
	int pivot = array[right];		// pivot 存的就是基准值

	while (begin < end) {
		// 如果基准值在最右边，想先动 begin
		// array[begin] 要 <= 不能 <
		while (begin < end && array[begin] <= pivot) {
			begin++;
		}

		array[end] = array[begin];

		while (begin < end && array[end] >= pivot) {
			end--;
		}

		array[begin] = array[end];
	}

	array[begin] = pivot;

	return begin;
}

// array [left, right]
// 左闭右闭
void __QuickSort(int array[], int left, int right)
{
	if (left == right) {
		// 只有 1 个数，已经有序
		return;
	}

	if (left > right) {
		// 没有数，不需要排序
		return;
	}

	int div = Partition_02(array, left, right);
	// div 是基准值所在的下标
	// [left, div-1]
	// [div+1, right]
	__QuickSort(array, left, div - 1);
	__QuickSort(array, div + 1, right);
}


void QuickSort(int array[], int size)
{
	__QuickSort(array, 0, size - 1);
}


void Test()
{
	int array[] = { 3, 5, 1, 4, 7, 2, 6, 0, 9, 8, 8 };
	// 1. 已经有序
	// 2. 完全逆序
	// 3. 乱序
	// 4. 相等
	// 5. 1 个数
	// 6. 0 个数
	// 7. 多个数
	//int array[] = { 1, 1, 1, 1, 1, 1, 1,1, 1 };
	int size = sizeof(array) / sizeof(int);
	//InsertSort(array, size);
	//QuickSort(array, size);
	HeapSort(array, size);
	PrintArray(array, size);
}