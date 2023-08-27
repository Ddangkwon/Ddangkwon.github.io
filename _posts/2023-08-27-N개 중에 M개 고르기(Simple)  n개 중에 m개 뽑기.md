---
layout : post
title : N개 중에 M개 고르기(Simple) n개 중에 m개 뽑기
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---
# N개 중에 M개 고르기(Simple)  n개 중에 m개 뽑기

1이상 N이하의 숫자 중 M개의 숫자를 골라 만들 수 있는 모든 조합을 구해주는 프로그램을 작성해보세요.

예를 들어 N이 4, M이 3인 경우 다음과 같이 4개의 조합이 가능합니다.

1 2 3

1 2 4

1 3 4

2 3 4


```cpp
#include <cstdio>
#include <iostream>

int N, M;
int isvisited[11] = { 0, };
int arr[11] = { 0, };
void dfs(int cnt)
{
    if(cnt == M)
    {   
        int temp_cnt = 1;
        while(temp_cnt < cnt)
        {
            if(arr[temp_cnt - 1] > arr[temp_cnt])
                return;
            temp_cnt++;
        }
        for(int i = 0; i < M; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for(int i = 1; i <= N; i++)
    {
        if(isvisited[i] == 0)
        {
            arr[cnt] = i;
            isvisited[i] = 1;
            dfs(cnt + 1);
            isvisited[i] = 0;
        }
        
        
    }

    return ;
}
int main() {
    
    scanf("%d %d", &N, &M);
    dfs(0);
    return 0;
}
```

개선 답안
```cpp

#include <cstdio>
#include <iostream>

int N, M;
int arr[11] = { 0, };
void dfs(int cnt, int curr_num)
{
    if(cnt == M)
    {   
        for(int i = 0; i < M; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        return;
    }
    for(int i = curr_num; i <= N; i++)
    {
        arr[cnt] = i;
        dfs(cnt + 1, i + 1);      
    }

    return ;
}
int main() {
    
    scanf("%d %d", &N, &M);
    dfs(0, 1);
    return 0;
}

```
해설 정답 코드
```cpp
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> combination;

// 방문한 원소들을 출력해줍니다.
void PrintCombination() {
    for(int i = 0; i < combination.size(); i++)
        cout << combination[i] << " ";
    cout << endl;
}

// 지금까지 뽑은 갯수와 뽑을지 말지를 결정할 숫자를 인자로 받습니다. 
void FindCombination(int curr_num, int cnt) {

    // n개의 숫자를 모두 탐색했으면 더 이상 탐색하지 않습니다.
    if(curr_num == n+1) {
        // 탐색하는 과정에서 m개의 숫자를 뽑은 경우 답을 출력해줍니다.
        if(cnt == m)
            PrintCombination();
        return;
    }

    // curr_num에 해당하는 숫자를 사용했을 때의 경우를 탐색합니다.
    combination.push_back(curr_num);
    FindCombination(curr_num + 1, cnt + 1);
    combination.pop_back();

    // curr_num에 해당하는 숫자를 사용하지 않았을 때의 경우를 탐색합니다.
    FindCombination(curr_num + 1, cnt);
}

int main() {
    cin >> n >> m;

    FindCombination(1, 0);
    return 0;
}
```