---
layout : post
title : STL_Priority_Queue
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---
# STL_Priority_Queue

priority_queue(우선순위큐)는 로그시간안에 삽입 및 가장 큰 원소의 추출을 제공하는 컨테이너 어댑터(container adaptor)다.
마찬가지로 queue 라이브러리를 include 헤서 사용한다.
 
priority_queue는 기본적으로 앞서 배운 힙(heap), 그 중 최대힙(max heap)으로 구현이 되어있다.

최소힙(min heap)을 사용하고 싶다면 std::greater<T>를 사용하면 된다.

기본적인 함수로는 아래와 같은 함수들이 있다.

- push(): 원소를 삽입

- pop() : top의 원소를 제거

- top() : top에 있는 원소인 우선순위가 높은 원소를 반환

- empty() : 비어있으면 true, 아니면 false를 반환

- size() : 원소의 수를 반환

## STL_Queue

- size() q의 사이즈(물리적인 저장 용량이 아닌 원소의 개수)를 리턴 

- empty() q의 사이즈가 0인지 아닌지를 확인
 
- front() q에 가장 먼저 들어간 원소를 리턴 

- back() q에 가장 나중에 들어간 원소를 리턴 

- push(val) 

- pop() q에 가장 먼저 들어간 원소를 삭제



priority_queue는 템플릿 클래스이며, 세 가지 매개변수를 가짐

- T: 저장할 데이터의 타입 (예: int)
- Container: 내부적으로 사용할 컨테이너 (기본은 vector<T>)
- Compare: 우선순위를 비교할 기준을 정하는 함수 객체 (기본은 std::less<T> = "큰 값이 먼저" → 최대 힙)

```cpp
template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
```
## 문제 

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