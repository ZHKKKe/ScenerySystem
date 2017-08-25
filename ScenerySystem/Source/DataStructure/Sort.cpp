#include <iostream>
#include "Sort.h"

using namespace std;

// DescQuickSort - quick sort
void DescQuickSort(int *arr, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = arr[l];
		while (i < j)
		{
			while (i < j && arr[j] < x)
				j--;
			if (i < j)
				arr[i++] = arr[j];

			while (i < j && arr[i] >= x)
				i++;
			if (i < j)
				arr[j--] = arr[i];
		}
		arr[i] = x;
		DescQuickSort(arr, l, i - 1);
		DescQuickSort(arr, i + 1, r);
	}
}