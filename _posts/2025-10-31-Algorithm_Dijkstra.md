---
layout : post
title : Algorithm_Dijkstra
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Dijkstra

# 다익스트라 알고리즘 (Dijkstra Algorithm)

**다익스트라 알고리즘(Dijkstra Algorithm)** 은 **하나의 시작점(Source)** 으로부터 다른 모든 정점까지의 **최단 거리(Shortest Path)** 를 구하는 알고리즘이다.  
단, **간선의 가중치(Weight)** 가 음수이면 사용할 수 없다.

---

## 1. 핵심 개념

1. 시작 노드의 거리를 0으로 두고, 나머지 노드의 거리를 무한(INF)으로 초기화한다.
2. **가장 짧은 거리의 노드**를 선택한다.
3. 그 노드와 연결된 간선을 확인하여 **더 짧은 경로를 발견하면 갱신(Relaxation)** 한다.
4. 모든 노드를 처리할 때까지 반복한다.

---

## 2. 자료구조 구성

| 역할 | 자료형 | 설명 |
|------|---------|------|
| 그래프 | `vector<vector<pair<int,int>>>` | 인접 리스트 (to, weight) |
| 거리 배열 | `vector<int>` | 시작점으로부터의 최단 거리 저장 |
| 우선순위 큐 | `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>` | 최소 거리 노드를 빠르게 탐색 |

---

## 3. 시간 복잡도

| 그래프 표현 | 복잡도 |
|--------------|----------|
| 인접 행렬 | O(V²) |
| 인접 리스트 + Min-Heap | **O((V + E) log V)** |

---

## 4. C++ 기본 구현 코드

```cpp
#include <iostream>
using namespace std;

struct Edge {
    int to; // 정점
    int cost; // 간선 가중치 (큐에서 사용할 때는 누적 가중치가 된다)
};

// 우선순위 큐 비교자 (Min-Heap)
struct cmp {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.cost > b.cost; // cost가 작은 Edge가 더 높은 우선순위
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m; // 정점, 간선 개수
    
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // 무방향 그래프 예시
    }

    const int INF = 1e9;
    vector<int> dist(n, INF);
    priority_queue<Edge, vector<Edge>, cmp> pq; // Edge 구조체 기반 큐

    int start = 0;
    dist[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        Edge cur = pq.top();
        pq.pop();
        // 현재 가중치가 작은 경우만 dist 에 업데이트 할 수 있도록 함
        if (cur.cost > dist[cur.to]) 
            continue;

        for (auto &next : graph[cur.to]) {
            int newCost = cur.cost + next.cost;
            if (newCost < dist[next.to]) {
                dist[next.to] = newCost;
                pq.push({next.to, newCost});
            }
        }
    }

    cout << "최단 거리 결과:\n";
    for (int i = 0; i < n; ++i)
        cout << i << " : " << dist[i] << "\n";

    return 0;
}

```

---

## 5. 구현 포인트 정리

| 요소 | 설명 |
|------|------|
| **priority_queue** | 가장 짧은 거리 노드를 효율적으로 선택 |
| **비교자 cmp** | Min-Heap 형태로 동작하도록 변경 |
| **Relaxation** | 더 짧은 경로를 발견하면 거리 갱신 |
| **visited 불필요** | dist 값으로 방문 여부 판별 가능 |
| **무방향 그래프** | 간선을 양쪽으로 추가 |

---

## 6. 시각적 이해

```
Start(0)
 ├──▶ (1, 2)
 ├──▶ (2, 5)
 └──▶ (3, 9)

pq: [ (0,0) ]
→ (0,0) pop → (1,2), (2,5), (3,9) push
→ (1,2) pop → Relax 주변 노드
→ 계속 반복하며 dist[] 갱신
```

---

## 7. 확장 응용

- **다중 시작점 Dijkstra**: 여러 source를 모두 pq에 넣고 시작
- **경로 복원(Path Tracking)**: `prev[]` 배열로 경로 추적
- **SPFA / Bellman-Ford**: 음수 가중치가 있을 때 대체 알고리즘

---

## 8. 결론

**다익스트라 알고리즘**은 **Greedy + Priority Queue** 조합으로,  
최단 경로를 효율적으로 찾는 대표적인 알고리즘이다.  
C++에서는 `priority_queue`를 Min-Heap으로 바꾸기 위해 **Functor** 또는 **greater<>** 비교자를 사용하는 것이 핵심이다.

