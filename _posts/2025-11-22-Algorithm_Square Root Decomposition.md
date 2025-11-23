---
layout : post
title : Algorithm_Square Root Decomposition
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Square Root Decomposition

# 1. Square Root Decomposition 개요

**Square Root Decomposition** 은 배열에 대한 **구간 질의(range query)** 와 **점 업데이트(point update)** 를 빠르게 처리하기 위한 자료구조 기법이다.

크기 **N** 인 배열을 **대략 √N 크기의 블록(block)** 으로 나누고, 각 블록에 대해 **요약 정보(예: 합, 최소, 최대 등)** 를 미리 저장한다.

대표적인 사용 예

- 구간 합 Range Sum Query  
- 구간 최소 Range Minimum Query  
- 구간 최대 Range Maximum Query  
- 구간 XOR, 빈도 등 변형 가능

시간 복잡도

- 전처리 O(N)  
- 구간 질의 O(√N)  
- 점 업데이트 O(√N)

---

# 2. 기본 아이디어

배열 크기 N

1. 블록 크기 B = floor(√N)  
2. 블록 개수 ≒ N / B  
3. 각 블록에 대한 합, 최소, 최대 등 요약 정보를 저장  
4. 질의 시  
   - 양 끝 블록은 직접 계산  
   - 중간 블록들은 저장된 요약 값만 사용  

---

# 3. Range Sum Query 구조

배열 arr[i]  
보조 배열 blockSum[b]  

i 의 블록 번호 b = i / B

구간 [L, R] 처리

1. L 에서 시작 블록 경계까지 직접 더하기  
2. 중간 블록들은 blockSum[b] 만 더하기  
3. 마지막 블록의 일부를 직접 더하기

업데이트

- diff = val - arr[i]  
- blockSum[i / B] += diff  

---

# 4. C++ 구현

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int n;
int blockSize;
int numBlocks;
vector<long long> arr;
vector<long long> blockSum;

// 전처리
void build(const vector<long long>& input) {
    n = input.size();
    arr = input;

    blockSize = (int)sqrt(n);
    if (blockSize == 0) blockSize = 1;

    numBlocks = (n + blockSize - 1) / blockSize;
    blockSum.assign(numBlocks, 0);

    for (int i = 0; i < n; i++) {
        blockSum[i / blockSize] += arr[i];
    }
}

// 점 업데이트: arr[idx] = val
void updateSet(int idx, long long val) {
    int b = idx / blockSize;
    long long diff = val - arr[idx];
    arr[idx] = val;
    blockSum[b] += diff;
}

// 구간 합 쿼리: [L, R]
long long querySum(int L, int R) {
    long long res = 0;
    int startBlock = L / blockSize;
    int endBlock = R / blockSize;

    // 같은 블록이면 직접 계산
    if (startBlock == endBlock) {
        for (int i = L; i <= R; i++) res += arr[i];
        return res;
    }

    // L 이 포함된 블록의 경계까지 직접 더하기
    int endOfStart = (startBlock + 1) * blockSize - 1;
    for (int i = L; i <= endOfStart; i++) {
        res += arr[i];
    }

    // 사이에 있는 블록들 전체 더하기
    for (int b = startBlock + 1; b <= endBlock - 1; b++) {
        res += blockSum[b];
    }

    // R 이 포함된 블록의 일부 직접 더하기
    int startOfEnd = endBlock * blockSize;
    for (int i = startOfEnd; i <= R; i++) {
        res += arr[i];
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> n;

    vector<long long> input(n);
    for (int i = 0; i < n; i++) cin >> input[i];

    build(input);

    cin >> q;
    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int idx;
            long long val;
            cin >> idx >> val;
            updateSet(idx, val);

        } else if (type == 2) {
            int L, R;
            cin >> L >> R;
            cout << querySum(L, R) << "\n";
        }
    }

    return 0;
}

```

---

# 5. 시간 복잡도

- 전처리 O(N)  
- 점 업데이트 O(1) 수준  
- 구간 질의 O(√N)  

---

# 6. 변형들

- 구간 최소: blockMin[b] 사용  
- 구간 최대: blockMax[b] 사용  
- 구간 XOR, AND, OR 도 가능  

---

# 7. 장단점

장점

1. 구현이 단순  
2. 대회에서 사용하기 좋음  
3. 다양한 변형 가능  

단점

1. 세그먼트 트리보다 느릴 수 있음  
2. 구간 업데이트는 복잡해짐  

---

# 8. 결론

Square Root Decomposition 은  
구간 질의 + 점 업데이트 문제에 대해  
단순성과 성능 사이의 균형을 제공하는 유용한 방법이다.
