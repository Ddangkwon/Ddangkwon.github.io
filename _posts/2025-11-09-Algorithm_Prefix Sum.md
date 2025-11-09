---
layout : post
title : Algorithm_Prefix Sum
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Prefix Sum

# 개요

**Prefix Sum(누적 합)** 은 배열의 부분합을 빠르게 계산하기 위한 대표적인 전처리 기법이다.  
한 번의 전처리로 **모든 구간 합**을 O(1)에 계산할 수 있어, 완전탐색 O(N²) 문제를 O(N)으로 줄인다.

---

# 기본 개념

배열 **A[1..N]** 에 대해 다음과 같이 누적합 배열 **P[1..N]** 을 정의한다.

$$
P[i] = A[1] + A[2] + ... + A[i]
$$

즉, **P[i] = P[i-1] + A[i]**, 단 P[0] = 0 으로 정의한다.

이때 구간 [L, R]의 합은 다음처럼 O(1)에 계산된다.

$$
sum(L, R) = P[R] - P[L-1]
$$

---

# 예제 코드 (기본 1차원)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N+1), P(N+1, 0);

    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        P[i] = P[i-1] + A[i];
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;
        cout << P[R] - P[L-1] << "\n";
    }
    return 0;
}
```

---

# 2차원 Prefix Sum

2차원 배열에서도 동일 개념을 확장할 수 있다.

$$
S[y][x] = A[y][x] + S[y-1][x] + S[y][x-1] - S[y-1][x-1]
$$

구간합([y1,x1]~[y2,x2])은 다음처럼 구한다.

$$
sum = S[y2][x2] - S[y1-1][x2] - S[y2][x1-1] + S[y1-1][x1-1]
$$

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(N+1, vector<int>(N+1));
    vector<vector<int>> S(N+1, vector<int>(N+1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            cin >> A[i][j];
            S[i][j] = A[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1];
        }
    }

    while (M--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        int ans = S[y2][x2] - S[y1-1][x2] - S[y2][x1-1] + S[y1-1][x1-1];
        cout << ans << "\n";
    }
}
```

---

# Prefix Sum 변형 응용

## 1️⃣ 차이 배열(Difference Array)

구간 업데이트를 빠르게 수행할 때 사용한다.

예: `[L, R]` 구간에 +v 를 더할 때

```cpp
diff[L] += v;
diff[R+1] -= v;
```
그리고 마지막에 누적합 한 번 수행:
```cpp
for (int i = 1; i <= N; ++i)
    arr[i] = arr[i-1] + diff[i];
```

---

## 2️⃣ 부분합이 K인 구간 개수 세기

누적합 배열을 이용해 빠르게 조건을 만족하는 구간 수를 찾을 수 있다.

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K; cin >> N >> K;
    vector<long long> a(N+1), prefix(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> a[i];
        prefix[i] = prefix[i-1] + a[i];
    }

    unordered_map<long long,int> cnt;
    long long ans = 0;
    cnt[0] = 1; // prefix[0]
    for (int i = 1; i <= N; ++i) {
        ans += cnt[prefix[i] - K];
        cnt[prefix[i]]++;
    }
    cout << ans << "\n";
}
```

---

# 시간복잡도

| 연산 | 복잡도 |
|------|--------|
| 누적합 계산 | O(N) |
| 구간합 계산 | O(1) |
| 2차원 누적합 전처리 | O(N²) |
| 2차원 구간합 계산 | O(1) |

---

# 핵심 요약

| 포인트 | 설명 |
|--------|------|
| **1. 전처리로 O(1) 쿼리 처리** | P[i] = P[i-1] + A[i] |
| **2. 구간합 계산 공식** | sum(L,R)=P[R]-P[L-1] |
| **3. 2차원 확장 가능** | 영역합 계산 가능 |
| **4. 구간 업데이트는 차이 배열** | diff로 처리 후 누적 |
| **5. 누적합+해시 조합** | 부분합이 K인 구간 개수 등 다양한 문제 해결 가능 |

---

# 마무리

Prefix Sum은 모든 **누적 연산 기반 문제의 기본 도구**이다.  
누적합 배열은 단순하지만 강력하며, 슬라이딩 윈도우·DP 등과 결합하면 효율적인 풀이를 구성할 수 있다.
