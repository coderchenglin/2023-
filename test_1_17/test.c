#include "Sort.h"
#include "Stack.h"

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

// �ʱ�临�Ӷ�O(N^2) -- ����
// ���ʱ�临�Ӷ�O(N) -- ˳������
void InsertSort(int* a, int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
		// [0,end] ���� end+1 [0, end+1]����
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
		}

		a[end + 1] = tmp;
	}
}
//
//void ShellSort(int* a, int n)
//{
	//int gap = 3;
	//for (int j = 0; j < gap; ++j)
	//{
	//	for (int i = j; i < n - gap; i += gap)
	//	{
	//		// [0,end] ���� end+gap [0, end+gap]����  -- ���Ϊgap������
	//		int end = i;
	//		int tmp = a[end + gap];
	//		while (end >= 0)
	//		{
	//			if (a[end] > tmp)
	//			{
	//				a[end + gap] = a[end];
	//				end -= gap;
	//			}
	//			else
	//			{
	//				break;
	//			}
	//		}
	//		a[end + gap] = tmp;
	//	}
	//}	

	// gap > 1  Ԥ����
	// gap == 1 ֱ�Ӳ�������

// O(N^1.3)
void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		//gap = gap / 2;
		gap = gap / 3 + 1;

		// [0,end] ���� end+gap [0, end+gap]����  -- ���Ϊgap������
		for (int i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void AdjustDown(int* a, int n, int parent)
{
	int minChild = parent * 2 + 1;
	while (minChild < n)
	{
		// �ҳ�С���Ǹ�����
		if (minChild + 1 < n && a[minChild + 1] > a[minChild])
		{
			minChild++;
		}

		if (a[minChild] > a[parent])
		{
			Swap(&a[minChild], &a[parent]);
			parent = minChild;
			minChild = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

// O(N*logN)
void HeapSort(int* a, int n)
{
	// ��˼·��ѡ����������ѡ�����Ӻ���ǰ��
	// ���� -- ���
	// ���� -- С��
	// ���� -- ���µ������� - O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	// ѡ�� N*logN
	int i = 1;
	while (i < n)
	{
		Swap(&a[0], &a[n - i]);
		AdjustDown(a, n - i, 0);
		++i;
	}
}

// �ʱ�临�Ӷȣ�O(N^2)
// ���ʱ�临�Ӷȣ�O(N^2)
void SelectSort(int* a, int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		// ѡ����С�ķ�beginλ��
		// ѡ�����ķ�endλ��
		int mini = begin, maxi = begin;
		for (int i = begin + 1; i <= end; ++i)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}

			if (a[i] < a[mini])
			{
				mini = i;
			}
		}

		Swap(&a[begin], &a[mini]);
		// ����һ��maxi
		if (maxi == begin)
			maxi = mini;

		Swap(&a[end], &a[maxi]);
		++begin;
		--end;
	}
}

// ������O(N^2)
// ��������O(N)
void BubbleSort(int* a, int n)
{
	for (int j = 0; j < n; ++j)
	{
		int exchange = 0;
		for (int i = 1; i < n - j; ++i)
		{
			if (a[i - 1] > a[i])
			{
				Swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}
		if (exchange == 0)
		{
			break;
		}
	}
}

int GetMidIndex(int* a, int left, int right)
{
	int mid = left + (right - left) / 2;
	if (a[left] < a[mid])
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else if (a[left] > a[right])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	else // a[left] >= a[mid]
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else if (a[left] < a[right])
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}

// [left, right] -- O(N)
// hoare
int PartSort1(int* a, int left, int right)
{
	// ����ȡ��
	int mid = GetMidIndex(a, left, right);
	//printf("[%d,%d]-%d\n", left, right, mid);

	Swap(&a[left], &a[mid]);

	int keyi = left;
	while (left < right)
	{
		// 6 6 6 6 6
		// R��С
		while (left < right && a[right] >= a[keyi])
		{
			--right;
		}

		// L�Ҵ�
		while (left < right && a[left] <= a[keyi])
		{
			++left;
		}

		if (left < right)
			Swap(&a[left], &a[right]);
	}

	int meeti = left;

	Swap(&a[meeti], &a[keyi]);

	return meeti;
}

// �ڿӷ�
int PartSort2(int* a, int left, int right)
{
	// ����ȡ��
	int mid = GetMidIndex(a, left, right);
	Swap(&a[left], &a[mid]);

	int key = a[left];
	int hole = left;
	while (left < right)
	{
		// �ұ���С�����߿�
		while (left < right && a[right] >= key)
		{
			--right;
		}

		a[hole] = a[right];
		hole = right;

		// ����Ҵ���ұ߿�
		while (left < right && a[left] <= key)
		{
			++left;
		}

		a[hole] = a[left];
		hole = left;
	}

	a[hole] = key;
	return hole;
}

// ǰ��ָ�뷨
int PartSort3(int* a, int left, int right)
{
	// ����ȡ��
	int mid = GetMidIndex(a, left, right);
	Swap(&a[left], &a[mid]);

	int keyi = left;
	int prev = left;
	int cur = left + 1;
	while (cur <= right)
	{
		// ��С
		if (a[cur] < a[keyi] && ++prev != cur)
			Swap(&a[cur], &a[prev]);

		++cur;
	}

	Swap(&a[keyi], &a[prev]);

	return prev;
}

// ��Ϣ10:33����
// [begin, end]
void QuickSort(int* a, int begin, int end)
{
	if (begin >= end)
	{
		return;
	}

	//if (end - begin <= 8)
	//{
	//	InsertSort(a + begin, end - begin + 1);
	//}
	//else
	//{
	int keyi = PartSort3(a, begin, end);
	//[begin, keyi-1] keyi [keyi+1, end]

	QuickSort(a, begin, keyi - 1);
	QuickSort(a, keyi + 1, end);
	//}
}

void QuickSortNonR(int* a, int begin, int end)
{
	ST st;
	StackInit(&st);
	StackPush(&st, begin);
	StackPush(&st, end);

	while (!StackEmpty(&st))
	{
		int right = StackTop(&st);
		StackPop(&st);

		int left = StackTop(&st);
		StackPop(&st);

		/*if (left >= right)
		{
			continue;
		}*/

		int keyi = PartSort3(a, left, right);
		// [left, keyi-1] keyi [keyi+1,right]

		if (keyi + 1 < right)
		{
			StackPush(&st, keyi + 1);
			StackPush(&st, right);
		}

		if (left < right - 1)
		{
			StackPush(&st, left);
			StackPush(&st, keyi - 1);
		}
	}

	StackDestroy(&st);
}

void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;

	int mid = (end + begin) / 2;
	// [begin, mid] [mid+1, end]

	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid + 1, end, tmp);

	// �鲢 ȡС��β��
	// [begin, mid] [mid+1, end]
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}

	while (begin2 <= end2)
	{
		tmp[i++] = a[begin2++];
	}

	// ������ԭ���� -- �鲢�Ĳ��־Ϳ����Ĳ��ֻ�ȥ
	memcpy(a + begin, tmp + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}

	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);
	tmp = NULL;
}

