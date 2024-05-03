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
		if (arr[i] <= arr[j]) 
			b[k++] = arr[i++];
		else 
			b[k++] = arr[j++];
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