---
layout : post
title : LCA(Lowest Common Ancestor)
comments : true
categories :
- CodingTest
tags : [CodingTest, Algorithm]
---

# LCA 알고리즘 정리

## LCA란?

**LCA(Lowest Common Ancestor)** 는 트리에서 두 노드가 주어졌을 때, 두 노드의 공통 조상 중 가장 깊이가 깊은 노드를 의미한다.

즉, 두 노드에서 부모 방향으로 올라갔을 때 처음으로 만나는 공통 조상이 LCA이다.

예를 들어 다음과 같은 트리가 있다고 하자.

```
          1
        /   \
       2     3
      / \   / \
     4   5 6   7
```

여기서 LCA는 다음과 같다.

| 노드 u | 노드 v | LCA |
|---:|---:|---:|
| 4 | 5 | 2 |
| 4 | 6 | 1 |
| 6 | 7 | 3 |
| 2 | 4 | 2 |

노드 4와 5의 공통 조상은 2, 1이다.
그중 가장 아래쪽에 있는 조상은 2이므로 LCA는 2이다.

---

# LCA가 필요한 경우

LCA는 트리에서 두 노드 사이의 관계를 빠르게 계산할 때 자주 사용한다.

대표적인 사용 예시는 다음과 같다.

| 사용 상황 | 설명 |
|---|---|
| 두 노드 사이 거리 계산 | depth[u] + depth[v] - 2 × depth[lca] |
| 트리 경로 질의 | 두 노드 사이 경로의 공통 조상 기준 분할 |
| 최소 공통 조상 탐색 | 계층 구조에서 공통 부모 탐색 |
| 네트워크 라우팅 | 트리형 네트워크에서 공통 경유 노드 탐색 |
| 조직도 분석 | 두 구성원의 가장 가까운 공통 상급자 탐색 |
| 알고리즘 문제 | 트리 DP, 경로 쿼리, 오프라인 쿼리 등 |

---

# 기본 아이디어

LCA를 구하는 기본 아이디어는 다음과 같다.

1. 두 노드의 depth를 맞춘다.
2. 두 노드가 같아질 때까지 동시에 부모 방향으로 올린다.
3. 처음으로 같아지는 노드가 LCA이다.

하지만 단순히 한 칸씩 올리면 최악의 경우 O(N)이 걸릴 수 있다.

그래서 여러 개의 쿼리를 빠르게 처리하려면 전처리를 사용한다.

대표적인 LCA 구현 방식은 다음과 같다.

| 방식 | 전처리 | 쿼리 | 특징 |
|---|---:|---:|---|
| 단순 부모 이동 | O(N) | O(N) | 구현이 가장 쉽지만 느림 |
| Sparse Table, Binary Lifting | O(N log N) | O(log N) | 가장 대표적인 방식 |
| Sqrt Decomposition | O(N) 또는 O(N sqrt N) | O(sqrt N) | 구현이 비교적 직관적 |
| Euler Tour + RMQ | O(N log N) | O(1) 또는 O(log N) | 매우 빠르지만 구현량이 많음 |
| Tarjan Offline LCA | O((N + Q) α(N)) | Offline 전체 처리 | 모든 쿼리를 미리 알고 있을 때 유용 |

---

# 1. 단순 부모 이동 방식

## 개념

각 노드의 parent와 depth만 저장해두고, 두 노드의 depth를 맞춘 뒤 하나씩 부모로 올리는 방식이다.

## 동작 순서

1. DFS 또는 BFS로 각 노드의 parent와 depth를 구한다.
2. 두 노드 u, v 중 depth가 더 깊은 노드를 위로 올린다.
3. depth가 같아지면 u와 v를 동시에 parent 방향으로 올린다.
4. u와 v가 같아지면 그 노드가 LCA이다.

## 장점

| 장점 | 설명 |
|---|---|
| 구현이 쉽다 | parent와 depth만 있으면 된다 |
| 이해가 쉽다 | LCA의 기본 원리를 그대로 구현한다 |
| 메모리 사용량이 작다 | 추가 테이블이 거의 필요 없다 |