void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}

	int gap = 1;
	while (gap < n)
	{
		// gap������  gap�����ݹ鲢
		for (int j = 0; j < n; j += 2 * gap)
		{
			// �鲢 ȡС��β��
			int begin1 = j, end1 = j + gap - 1;
			int begin2 = j + gap, end2 = j + 2 * gap - 1;

			// ��һ��Խ��
			if (end1 >= n)
			{
				printf("[%d,%d]", begin1, n - 1);
				break;
			}

			// �ڶ���ȫ��Խ��
			if (begin2 >= n)
			{
				printf("[%d,%d]", begin1, end1);
				break;
			}

			// �ڶ��鲿��Խ��
			if (end2 >= n)
			{
				// ����һ��end2�������鲢
				end2 = n - 1;
			}

			printf("[%d,%d][%d,%d] ", begin1, end1, begin2, end2);

			int i = j;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] <= a[begin2])
				{
					tmp[i++] = a[begin1++];
				}
				else
				{
					tmp[i++] = a[begin2++];
				}
			}

			while (begin1 <= end1)
			{
				tmp[i++] = a[begin1++];
			}

			while (begin2 <= end2)
			{
				tmp[i++] = a[begin2++];
			}

			// ������ԭ���� -- �鲢�Ĳ��־Ϳ����Ĳ��ֻ�ȥ
			memcpy(a + j, tmp + j, (end2 - j + 1) * sizeof(int));
		}

		gap *= 2;
		printf("\n");
	}

	free(tmp);
	tmp = NULL;
}

// ʱ�临�Ӷȣ�O(N+range)
// �ռ临�Ӷȣ�O(range)
// �ʺ����ݷ�Χ���У�Ҳ����rangeС
// ֻ�ʺ����������ʺϸ��������ַ�����
void CountSort(int* a, int n)
{
	int max = a[0], min = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
		}

		if (a[i] < min)
		{
			min = a[i];
		}
	}

	int range = max - min + 1;
	// ͳ�ƴ���
	int* countA = (int*)malloc(sizeof(int) * range);
	if (countA == NULL)
	{
		perror("malloc fail");
		return;
	}
	memset(countA, 0, sizeof(int) * range);

	for (int i = 0; i < n; ++i)
	{
		countA[a[i] - min]++;
	}

	// ����
	int j = 0;
	for (int i = 0; i < range; ++i)
	{
		while (countA[i]--)
		{
			a[j] = i + min;
			++j;
		}
	}

	free(countA);
}