#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

#include "arrange.h"

using namespace std;

vector<int> &bubblesort(vector<int>& array)
{
	for (unsigned short i = 0; i < array.size(); i++)
	{
		bool isExchanged = false;
		for (unsigned short j = 0; j < array.size() - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
				isExchanged = true;
			}
		}
		if (!isExchanged)
			break;
	}
	return array;
}

vector<int> &selectSort(vector<int>& array)
{
	for (unsigned short i = 0; i < array.size(); i++)
	{
		unsigned short minIndex = i;
		for (unsigned short j = i + 1; j < array.size(); j++)
		{
			if (array[minIndex] > array[j])
				minIndex = j;
		}
		if (minIndex != i)
			swap(array[i], array[minIndex]);
	}
	return array;
}

vector<int> &isertionSort(vector<int>& array)
{
	for (unsigned short i = 1; i < array.size(); i++)
	{
		unsigned short pred_index = i - 1;
		int current = array[i];

		for (; pred_index >= 0; pred_index--)
			if (array[pred_index] >= current)
				array[pred_index + 1] = array[pred_index];
			else
				break;

		array[pred_index + 1] = current;
	}
	return array;
}

vector<int> &shellSort(vector<int>& array)
{
	unsigned short n = array.size();
	for (unsigned short gap = n / 2; gap >= 1; gap /= 2)
	{
		for (unsigned short i = gap; i < n;i++)
		{
			int itermToInsert = array[i];
			int j = i - gap;
			while (j >= 0 && array[i] >= itermToInsert)
			{
				array[j + gap] = array[j];
				j -= gap;
			}
			array[j + gap] = itermToInsert;
		}
	}
}


class Merge
{
public:
	void merge(vector<int>& arr, vector<int> copyarr, u8 left, u8 right)
	{
		u8 mid = (left + right) / 2;
		u8 i = left, j = mid + 1, k = 0;
		while (i <= mid || j <= right)
		{
			if (i > mid)
			{
				copyarr[k] = arr[j];
				j++;
			}
			else if(j>right)
			{
				copyarr[k] = arr[i];
				i++;
			}
			else
			{
				copyarr[k] = arr[i];
				i++;
			}
			k++;
		}
		for (u8 i = left; i <= right; i++)
		{
			arr[i] = copyarr[i - left];
		}
	}

	void mergeSortHelp(vector<int>& arr, vector<int> copyarr, u8 left, u8 right)
	{
		if (left < right)
		{
			u8 mid = (left + right) / 2;
			mergeSortHelp(arr, copyarr, left, mid);
			mergeSortHelp(arr, copyarr, mid + 1, right);
			merge(arr, copyarr, left, right);
		}
	}
	//递归实现归并排序
	vector<int> &mergeSortRecursive(vector<int>& arr)
	{
		vector<int> copyarr(arr);
		mergeSortHelp(arr, copyarr, 0, arr.size() - 1);
		return arr;
	}

	//迭代实现归并排序
	vector<int> &mergeSortIteration(vector<int>& arr)
	{
		vector<int> copyarr(arr);
		u8 left = 0, right = arr.size() - 1;
		stack<vector<int>> boundaries;
		while (left < right || !boundaries.empty())
		{
			if (left < right)
			{
				boundaries.push({ left,right });
				right = (left + right) / 2;
			}
			else
			{
				vector<int> boundary = boundaries.top();
				boundaries.pop();
				left = boundary[0];
				right = boundary[1];
				merge(arr, copyarr, left, right);

				if (boundaries.empty())
					break;

				boundary = boundaries.top();
				left = right + 1;
				right = boundary[1];
			}
		}
		return arr;
	}
};

class QuickSort
{
private:

public:
	int medianPovit(vector<int>& arr, u8 left, u8 mid, u8 right)
	{
		if (arr[left] > arr[mid])
			swap(arr[mid], arr[left]);
		if (arr[left] > arr[right])
			swap(arr[left], arr[right]);
		if (arr[mid] > arr[right])
			swap(arr[mid], arr[right]);

		return arr[mid];
	}
	u8 partition(vector<int>& arr, u8 left, u8 right)
	{
		u8 mid = (left + right) / 2;
		int povit = medianPovit(arr, left, mid, right);
		arr[mid] = arr[right - 1];
		arr[right - 1] = povit;

		u8 i = left, j = right - 1;
		while (i<j)
		{
			if (arr[i] < povit)
				i++;
			else if (arr[j] >= povit)
				j--;
			else
				swap(arr[i], arr[j]);
		}
		swap(arr[i], arr[j]);
		return i;
	}
	vector<int>& quickSortHelp(vector<int>& arr, u8 left, u8 right)
	{
		if (left < right)
		{
			u8 pivotLoction = partition(arr, left, right);
			quickSortHelp(arr, left, pivotLoction - 1);
			quickSortHelp(arr, pivotLoction, right);
		}
		return arr;
	}
	vector<int>& quickSortRecursive(vector<int>& arr)
	{
		return quickSortHelp(arr, 0, arr.size() - 1);
	}

