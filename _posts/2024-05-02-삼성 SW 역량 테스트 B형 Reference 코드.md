---
layout : post
title : 삼성 SW 역량 테스트 B형 Reference 코드
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---

# 삼성 SW 역량 테스트 B형 Reference 코드

## Hash 코드
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
#define ARR_MAX 110

int b[ARR_MAX];
int marr[ARR_MAX];
void merge(int* arr, int start, int end)
{
	int mid, i, j, k;

	mid = (start + end) >> 1;
	i = k = start;
	j = mid + 1;
	while (i <= mid && j <= end)
	{
		if (arr[i] < arr[j])
		{
			marr[k++] = arr[i++];
		}
		else
		{
			marr[k++] = arr[j++];
		}
	}
	while (i <= mid)
	{
		marr[k++] = arr[i++];
	}
		
	while (j <= end)
	{
		marr[k++] = arr[j++];
	}

	for (int i = start; i <= end; i++)
	{
		arr[i] = marr[i];
	}

}
void sort(int* arr, int start, int end)
{
	if (start >= end)
		return;
	int mid = (start + end) >> 1;
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
		printf("%d ", marr[i]);
	}
	return 0;
}
```


## DP, Memoization

다이나믹 프로그래밍은 조건을 만족해야 사용할 수 있다.

최적 부분 구조 - 큰 문제를 작은 문제로 나눌 수 있고, 작은 문제를 모아서 큰 문제를 해결

중복 부분 문제 - 동일한 작은 문제를 반복적으로 해결한다.

- 피보나치, 일반적인 DP 풀이 방식(재귀)

```cpp
#include <iostream>
using namespace std;

int fibo(int x){
	if(x==1 || x==2){
    	return 1;
    }
    return fibo(x-1)+fibo(x-2);
}

int main(){
	cout << fibo(4) << '\n';
    return 0;
}​
```

- 피보나치, Memoization 탑 다운 방식 (재귀 사용)

```cpp
// Memoization 탑다운 방식
#include <iostream>
using namespace std;

// 한 번 계산된 결과를 메모이제이션(Memoization)하기 위한 리스트 초기화
long long d[100];

// 피보나치 함수를 재귀함수로 구현(탑다운 다이나믹 프로그래밍)
int fibo(int x) {
	// 종료조건(1혹은 2일때 1반환)
    if(x==1 || x==2){
    	return 1;
    }
    // 이미 계산한적 있는 문제라면 그대로 반환
    if(d[x] != 0) {
    	return d[x];
    }
    // 아직 계산하지 않은 문제라면 점화식에 따라서 피보나치 결과 반환
    return d[x] = fibo(x-1) + fibo(x-2);
}

int main() {
	int N;
    cin >> N;
    cout << fibo(N);
}
```

- 피보나치, Memoization 바텀업 방식 (반복문 사용)

```cpp
// 바텀업 방식
#include <iostream>
using namespace std;
// 앞서 계산된 결과를 저장하기 위한 DP테이블 초기화
long long  d[100];

int main(void){
  // 첫번째, 두번째 피보나치 수열은 1
  d[1] = 1;
  d[2] = 1;
  int n = 50;
  
  // 피보나치 함수 반복문으로 구현 (바텀업 다이나믹 프로그래밍)
  for(int i=3; i<n+1; i++){
  	d[i] = d[i-1]+d[i-2];
  }
  cout << d[n] << '\n';
  return 0;
}
```


### 다이나믹 프로그래밍 VS 분할 정복

공통점 : 모두 최적 부분 구조를 가질 때 사용 가능

(큰 문제를 작은 문제로 나눌 수 있으며 작은 문제의 답을 모아서 큰 문제를 해결할 수 있는 상황)

 

차이점 : 부분 문제 정복.

(다이나믹 프로그래밍 문제에서는 각 부분 문제들이 서로 영향을 미치며 부분 문제가 중복되고,

분할 정복 문제에서는 동일한 부분 문제가 반복적으로 계산되지 않는다.)

분할 정복의 대표 사례인 퀵 정렬에서는 한 번 기준 원소가 자리를 변경해서 자리를 잡으면, 그 기준 원소의 위치가 바뀌지 않는다.

또한 분할 이후에 해당 피벗을 다시 처리하는 부분에서 다시 호출하지 않는다.

동적 계획법은 이미 해결한 문제를 반복적으로 해결하여 비효율적인 문제에서 유용할 것이다.


## 우선순위 큐(priority queue)

- B형에서 Merge Sort는 마지막에 이분 탐색을 위해 필요한 경우가 많다.
 - 그리고 '무언가'를 push해주고, 그 중 가장 우선순위가 높은 '무언가'를 pop하면서, 순서를 유지하고 싶을 때는 우선순위 큐를 이용한다.
 - 우선순위 큐는 즉 자동 정렬되는 큐라고 이해하면 편하다.

```cpp
#include <stdio.h>

#define ARR_MAX 110

int heap[ARR_MAX];
int hn;
int N;
int pop(int* heap, int& hn)
{
	register int tmp, ret;
	//1) pop의 return값 heap[1]을 기억해둔다.
	ret = heap[1];
	//2) heap의 배열에서 가장 끝에 값, 즉 heap[hn]을 heap[1]로 변경한다.
	heap[1] = heap[hn];
	//3) heap[hn]은 최악의 우선순위값(최소힙이므로 0x7fff0000 정도의 큰 값)으로 변경해둔다.
	//4) heap이 1개 줄었으므로 hn 을 1 감소 시킨다.
	heap[hn--] = 0x7fff0000;

	for (register int i = 1; i * 2 <= hn;)
	{
		if (heap[i] < heap[i * 2] && heap[i] < heap[i * 2 + 1]) break;
		else if (heap[i * 2] < heap[i * 2 + 1])
		{
			tmp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = tmp;

			i = i * 2;
		}
		else
		{
			tmp = heap[i * 2 + 1];
			heap[i * 2 + 1] = heap[i];
			heap[i] = tmp;

			i = i * 2 + 1;
		}
	}

	return ret;
}

void push(int* heap, int& hn, int x)
{
	register int tmp;
	//모든 i에 대해서 자식 node는 i * 2, i * 2 + 1이 되고,
	//부모 node는 i / 2로 하면 된다.

	heap[++hn] = x;
	for (register int i = hn; i > 1; i /= 2)
	{
		// 자식 노드가 더 크면 pass
		if (heap[i / 2] <= heap[i]) 
			break;
		// 아니면 조상 <-> 부모 <-> 자식 노드간에 교환을 반복해서 수행한다. (부모노드가 자식노드보다 작을때까지)
		// 부모 노드와 자식 노드와의 교환
		tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}

int main(void)
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int x = scanf("%d", &x);
		if (x)
		{
			push(heap, hn, x);
		}
		else
		{
			if (hn)
			{
				printf("%d", pop(heap, hn));
			}
			// 큐가 비어있는 경우
			else
			{
				printf("0\n");
			}
		}

	}
	//int heap_len = sizeof(heap) / sizeof(int);
	//for (int i = 1; i < heap_len; i++)
	//{
	//	printf("%d ", heap[i]);
	//}
	return 0;
}
```