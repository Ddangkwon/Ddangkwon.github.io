---
layout : post
title : STL_Priority_Queue
comments : true
categories : 
- CodingTest
tags : [CodingTest, STL, Container]
---

# 개요

**priority_queue** 는 **우선순위 큐(Priority Queue)** 를 구현하는 STL 컨테이너 어댑터이다.  
내부적으로 **heap(힙)** 자료구조를 사용하며, 기본적으로 **최대 힙(Max-Heap)** 형태를 가진다.

**std::priority_queue** 는 **가장 큰 원소(우선순위가 높은 값)** 가 top() 에 위치한다.  
이를 통해 항상 최대 혹은 최소 원소를 빠르게 접근할 수 있다.  

---

# 헤더와 기본 선언

```cpp
#include <queue>
#include <vector>

using namespace std;

int main() {
    priority_queue<int> pq;  // 기본: 최대 힙 (std::less<int>)
    priority_queue<int, vector<int>, greater<int>> minPQ; // 최소 힙
}
```

- 내부 컨테이너로 **std::vector** 가 기본 사용됨  
- 비교 객체(comparator)는 기본적으로 **std::less<T>** → 최대 힙  
- 최소 힙을 만들고 싶다면 **std::greater<T>** 사용  

---

# 주요 특징

- 항상 **가장 우선순위가 높은 값** 을 O(1) 에 top() 으로 조회 가능  
- 삽입(push) / 삭제(pop) 은 O(log n)  
- 임의 접근(random access) 불가능 (heap 구조이기 때문)  
- 내부적으로 **make_heap**, **push_heap**, **pop_heap** 연산 사용  

---

# 멤버 함수 정리

| 함수 | 설명 |
|------|------|
| **push(const T& val)** | 원소 삽입 (O(log n)) |
| **emplace(args...)** | 원소 직접 생성 후 삽입 |
| **pop()** | top 원소 제거 (O(log n)) |
| **top()** | 가장 우선순위 높은 원소 반환 |
| **empty()** | 비어있는지 여부 확인 |
| **size()** | 원소 개수 반환 |

---

# 기본 사용 예제

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    priority_queue<int> pq;  // 최대 힙
    pq.push(10);
    pq.push(5);
    pq.push(20);

    cout << "Top: " << pq.top() << "\n"; // 20

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
    return 0;
}
```

**출력**
```
Top: 20
20 10 5
```

---

# 최소 힙 예제

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> pq; // 최소 힙

    pq.push(10);
    pq.push(5);
    pq.push(20);

    cout << "Top: " << pq.top() << "\n"; // 5

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << "\n";
}
```

**출력**
```
Top: 5
5 10 20
```

---

# 사용자 정의 구조체 예제 (커스텀 우선순위)

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;
};

// 나이 많은 순서대로 정렬
struct Compare {
    bool operator()(const Person& a, const Person& b) const {
        return a.age < b.age;  // 큰 age가 먼저
    }
};

int main() {
    priority_queue<Person, vector<Person>, Compare> pq;

    pq.push({"Alice", 25});
    pq.push({"Bob", 30});
    pq.push({"Charlie", 22});

    while (!pq.empty()) {
        cout << pq.top().name << " (" << pq.top().age << ")\n";
        pq.pop();
    }
}
```

**출력**
```
Bob (30)
Alice (25)
Charlie (22)
```

---

# lambda 를 이용한 커스텀 정렬 (modern C++)

```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int main() {
    auto cmp = [](const pair<string,int>& a, const pair<string,int>& b) {
        return a.second < b.second;  // 점수가 높은 순
    };

    priority_queue<pair<string,int>, vector<pair<string,int>>, decltype(cmp)> pq(cmp);

    pq.push({"A", 90});
    pq.push({"B", 75});
    pq.push({"C", 95});

    while (!pq.empty()) {
        cout << pq.top().first << " : " << pq.top().second << "\n";
        pq.pop();
    }
}
```

**출력**
```
C : 95
A : 90
B : 75
```

---

# emplace 사용 예시

```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Data {
    string name;
    int score;
    Data(string n, int s) : name(n), score(s) {}
    bool operator<(const Data& other) const {
        return score < other.score;  // 높은 점수 우선
    }
};