## 단점

| 단점 | 설명 |
|---|---|
| 쿼리가 느리다 | 최악의 경우 루트까지 올라가야 한다 |
| 쿼리 수가 많으면 부적합하다 | Q가 크면 시간 초과가 발생하기 쉽다 |
| 깊은 트리에 약하다 | 일자형 트리에서 성능이 나쁘다 |

## 시간 복잡도

| 항목 | 복잡도 |
|---|---:|
| 전처리 | O(N) |
| 쿼리 | O(N) |
| 메모리 | O(N) |

---

# 2. Sparse Table 방식, Binary Lifting

## 개념

Sparse Table 방식은 각 노드의 2의 거듭제곱 번째 조상을 미리 저장하는 방식이다.

LCA에서 이 방식은 보통 **Binary Lifting**이라고 부른다.

예를 들어 다음과 같은 정보를 저장한다.

| 테이블 | 의미 |
|---|---|
| parent[k][x] | x번 노드의 2^k 번째 조상 |

예시는 다음과 같다.

| 값 | 의미 |
|---|---|
| parent[0][x] | x의 1번째 부모 |
| parent[1][x] | x의 2번째 조상 |
| parent[2][x] | x의 4번째 조상 |
| parent[3][x] | x의 8번째 조상 |

즉, 한 칸씩 올라가는 대신 1, 2, 4, 8, 16칸씩 점프할 수 있게 만든다.

---

## 왜 Sparse Table이라고 부르는가?

Sparse Table은 보통 정적 배열에서 구간 최솟값, 최댓값, GCD(Greatest Common Divisor) 등을 빠르게 구하기 위해 사용하는 전처리 테이블을 의미한다.

LCA에서 사용하는 parent 테이블도 2의 거듭제곱 단위로 조상을 저장한다는 점에서 Sparse Table 구조와 유사하다.

그래서 LCA에서는 다음과 같은 표현을 함께 사용한다.

| 표현 | 의미 |
|---|---|
| Sparse Table LCA | 2^k 조상 테이블 기반 LCA |
| Binary Lifting | 이진수 분해를 이용해 노드를 점프시키는 방식 |
| parent table | 각 노드의 2^k 조상을 저장한 테이블 |

---

## 핵심 아이디어

어떤 노드 x를 13칸 위로 올리고 싶다고 하자.

13은 이진수로 다음과 같이 표현된다.

13 = 8 + 4 + 1

따라서 한 칸씩 13번 이동하지 않고 다음처럼 이동할 수 있다.

1. 8번째 조상으로 이동
2. 4번째 조상으로 이동
3. 1번째 조상으로 이동

즉, 깊이 차이를 이진수로 분해해서 빠르게 위로 올린다.

---

## Sparse Table 전처리

먼저 DFS 또는 BFS로 각 노드의 depth와 parent[0][x]를 구한다.

그다음 다음 점화식으로 테이블을 채운다.

```
parent[k][x] = parent[k - 1][parent[k - 1][x]]
```

이 식의 의미는 다음과 같다.

x의 2^k 번째 조상은
x의 2^(k-1) 번째 조상의 2^(k-1) 번째 조상이다.

예를 들어 x의 8번째 조상은 다음과 같다.

x의 4번째 조상으로 이동한 뒤, 그 노드의 4번째 조상으로 다시 이동한다.

---

## LCA 쿼리 과정

두 노드 u, v의 LCA를 구하는 과정은 다음과 같다.

1. depth가 더 깊은 노드를 위로 올려서 두 노드의 depth를 맞춘다.
2. 두 노드가 같아지면 그 노드가 LCA이다.
3. 같지 않으면 큰 k부터 작은 k까지 확인하면서 parent[k][u]와 parent[k][v]가 다를 때만 동시에 올린다.
4. 마지막에 u와 v는 LCA 바로 아래 자식 노드가 된다.
5. parent[0][u]가 LCA이다.

