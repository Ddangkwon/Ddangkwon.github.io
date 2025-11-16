---
layout : post
title : Algorithm_Union Find
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Union Find


# 개요

**Union-Find(서로소 집합, Disjoint Set)** 은 여러 원소가 속한 집합을 효율적으로 관리하기 위한 자료구조이다.  
특히 **집합의 합치기(Union)** 와 **대표 원소 찾기(Find)** 연산을 매우 빠르게 수행할 수 있다.

대표적인 활용 분야는 다음과 같다.

- 그래프의 **사이클 판별**
- **MST(최소 스패닝 트리)** 알고리즘 (Kruskal)
- 네트워크 연결 여부 확인
- 집합 간 관계 관리

---

# 핵심 개념

Union-Find 구조는 **트리 기반 집합 표현**을 사용한다.

- **parent[x]**: x의 부모 노드 (루트면 자기 자신)
- **find(x)**: x가 속한 집합의 대표(root)를 찾음
- **union(a, b)**: a와 b가 속한 두 집합을 하나로 합침

---

# 기본 구조

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int find_parent(int x) {
    if (parent[x] == x) 
        return x; // 루트 노드
    return parent[x] = find_parent(parent[x]); // 경로 압축(Path Compression)
}

void union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a < b) 
        parent[b] = a;
    else 
        parent[a] = b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m; // 노드, 연산 수
    parent.resize(n + 1);

    for (int i = 1; i <= n; ++i) 
        parent[i] = i;

    for (int i = 0; i < m; ++i) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 0) 
            union_parent(a, b); // 합치기
        else {
            if (find_parent(a) == find_parent(b)) 
                cout << "YES\n";
            else 
                cout << "NO\n";
        }
    }
}
```

---

# 최적화 기법

## 1️⃣ 경로 압축 (Path Compression)

find 연산 시 재귀적으로 올라가며, **부모를 루트로 직접 연결**한다.  
이를 통해 시간 복잡도를 거의 O(1)에 가깝게 만든다.

```cpp
int find_parent(int x) {
    if (parent[x] != x)
        parent[x] = find_parent(parent[x]);
    return parent[x];
}
```

## 2️⃣ 랭크(또는 크기) 기반 합치기 (Union by Rank/Size)

작은 트리를 큰 트리에 붙이면 트리 깊이가 줄어든다.

```cpp
vector<int> parent, rankv;

void union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a == b) 
        return;

    if (rankv[a] < rankv[b]) 
        swap(a, b);

    parent[b] = a;

    if (rankv[a] == rankv[b]) 
        rankv[a]++;
}
```

---

# 응용 1: 사이클 판별

무방향 그래프에서 **사이클 발생 여부**를 확인할 때 사용한다.

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int find_parent(int x) {
    if (x == parent[x]) 
        return x;
    return parent[x] = find_parent(parent[x]);
}

bool union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a == b) 
        return true; // 사이클 존재
    parent[b] = a;
    return false;
}

int main() {
    int V, E;
    cin >> V >> E;
    parent.resize(V + 1);
    for (int i = 1; i <= V; ++i) 
        parent[i] = i;

    bool cycle = false;
    for (int i = 0; i < E; ++i) {
        int a, b;
        cin >> a >> b;
        if (union_parent(a, b)) cycle = true;
    }
    cout << (cycle ? "Cycle Detected" : "No Cycle") << "\n";
}
```

---

# 응용 2: Kruskal MST (최소 스패닝 트리)

Union-Find 는 **Kruskal 알고리즘**에서 사이클 판별에 핵심적으로 사용된다.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

vector<int> parent;

int find_parent(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find_parent(parent[x]);
}

bool union_parent(int a, int b) {
    a = find_parent(a);
    b = find_parent(b);
    if (a == b) 
        return false;
    parent[b] = a;
    return true;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end());
    parent.resize(V + 1);
    for (int i = 1; i <= V; ++i) parent[i] = i;

    int total = 0;
    for (auto &e : edges)
        if (union_parent(e.u, e.v))
            total += e.w;

    cout << "MST cost: " << total << "\n";
}
```

---

# 시간 복잡도

| 연산 | 일반 | 최적화 적용 후 |
|------|------|----------------|
| find / union | O(log N) | **O(α(N)) ≈ O(1)** |
| 전체 연산 N번 | O(N log N) | **O(N)** |

> α(N): 아커만(Ackermann) 함수의 역함수. 매우 느리게 증가하므로 거의 상수.

---

# 핵심 요약

| 개념 | 설명 |
|------|------|
| **Find** | 원소의 루트 노드 탐색 |
| **Union** | 두 집합 병합 |
| **Path Compression** | 부모를 루트로 직접 연결 |
| **Union by Rank** | 트리 깊이 최소화 |
| **시간복잡도** | 거의 O(1) 수준 |

---

# 마무리

Union-Find는 단순하면서도 강력한 구조로,  
**그래프 이론**, **집합 관리**, **네트워크 연결성** 등 다양한 분야에서 사용된다.

특히 MST, 그룹화, 사이클 검출 등 **모든 연결성 기반 문제의 핵심 도구**이다.