int main() {
    priority_queue<Data> pq;
    pq.emplace("Alice", 90);
    pq.emplace("Bob", 85);
    pq.emplace("Charlie", 95);

    while (!pq.empty()) {
        cout << pq.top().name << " : " << pq.top().score << "\n";
        pq.pop();
    }
}
```

**출력**
```
Charlie : 95
Alice : 90
Bob : 85
```

---

# 주의 사항

- priority_queue 는 **직접 순회(iterator)** 불가능  
- 내부 데이터 접근은 **top()** 으로만 가능  
- 정렬 기준을 변경하려면 반드시 **생성 시 comparator** 를 지정해야 함  
- 중간 변경, erase, 특정 원소 삭제 기능 없음 (heap 재구성 필요)

---

# 응용 예시

## 1️⃣ K번째 큰 원소 찾기

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {3,2,1,5,6,4};
    int k = 2;
    priority_queue<int, vector<int>, greater<int>> pq; // 최소 힙

    for (int n : nums) {
        pq.push(n);
        if (pq.size() > k) 
            pq.pop();
    }

    cout << k << "번째 큰 수: " << pq.top() << "\n"; // 5
}
```

## Dijkstra 최단경로

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct {
    int to;
    int cost;
} Edge;

struct cmp {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.cost > b.cost;
    }
};


int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> dist(n, 1e9);
    priority_queue<Edge, vector<Edge>, cmp> pq;
    dist[0] = 0;
    pq.push({0, 0}); // to=0, cost=0

    while (!pq.empty()) {
        Edge cur = pq.top();
        pq.pop();

        int u = cur.to;
        int d = cur.cost;
        if (d > dist[u]) continue;

        for (auto next : graph[u]) {
            int v = next.to;
            int w = next.cost;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({v, dist[v]});
            }
        }
    }

    for (int i = 0; i < n; ++i)
        cout << i << ": " << dist[i] << "\n";
}

```

---

# 시간복잡도 표

| 연산 | 복잡도 |
|------|--------|
| push / emplace | O(log n) |
| pop | O(log n) |
| top | O(1) |
| size / empty | O(1) |

---

# 요약

| 구분 | 기본 비교자 | 내부 컨테이너 | 기본 정렬 방향 |
|------|--------------|----------------|----------------|
| **priority_queue** | std::less<T> | std::vector<T> | 최대 힙 |
| **priority_queue (min)** | std::greater<T> | std::vector<T> | 최소 힙 |

---

priority_queue 는 **최대/최소값 관리**, **탐욕 알고리즘**, **Dijkstra, Huffman, Kth 문제** 등  
우선순위 기반 연산에 필수적인 STL 도구이다.


# 예시 문제 

정올 외과 응급실에서는 환자들을 입원시킬 때 환자의 나이와 출혈량을 물어본다.

출혈량이 높을 수록 더 먼저 수술을 받게 되는데, 출혈량이 같다면 고령의 환자를 먼저 수술한다.

 

환자의 입원과 수술 데이터를 실시간으로 처리하는 프로그램을 작성하라.

입원 데이터는 "push Thomas 37 ​120.6" 와 같이 이름, 나이, 출혈량(ml) 순서로 주어지며,

수술 데이터는 "pop"으로 주어진다. 이 경우 환자가 없다면 무시된다.


```cpp
#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct pat_info {
    string name;
    int age;
    float blood;
};

// 우선순위 비교: 출혈량이 높을수록 우선, 같으면 나이 많은 사람이 우선
// 부등호의 방향은 우선순위 방향으로 정한다
// 우선 순위 큐에서는 우선순위를 따지고 a의 우선순위가 b보다 낮으므로 a가 뒤로 가야 한다
// 우선 순위가 높을 수록 top 으로 가야한다. 
// 이는 vector 에서 sort 할 때 compare 함수 할 때와는 다르다. 그 때는 출혈량이 높은(값이 큰) 경우 앞으로 가야하므로 부등호의 방향이 반대여야 한다.

struct compare {
    bool operator()(const pat_info& a, const pat_info& b) {
        int blood_a = a.blood * 10;
        int blood_b = b.blood * 10;

        if (blood_a < blood_b) return true;
        if (blood_a == blood_b && a.age < b.age) return true;

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int Q;
    cin >> Q;

    priority_queue<pat_info, vector<pat_info>, compare> max_heap;

    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "push") {
            pat_info input;
            cin >> input.name >> input.age >> input.blood;
            max_heap.push(input);
        } else if (cmd == "pop") {
            if (!max_heap.empty()) {
                cout << max_heap.top().name << '\n';
                max_heap.pop();
            }
        }
    }

    return 0;
}

```