---

## C++ 구현 예제

아래 코드는 Sparse Table, Binary Lifting 방식으로 LCA를 구하는 예제이다.
```cpp
    #include <iostream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    const int MAXN = 100001;
    const int LOG = 17;

    int N, Q;
    vector<int> graph[MAXN];
    int depth[MAXN];
    int parent[LOG + 1][MAXN];

    void dfs(int cur, int par)
    {
        parent[0][cur] = par;
        depth[cur] = depth[par] + 1;

        for (int next : graph[cur]) {
            if (next == par) continue;
            dfs(next, cur);
        }
    }

    void build_sparse_table()
    {
        for (int k = 1; k <= LOG; k++) {
            for (int node = 1; node <= N; node++) {
                int mid = parent[k - 1][node];
                parent[k][node] = parent[k - 1][mid];
            }
        }
    }

    int lca(int u, int v)
    {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }

        int diff = depth[u] - depth[v];

        for (int k = LOG; k >= 0; k--) {
            if (diff & (1 << k)) {
                u = parent[k][u];
            }
        }

        if (u == v) {
            return u;
        }

        for (int k = LOG; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }

        return parent[0][u];
    }

    int main()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        cin >> N;

        for (int i = 0; i < N - 1; i++) {
            int a, b;
            cin >> a >> b;

            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        depth[0] = 0;
        dfs(1, 0);
        build_sparse_table();

        cin >> Q;

        while (Q--) {
            int u, v;
            cin >> u >> v;
            cout << lca(u, v) << '\n';
        }

        return 0;
    }
```

---

## 예제 입력
```
    9
    1 2
    1 3
    2 4
    2 5
    3 6
    3 7
    5 8
    5 9
    5
    4 5
    4 6
    8 9
    8 6
    2 9
```
## 예제 트리

```
              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9
```

## 예제 출력

```
    2
    1
    5
    1
    2
```

## 예제 해석

| Query | 설명 | LCA |
|---|---|---:|
| 4, 5 | 4와 5의 가장 가까운 공통 조상 | 2 |
| 4, 6 | 4는 2쪽, 6은 3쪽 subtree | 1 |
| 8, 9 | 둘 다 5의 자식 | 5 |
| 8, 6 | 서로 다른 큰 subtree | 1 |
| 2, 9 | 2가 9의 조상 | 2 |

---

## Sparse Table 방식의 장점

| 장점 | 설명 |
|---|---|
| 쿼리가 빠르다 | O(log N)에 LCA를 구할 수 있다 |
| 여러 쿼리에 적합하다 | Q가 큰 문제에서 효율적이다 |
| 구현 패턴이 표준적이다 | 많은 알고리즘 문제에서 가장 많이 사용된다 |
| 거리 계산과 결합하기 쉽다 | LCA를 이용해 두 노드 거리도 빠르게 구할 수 있다 |
| 정적 트리에 적합하다 | 간선이 바뀌지 않는 트리에서 안정적이다 |

## Sparse Table 방식의 단점

| 단점 | 설명 |
|---|---|
| 전처리가 필요하다 | parent 테이블을 미리 만들어야 한다 |
| 메모리를 더 사용한다 | O(N log N) 크기의 테이블이 필요하다 |
| 구현 실수가 잦다 | depth 맞추기, k 범위, parent[0] 처리에서 실수하기 쉽다 |
| 동적 트리에는 부적합하다 | 간선이 계속 바뀌면 테이블 갱신이 어렵다 |

## 시간 복잡도

| 항목 | 복잡도 |
|---|---:|
| 전처리 | O(N log N) |
| 쿼리 | O(log N) |
| 메모리 | O(N log N) |

---

# 3. Sqrt Decomposition 방식

## 개념

Sqrt Decomposition 방식은 트리의 depth를 block 단위로 나누고, 각 노드가 속한 block의 위쪽 대표 조상을 저장해두는 방식이다.

