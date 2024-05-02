---
layout : post
title : 삼성 SW 역량 테스트 B형 Reference 코드
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---

# 삼성 SW 역량 테스트 B형 Reference 코드

## Hash의 hashing 함수

```cpp
unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

```


## Merge Sort

정렬된 배열 merge하기
```cpp
#include <stdio.h>

int N, M;

int a[1000100];
int b[1000100];

int main(void)
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}
		
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &b[i]);
	}
	int i, j;
	i = 0;
	j = 0;

	while (i < N && j < M)
	{

		if (a[i] > b[j])
		{
			printf("%d ", b[j++]);
		}
		else
		{
			printf("%d ", a[i++]);
		}
	}
	// 어차피 while 문 중 하나만 실행될 것
	while (i < N)
	{
		printf("%d ", a[i++]);
	}
	
	while (j < M)
	{
		printf("%d ", b[j++]);
	}
		
	return 0;
}

```

- Merge Sort 구현하기

```cpp
#include <stdio.h>

int b[100];

void merge(int* arr, int start, int end)
{
	int mid, i, j, k;

	mid = (start + end) >> 1;
	i = start;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= end)
	{
		if (arr[i] <= arr[j]) b[k++] = arr[i++];
		else b[k++] = arr[j++];
	}

	while (i <= mid)
	{
		b[k++] = arr[i++];
	}
	while (j <= end)
	{
		b[k++] = arr[j++];
	}
	for (i = start; i <= end; i++)
	{
		arr[i] = b[i - start];
	}

}

void sort(int* arr, int start, int end)
{
	int mid;
	if (start >= end)
		return;

	mid = (start + end) >> 1;
	sort(arr, start, mid);
	sort(arr, mid + 1, end);
	merge(arr, start, end);
}

int main(void)
{
	int arr[] = { -1, -12, 5, 4, 3, 7, 7, -2, -1, -3 };
	int length = sizeof(arr) / sizeof(int);

	sort(arr, 0, length - 1);

	for (int i = 0; i < length; i++)
	{
		printf("%d ", b[i]);
	}
	return 0;
}
```
