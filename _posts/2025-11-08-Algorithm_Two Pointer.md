---
layout : post
title : Algorithm_Two Pointer
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Two Pointer


# 개요

**Two Pointers(투 포인터)** 는 하나의 배열 또는 두 개의 배열 위에서 두 개의 인덱스 포인터를 이동시키며 답을 구하는 기법이다. **Sliding Window(슬라이딩 윈도우)** 는 Two Pointers의 특수 케이스로, 구간의 왼쪽·오른쪽 경계를 포인터로 관리해 **연속 구간 성질**을 유지한 채 확장·축소한다. (정렬된 배열에서 해당 알고리즘을 사용해야 함)

이 기법은 누적합 대비 메모리 사용이 적고, 완전탐색의 O(N²) 을 O(N) 또는 O(N log N) 으로 줄이는 데 효과적이다.

---

## 알고리즘 활용 포인트

- 정렬된 배열에서 합이나 차이의 조건을 만족하는 쌍, 트리플을 찾을 때 적합하다.
- **연속 구간**에 대한 합, 개수, 조건 만족 여부를 관리할 때 슬라이딩 윈도우가 적합하다.
- 윈도우 내부의 성질이 **단조(monotonic)** 하게 변해 왼쪽 포인터를 이동할 충분조건이 있을 때 효과적이다.
- 음수가 섞인 합 문제는 윈도우 불변식이 깨지는 경우가 많아 주의가 필요하다. 이 경우 자료구조 보강이나 다른 기법이 필요하다.

---

## 시간복잡도

| 패턴 | 전형 복잡도 |
| --- | --- |
| 두 포인터 합/차이 탐색 | O(N) |
| 가변 길이 슬라이딩 윈도우(해시맵 동반) | O(N) 평균 |
| 고정 길이 슬라이딩 윈도우 | O(N) |

두 포인터는 각 포인터가 배열을 최대 한 번씩만 끝까지 이동하기 때문에 O(N) 이 된다.

---

# 기본 패턴

## 1. 같은 배열에서 양끝 수렴(two-sum on sorted)

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n; ll target;
    cin >> n >> target;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) 
        cin >> a[i];
    // 정렬된 배열에서 사용되는 알고리즘이기 때문에 먼저 정렬 수행
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    bool ok = false;
    while (l < r) {
        ll s = a[l] + a[r];
        if (s == target) { 
            ok = true; 
            break; 
        }
        if (s < target) 
            ++l;
        else 
            --r;
    }
    cout << (ok ? "YES\n" : "NO\n");
    return 0;
}
```

---

## 2. 서로 다른 두 배열 머지·교집합 탐색

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin >> n >> m;
    vector<int> A(n), B(m);
    for (int &x: A) 
        cin >> x;
    for (int &y: B) 
        cin >> y;
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int i = 0, j = 0;
    vector<int> inter;

    while (i < n && j < m) {
        if (A[i] == B[j]) { 
            inter.push_back(A[i]); 
            ++i; ++j; 
        }
        else if 
            (A[i] < B[j]) ++i;
        else 
            ++j;
    }

    for (int z: inter) 
        cout << z << ' ';

    cout << '\n';
}
```

---

## 3. 고정 길이 슬라이딩 윈도우(fixed window)

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int n, k; 
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) 
        cin >> a[i];

    ll sum = 0, best = LLONG_MIN;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (i >= k) 
            sum -= a[i - k];
        if (i >= k - 1) 
            best = max(best, sum);
    }
    cout << best << '\n';
}
```

---

## 4. 가변 길이 슬라이딩 윈도우(양수 배열의 부분합)

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; 
    long long S; 
    cin >> n >> S;
    vector<long long> a(n);
    for (auto &x: a) 
        cin >> x;

    long long sum = 0;
    int ans = INT_MAX, l = 0;
    for (int r = 0; r < n; ++r) {
        sum += a[r];
        while (l <= r && sum - a[l] >= S) { 
            sum -= a[l]; ++l; 
        }
        if (sum >= S) 
            ans = min(ans, r - l + 1);
    }
    cout << (ans == INT_MAX ? 0 : ans) << '\n';
}
```

---

# 마무리

Two Pointers 및 Sliding Window 는 연속 구간의 성질과 단조성을 이용해 완전탐색을 선형으로 줄이는 핵심 기법이다. 정렬 전제와 윈도우 불변식을 정확히 세우고, 포인터 전진 규칙을 명확히 구현하면 대부분의 고전 문제를 효율적으로 해결할 수 있다.