일반적으로 block size를 sqrt(N) 정도로 둔다.

각 노드마다 다음 정보를 저장한다.

| 정보 | 의미 |
|---|---|
| parent[x] | x의 바로 위 부모 |
| depth[x] | x의 깊이 |
| jump[x] | x가 속한 block의 위쪽 대표 조상 |

여기서 jump[x]는 x에서 여러 칸 위로 빠르게 이동하기 위한 포인터이다.

---

## 핵심 아이디어

단순 부모 이동은 한 칸씩 올라가기 때문에 느리다.

Sqrt Decomposition은 한 칸씩만 올라가지 않고, block 단위로 크게 점프할 수 있게 한다.

즉, 다음 두 이동을 섞어서 사용한다.

| 이동 방식 | 설명 |
|---|---|
| jump 이동 | block 단위로 크게 이동 |
| parent 이동 | block 안에서는 한 칸씩 이동 |

그래서 전체 쿼리를 O(sqrt N) 정도로 줄일 수 있다.

---

## jump 배열 정의 방법

root를 1번 노드라고 하자.

block size를 B라고 할 때, 다음처럼 jump를 정의할 수 있다.

1. root의 jump는 root이다.
2. depth[x]가 B의 배수이면 jump[x]는 parent[x]이다.
3. 그 외에는 jump[x]는 jump[parent[x]]이다.

즉, 같은 block 안에 있는 노드들은 같은 block의 위쪽 경계 노드를 바라본다.

이 방식은 트리에서 위쪽으로 block 단위 점프를 하기 위한 구조이다.

---

## 예시

block size가 3이라고 하자.

다음과 같은 일자형 트리가 있다.
```
    1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9
```
depth가 다음과 같다고 하자.

| Node | Depth |
|---:|---:|
| 1 | 0 |
| 2 | 1 |
| 3 | 2 |
| 4 | 3 |
| 5 | 4 |
| 6 | 5 |
| 7 | 6 |
| 8 | 7 |
| 9 | 8 |

block size가 3이면 depth 구간은 다음처럼 나눌 수 있다.

| Block | Depth 범위 |
|---|---|
| Block 0 | 0, 1, 2 |
| Block 1 | 3, 4, 5 |
| Block 2 | 6, 7, 8 |

노드 9에서 jump를 사용하면 block 단위로 6 또는 4 근처까지 빠르게 올라갈 수 있다.
이후 같은 block 안에서는 parent로 한 칸씩 움직인다.

---

## LCA 쿼리 과정

Sqrt Decomposition 방식의 LCA 과정은 다음과 같다.

1. 두 노드 u, v의 jump가 다르면 depth가 더 깊은 jump를 가진 노드를 jump 방향으로 올린다.
2. 두 노드의 jump가 같아질 때까지 반복한다.
3. jump가 같아지면 같은 block 안에 들어온 것이다.
4. 이제 parent를 한 칸씩 올려서 u와 v가 같아질 때까지 이동한다.
5. 같아진 노드가 LCA이다.

---

## C++ 구현 예제

아래 코드는 Sqrt Decomposition 방식으로 LCA를 구하는 예제이다.
```cpp
    #include <iostream>
    #include <vector>
    #include <cmath>
    #include <algorithm>

    using namespace std;

    const int MAXN = 100001;

    int N, Q;
    int block_size;
    vector<int> graph[MAXN];

    int parent_node[MAXN];
    int depth_node[MAXN];
    int jump[MAXN];

    void dfs(int cur, int par)
    {
        parent_node[cur] = par;
        depth_node[cur] = depth_node[par] + 1;

        if (cur == 1) {
            jump[cur] = 1;
        }
        else if (depth_node[cur] % block_size == 0) {
            jump[cur] = par;
        }
        else {
            jump[cur] = jump[par];
        }

        for (int next : graph[cur]) {
            if (next == par) continue;
            dfs(next, cur);
        }
    }

    int lca_sqrt(int u, int v)
    {
        while (jump[u] != jump[v]) {
            if (depth_node[jump[u]] < depth_node[jump[v]]) {
                v = jump[v];
            }
            else {
                u = jump[u];
            }
        }

        while (u != v) {
            if (depth_node[u] < depth_node[v]) {
                v = parent_node[v];
            }
            else {
                u = parent_node[u];
            }
        }

        return u;
    }

    int main()
    {
        ios::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        cin >> N;

        block_size = sqrt(N) + 1;

        for (int i = 0; i < N - 1; i++) {
            int a, b;
            cin >> a >> b;

            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        depth_node[0] = -1;
        dfs(1, 0);

        cin >> Q;

        while (Q--) {
            int u, v;
            cin >> u >> v;
            cout << lca_sqrt(u, v) << '\n';
        }

        return 0;
    }
```

