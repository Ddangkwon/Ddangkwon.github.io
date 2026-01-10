---
layout : post
title : Algorithm_Floyd Warshall
comments : true
categories :
- CodingTest
tags : [CodingTest, Floyd Warshall]
---

# Algorithm_Floyd Warshall


## 1. 개요

**플루이드 와샬(Floyd–Warshall) 알고리즘**은
그래프에서 **모든 정점 쌍(All-Pairs)** 사이의 **최단 거리**를 구하는 알고리즘이다.

- 모든 정점 → 모든 정점
- 음수 가중치 허용
- 음수 사이클 탐지 가능
- 동적 계획법(DP, Dynamic Programming) 기반

---

## 2. 언제 사용하는가

다음 조건일 때 적합하다.

- 정점 개수 N이 작을 때 (보통 N ≤ 400)
- 모든 쌍 최단 거리가 필요할 때
- 그래프가 조밀(Dense)할 때
- 음수 간선이 존재할 수 있을 때

다익스트라(Dijkstra)는 단일 출발점(Single Source)에 적합하고,
플루이드 와샬은 전역 최단 경로 문제에 적합하다.

---

## 3. 핵심 아이디어

정점 k를 **중간 경유지**로 사용할 수 있는지 여부를 기준으로
최단 거리를 점진적으로 갱신한다.

i → j 최단 경로는

- 기존 i → j
- i → k → j

중 더 짧은 것을 선택한다.

---

## 4. 점화식

```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

k를 1부터 N까지 확장하며 적용한다.

---

## 5. 알고리즘 구조

3중 반복문 구조

- k : 경유 정점
- i : 출발 정점
- j : 도착 정점

반드시 k → i → j 순서를 유지해야 한다.

---

## 6. 시간 / 공간 복잡도

- 시간 복잡도: O(N³)
- 공간 복잡도: O(N²)

---

## 7. 기본 구현 (C++)

```cpp
#include <iostream>
#include <climits>
using namespace std;

#define INF 1000000000
#define MAXN 401

int dist[MAXN][MAXN];
int N, M;

int main() {
    cin >> N >> M;

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }

    for(int i = 0; i < M; i++){
        int a, b, c;
        cin >> a >> b >> c;
        dist[a][b] = min(dist[a][b], c);
    }

    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return 0;
}
```

---

## 8. 음수 사이클 탐지

- dist[i][i] < 0 인 정점이 존재하면
- 음수 사이클이 존재한다.

---

## 9. 요약

- 모든 쌍 최단 경로 알고리즘
- O(N³) 복잡도
- 음수 간선, 음수 사이클 처리 가능
- 정점 수가 작을 때 매우 강력
