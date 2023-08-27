---
layout : post
title : xor 결과 최대 만들기
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---
# xor 결과 최대 만들기
n개의 음이 아닌 정수가 입력으로 주어졌을 때, 그 중 m개의 숫자를 뽑아 모두 xor한 결과의 최댓값을 출력하는 코드를 작성해보세요.

조합 문제 : 순서를 따지지 않고 중복을 허용하지 않는 경우
```cpp
#include <cstdio>
#include <iostream>
int arr[21] = { 0, };
int pick[21] = { 0, };
int isvisited[21] = { 0, };
int n, m;
int max_xor = 0;
void dfs(int cnt, int curr_num) 
{

    if(cnt == m)
    {
        int temp_xor = pick[0];
        // printf("%d ", pick[0]);
        for(int i = 1; i < m; i++)
        {
            temp_xor= temp_xor ^ pick[i];
            // printf("%d ", pick[i]);
        } 
        // printf("\n");
        if(max_xor < temp_xor)
            max_xor = temp_xor;
        return;
    }


    for(int i = curr_num; i < n; i++)
    {
            pick[cnt] = arr[i];
            dfs(cnt + 1, i + 1);     
    }
    return;
}
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    dfs(0, 0);
    printf("%d\n", max_xor);
    return 0;
}
```

해설 정답 코드
```cpp
#include <iostream>
#include <algorithm>

#define MAX_NUM 20

using namespace std;

// 전역 변수 선언:
int n, m;
int A[MAX_NUM];
bool visited[MAX_NUM];

int ans;

int Calc() {
    // xor 연산의 항등원인 0을 초기값으로 설정합니다.
    int val = 0;
    for(int i = 0; i < n; i++)
        if(visited[i])
            val ^= A[i];
    
    return val;
}

void FindMaxXor(int curr_idx, int cnt) {
    if(cnt == m) {
        // 선택된 모든 조합에 대해 xor 연산을 적용해봅니다.
        ans = max(ans, Calc());
        return;
    }

    if(curr_idx == n) 
        return;

    // curr_idx index 에 있는 숫자를 선택하지 않은 경우
    FindMaxXor(curr_idx + 1, cnt);
    
    // curr_idx index 에 있는 숫자를 선택한 경우
    visited[curr_idx] = true;
    FindMaxXor(curr_idx + 1, cnt + 1);
    visited[curr_idx] = false;
}

int main() {
    // 입력:
    cin >> n >> m;
    for(int i = 0; i < n; i++) 
        cin >> A[i];

    FindMaxXor(0, 0);
    
    // 출력:
    cout << ans;

    return 0;
}
```