---

## 예제 입력

```
    9
    1 2
    1 3
    2 4
    2 5
    3 6
    3 7
    5 8
    5 9
    5
    4 5
    4 6
    8 9
    8 6
    2 9

## 예제 출력

    2
    1
    5
    1
    2
```

---

## Sqrt Decomposition 방식의 장점

| 장점 | 설명 |
|---|---|
| Binary Lifting보다 개념이 단순할 수 있다 | 큰 점프와 한 칸 이동만 이해하면 된다 |
| 메모리 사용량이 작다 | O(N) 배열 몇 개만 사용한다 |
| 전처리가 비교적 가볍다 | DFS 한 번으로 jump를 만들 수 있다 |
| 단순 부모 이동보다 빠르다 | 최악 O(N) 이동을 O(sqrt N) 수준으로 줄일 수 있다 |

## Sqrt Decomposition 방식의 단점

| 단점 | 설명 |
|---|---|
| Binary Lifting보다 쿼리가 느리다 | O(sqrt N)이므로 O(log N)보다 느린 경우가 많다 |
| block 정의에 따라 구현이 헷갈릴 수 있다 | jump 설정 방식에 주의해야 한다 |
| 표준 풀이로는 덜 자주 사용된다 | 많은 문제에서는 Binary Lifting이 더 일반적이다 |
| 매우 큰 Q에는 불리할 수 있다 | 쿼리 수가 많으면 O(log N) 방식이 더 유리하다 |

## 시간 복잡도

| 항목 | 복잡도 |
|---|---:|
| 전처리 | O(N) |
| 쿼리 | O(sqrt N) |
| 메모리 | O(N) |

---

# Sparse Table 방식과 Sqrt Decomposition 방식 비교

| 항목 | Sparse Table, Binary Lifting | Sqrt Decomposition |
|---|---|---|
| 핵심 아이디어 | 2^k 조상을 저장해 이진 점프 | block 단위 대표 조상으로 점프 |
| 전처리 | O(N log N) | O(N) |
| 쿼리 | O(log N) | O(sqrt N) |
| 메모리 | O(N log N) | O(N) |
| 구현 난이도 | 중간 | 중간 이하 |
| 실무 코딩테스트 빈도 | 매우 높음 | 상대적으로 낮음 |
| Q가 큰 경우 | 유리함 | 상대적으로 불리함 |
| 메모리가 제한적인 경우 | 부담될 수 있음 | 유리함 |
| 추천 상황 | 대부분의 LCA 문제 | 메모리 절약, 개념 학습, 간단 구현 |

---

# 두 노드 사이 거리 계산

LCA를 구할 수 있으면 두 노드 사이의 거리도 쉽게 구할 수 있다.

공식은 다음과 같다.

```
dist(u, v) = depth[u] + depth[v] - 2 \times depth[LCA(u, v)]
```

예를 들어 다음 트리에서 8과 6의 거리를 구한다고 하자.

              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9

LCA(8, 6)은 1이다.

| 노드 | Depth |
|---:|---:|
| 8 | 3 |
| 6 | 2 |
| 1 | 0 |

따라서