	vector<int> &quickSortIteration(vector<int>& arr)
	{
		stack<vector<int>> boundaries;
		u8 left = 0, right = arr.size() - 1;
		while (left<right || !boundaries.empty())
		{
			if (left < right)
			{
				vector<int> boundary = boundaries.top();
				boundaries.pop();
				left = boundary[0];
				right = boundary[1];
			}
			u8 pivotLocation = partition(arr, left, right);
			if (pivotLocation + 1 < right)
			{
				boundaries.push({ pivotLocation + 1,right });
			}
			right = pivotLocation - 1;
		}
		return arr;
	}
};

class HeapSort
{
public:
	void moveDown(vector<int>& arr, u8 first, u8 last)
	{
		u8 curIndex = first * 2 + 1;
		while (curIndex<=last)
		{
			if (curIndex < last&&arr[curIndex] < arr[curIndex + 1])
				curIndex++;

			if (arr[first] < arr[curIndex])
			{
				swap(arr[first], arr[curIndex]);
				first = curIndex;
				curIndex = 2 * first + 1;
			}
			else
				break;
		}
	}
	void buildHeap(vector<int>& arr)
	{
		u8 i = arr.size() / 2 - 1;
		while (i>=0)
		{
			moveDown(arr, i, arr.size() - 1);
			i--;
		}
	}
	vector<int>& heapSort(vector<int>& arr)
	{
		buildHeap(arr);
		u8 first = 0, last = arr.size() - 1;
		while (first <= last)
		{
			swap(arr[first], arr[last]);
			last--;
			moveDown(arr, first, last);
		}
		return arr;
	}
};

vector<int> &countSort(vector<int>& arr)
{
	if (arr.empty())
		return arr;

	int min = arr.front(), max = arr.front();
	for (u8 i = 1; i < arr.size(); i++)
	{
		if (min > arr[i])
			min = arr[i];
		else if (max < arr[i])
			max = arr[i];
	}

	vector<int> counts(max - min + 1);
	for (u8 i = 0; i < arr.size(); i++)
		counts[arr[i] - min]++;

	u8 index = 0;
	for (u8 j = 0; j < counts.size(); j++)
	{
		u8 n = counts[j];
		while (n--)
		{
			arr[index] = j + min;
			index++;
		}
	}
	return arr;
}


void bucketSort(vector<int>& array, int bucketCount) {
	if (array.empty()) {
		return;
	}
	// 找出最大最小值
	int max = array.front(), min = array.front();
	for (int i = 1; i < array.size(); i++) {
		if (min > array[i]) {
			min = array[i];
		}
		else if (max < array[i]) {
			max = array[i];
		}
	}

	// 将待排序的各元素分入对应桶中
	vector<vector<int>> buckets(bucketCount);
	int bucketSize = ceil((double)(max - min + 1) / bucketCount);
	for (int i = 0; i < array.size(); i++) {
		int bucketIndex = (array[i] - min) / bucketSize;
		buckets[bucketIndex].push_back(array[i]);
	}

	// 对各桶中元素进行选择排序
	int index = 0;
	for (vector<int> bucket : buckets) {
		if (!bucket.empty()) {
			// 使用选择排序算法对桶内元素进行排序
			selectSort(bucket);
			for (int value : bucket) {
				array[index] = value;
				index++;
			}
		}
	}

}
// 桶排序
void bucketSort(vector<int>& array) {
	bucketSort(array, array.size() / 2);
}

vector<int> &radixSort(vector<int>& arr)
{
	u8 curdigit = 10;
	bool isOverHighest = false;
	while (!isOverHighest)
	{
		isOverHighest = true;
		vector<vector<int>> buckets(10);

		for (u8 curVal : arr)
		{
			u8 bucketIndex = curVal%curdigit - curVal % (curdigit / 10);
			buckets[bucketIndex].push_back(curVal);
			if (isOverHighest&&curVal / curdigit)
				isOverHighest = false;
		}
	}

	u8 index = 0;
	for (vector<int>bucket : buckets)
	{
		for (int value : bucket)
		{
			arr[index] = value;
			index++;
		}
		curdigit *= 10;
	}
	return arr;
}

