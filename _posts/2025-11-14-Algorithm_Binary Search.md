---
layout : post
title : Algorithm_Binary Search
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Binary Search


# 개요

**Binary Search(이진 탐색)** 은 **정렬된 배열 또는 단조성을 가진 함수**에서 특정 값을 빠르게 찾는 알고리즘이다.  
단순 선형 탐색이 O(N) 인 반면, 이진 탐색은 **O(log N)** 으로 동작한다.

---

# 기본 원리

1. 탐색 구간의 시작(`low`)과 끝(`high`)을 지정한다.  
2. 중간 인덱스(`mid = (low + high) / 2`)를 계산한다.  
3. `mid` 위치의 값과 목표값을 비교한다.  
   - 목표값이 작으면 `high = mid - 1`
   - 목표값이 크면 `low = mid + 1`
4. 같으면 탐색 종료.  
5. 값이 없으면 `low > high` 시점에 종료된다.

---

# 예시 코드 (정확한 값 탐색)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    sort(arr.begin(), arr.end());

    int low = 0, high = n - 1;
    bool found = false;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            found = true;
            break;
        }
        else if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    cout << (found ? "YES" : "NO") << "\n";
}
```

---

# STL 이진 탐색 함수

C++ STL 은 이진 탐색을 위한 다양한 함수들을 제공한다.  
모두 `<algorithm>` 헤더에 정의되어 있다.

| 함수 | 반환 | 설명 |
|------|------|------|
| `binary_search(begin, end, val)` | bool | 존재 여부 확인 |
| `lower_bound(begin, end, val)` | iterator | `val` 이상이 처음 나오는 위치 |
| `upper_bound(begin, end, val)` | iterator | `val` 초과가 처음 나오는 위치 |
| `equal_range(begin, end, val)` | pair | [lower_bound, upper_bound) 구간 반환 |

---

# 예시: lower_bound / upper_bound

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> v = {1, 2, 2, 2, 3, 5, 7};
    int x = 2;

    auto lb = lower_bound(v.begin(), v.end(), x); // 첫 2의 위치
    auto ub = upper_bound(v.begin(), v.end(), x); // 마지막 2 다음 위치

    cout << "lower_bound index: " << (lb - v.begin()) << "\n";
    cout << "upper_bound index: " << (ub - v.begin()) << "\n";
    cout << "count of 2 = " << (ub - lb) << "\n";
}
```

출력:
```
lower_bound index: 1
upper_bound index: 4
count of 2 = 3
```

---

# 예시: 조건을 만족하는 최솟값 / 최댓값 찾기

이진 탐색은 단순 값 탐색뿐 아니라 **단조성(boolean monotonic)** 을 가지는 조건에 대해 경계값을 찾는 데 자주 쓰인다.

예시: `x^2 >= N` 을 만족하는 최소 x 찾기

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N; cin >> N;
    ll low = 0, high = N, ans = -1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        if (mid * mid >= N) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans << "\n"; // sqrt(N)의 올림값
}
```

---

# 응용 패턴

| 패턴 | 설명 |
|------|------|
| **정렬 배열에서 값 찾기** | 기본 이진 탐색 |
| **정답이 단조적인 문제** | parametric search(파라메트릭 서치) |
| **배열 내 특정 조건 만족 구간 찾기** | lower_bound / upper_bound |
| **함수의 경계 탐색** | 연속값 함수에서 최소/최대 경계값 계산 |
| **시간·거리·속도 등 이분 탐색** | Ex: 최소 시간, 최소 거리 등 문제 |

---

# Parametric Search (파라메트릭 서치)

**이진 탐색을 이용한 최적화 문제 풀이 기법**으로,  
“**조건을 만족하는 최솟값(혹은 최댓값)**” 을 구하는 형태로 자주 사용된다.

예제: 나무 자르기 문제 (BOJ 2805)

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; ll M;
    cin >> N >> M;
    vector<ll> tree(N);
    for (auto &t : tree) cin >> t;
    ll low = 0, high = *max_element(tree.begin(), tree.end());
    ll ans = 0;

    while (low <= high) {
        ll mid = (low + high) / 2;
        ll sum = 0;
        for (ll h : tree) if (h > mid) sum += (h - mid);

        if (sum >= M) { // 더 많이 잘랐으면 절단 높이를 높인다.
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    cout << ans << "\n";
}
```

---

# 시간복잡도

| 연산 | 복잡도 |
|------|--------|
| 이진 탐색 | O(log N) |
| lower_bound / upper_bound | O(log N) |
| parametric search | O(log N × f(N)) |

---

# 핵심 요약

| 포인트 | 설명 |
|--------|------|
| **1. 정렬 필요** | 이진 탐색은 정렬된 데이터에만 적용 가능 |
| **2. 중간값 계산 시 오버플로우 주의** | mid = low + (high - low) / 2 |
| **3. lower/upper_bound 적극 활용** | 경계 탐색 문제에 유용 |
| **4. Parametric Search** | 조건 만족 최소/최대값 탐색 시 강력 |
| **5. O(log N)** | 매우 효율적인 탐색 알고리즘 |

---

# 마무리

Binary Search 는 단순 탐색부터 최적화 문제까지 폭넓게 사용된다.  
특히 **단조성을 가진 조건**을 잘 정의하면, 거의 모든 “최소/최대” 문제를 해결할 수 있다.