```
dist(8, 6) = 3 + 2 - 2 \times 0 = 5
```

실제 경로는 다음과 같다.

```
    8 → 5 → 2 → 1 → 3 → 6
```

간선 수는 5개이다.

---

# 어떤 방식을 선택해야 할까?

## 쿼리 수가 많으면 Sparse Table 방식

N과 Q가 모두 큰 경우에는 Sparse Table, Binary Lifting 방식이 가장 안정적이다.

예를 들어 다음 조건에서는 Sparse Table 방식이 적합하다.

| 조건 | 추천 방식 |
|---|---|
| N이 100,000 이상 | Sparse Table |
| Q가 100,000 이상 | Sparse Table |
| 시간 제한이 빡빡함 | Sparse Table |
| 거리 계산도 같이 필요함 | Sparse Table |

## 메모리를 줄이고 싶으면 Sqrt Decomposition 방식

메모리 제한이 엄격하거나, 구현을 조금 더 단순하게 가져가고 싶다면 Sqrt Decomposition 방식도 사용할 수 있다.

| 조건 | 추천 방식 |
|---|---|
| 메모리 제한이 매우 작음 | Sqrt Decomposition |
| Q가 아주 크지는 않음 | Sqrt Decomposition |
| LCA 기본 원리 학습 목적 | Sqrt Decomposition |
| O(N log N) 메모리가 부담됨 | Sqrt Decomposition |

---

# 연습문제 1

다음 트리에서 LCA(8, 9)를 구하여라.

              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9

## 정답

LCA(8, 9) = 5

## 풀이

8의 조상은 8, 5, 2, 1이다.
9의 조상은 9, 5, 2, 1이다.

가장 가까운 공통 조상은 5이다.

---

# 연습문제 2

다음 트리에서 LCA(4, 7)를 구하여라.

              1
            /   \
           2     3
          / \   / \
         4   5 6   7
            / \
           8   9

## 정답

LCA(4, 7) = 1

## 풀이

4는 2번 subtree에 있고, 7은 3번 subtree에 있다.
두 subtree가 만나는 가장 가까운 공통 조상은 root인 1이다.

---

# 연습문제 3

Sparse Table 방식에서 parent[3][x]는 무엇을 의미하는가?

1. x의 3번째 부모
2. x의 6번째 조상
3. x의 8번째 조상
4. x의 root

## 정답

3번

## 풀이

parent[k][x]는 x의 2^k 번째 조상이다.
따라서 parent[3][x]는 x의 2^3 번째 조상, 즉 8번째 조상이다.

---

# 연습문제 4

N = 100,000, Q = 100,000인 LCA 문제에서 일반적으로 가장 추천되는 방식은?

1. 단순 부모 이동
2. Sparse Table, Binary Lifting
3. 매 쿼리마다 DFS
4. 완전 탐색

## 정답

2번

## 풀이

N과 Q가 모두 크기 때문에 쿼리마다 O(N)이 걸리는 방식은 시간 초과 가능성이 높다.
Sparse Table 방식은 O(N log N) 전처리 이후 각 쿼리를 O(log N)에 처리할 수 있어 적합하다.

---

# 핵심 요약

| 개념 | 핵심 |
|---|---|
| LCA | 두 노드의 가장 가까운 공통 조상 |
| 단순 방식 | parent를 한 칸씩 올라가는 방식 |
| Sparse Table | 2^k 번째 조상을 저장해 빠르게 점프 |
| Binary Lifting | 깊이 차이를 이진수로 분해해서 이동 |
| Sqrt Decomposition | depth를 block으로 나눠 대표 조상으로 점프 |
| 거리 계산 | depth[u] + depth[v] - 2 × depth[lca] |

결론적으로 대부분의 코딩테스트 LCA 문제에서는 **Sparse Table, Binary Lifting** 방식을 우선 고려하는 것이 좋다.
다만 LCA 원리 학습이나 메모리 절약 목적이라면 **Sqrt Decomposition** 방식도 좋은 대안이다.
