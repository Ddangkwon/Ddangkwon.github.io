---
layout : post
title : C++_Iterator_Range_Base_For_Loop
comments : true
categories : 
- CodingTest
tags : [CodingTest, C++]
---

# C++_Iterator_Range_Base_For_Loop

++11에서 도입된 **Range-based for loop** 은 컨테이너(STL Container)나 배열(Array)의 모든 요소를 간결하게 순회할 수 있는 구문이다.  
이 문법은 반복자의 begin(), end() 함수를 내부적으로 호출하여, **기존 for문을 자동으로 단축**한 형태로 동작한다.

---

## 1. 사전개념 (C++ Iterator)

C++의 **Iterator(반복자)** 는 컨테이너(Container) 내부의 원소를 순회(Traverse)하기 위한 객체이다.  
즉, 배열의 인덱스처럼 작동하지만, 모든 STL 컨테이너(vector, list, map 등)에서 **통일된 방식으로** 동작한다.


Iterator는 컨테이너 내부 요소를 가리키는 **포인터(Pointer)와 유사한 객체**이다.  
하지만 컨테이너의 내부 구조를 몰라도 접근할 수 있도록 **일종의 추상화 계층(Abstract Layer)** 역할을 한다.

**즉,**
- 배열의 인덱스 접근과 같은 기능을 일반화한 것  
- 컨테이너마다 내부 구조(list, tree, hash)가 달라도 동일한 인터페이스로 접근 가능


iterator는 컨테이너 내부를 직접 가리키는 **포인터나 구조체 형태의 객체**다.

**예: vector의 iterator 구조(개념적)**

```
┌──────────────┐
│ vector<int>  │
│ [10][20][30] │
└──────────────┘
     ↑
     └── iterator(it)
```

---

### 기본 문법

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {10, 20, 30, 40, 50};
    vector<int>::iterator it;

    for (it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
}
```

**출력 결과**

```
10 20 30 40 50
```

---

### 설명
| 코드 | 의미 |
|------|------|
| v.begin() | 컨테이너의 첫 번째 원소를 가리키는 iterator 반환 |
| v.end() | 마지막 원소 **다음 위치** 를 가리키는 iterator 반환 |
| *it | iterator가 가리키는 원소의 실제 값 참조 |
| ++it | 다음 원소로 이동 (전위 증가 연산자) |

---

### Iterator의 장점

| 항목 | 설명 |
|------|------|
| **컨테이너 독립성** | 배열, vector, list, set 등 어떤 컨테이너든 동일한 접근 방식 |
| **포인터 유사성** | *, ++, --, -> 연산자 사용 가능 |
| **일관된 인터페이스** | 알고리즘(sort, find, copy 등)에서 범용적으로 사용 가능 |
| **추상화 유지** | 내부 자료구조(연결리스트, 트리 등)를 몰라도 접근 가능 |

---

### Iterator의 주요 연산자

| 연산자 | 의미 | 예시 |
|--------|------|------|
| *it | iterator가 가리키는 원소의 값 | cout << *it; |
| it-> | 구조체나 클래스의 멤버 접근 | it->member |
| ++it | 다음 원소로 이동 (전위 증가) | ++it |
| --it | 이전 원소로 이동 (양방향 컨테이너만) | --it |
| it1 == it2 | 동일 위치 비교 | if (it == v.end()) |
| it + n, it - n | n만큼 이동 (Random Access 지원 컨테이너만) | v.begin() + 3 |

---


## 2. 예시

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5};

    // (1) 값 복사 방식
    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;

    // (2) 참조 방식
    for (auto &x : v) {
        x *= 2;  // 원본 데이터 수정
    }

    // (3) const 참조 방식
    for (const auto &x : v) {
        cout << x << " ";
    }
}

```


**출력 결과**

```
1 2 3 4 5
2 4 6 8 10
```

---

## 3. 참조 & const의 차이

| 형태 | 의미 | 원본 수정 가능 여부 |
|------|------|------------------|
| auto x | 복사 | 불가능 |
| auto &x | 참조 | 가능 |
| const auto &x | 읽기 전용 참조 | 불가능 |

**auto &** 또는 **const auto &** 를 사용하면 불필요한 복사를 방지하고 성능을 향상시킬 수 있다.

---

## 4. 최종 요약

| 항목 | range-based for | 일반 for |
|------|------------------|-----------|
| 가독성 | 매우 높음 | 낮음 |
| 코드 길이 | 짧음 | 김 |
| 성능 (참조) | 동일 | 동일 |
| 복사 비용 | auto x 시 발생 | 없음 |
| 인덱스 접근 | 불가능 | 가능 |
| iterator 제어 | 불가능 | 가능 |
| STL 호환성 | 높음 | 높음 |

---

## 5. 권장 사용 패턴

| 목적 | 추천 구문 |
|------|------------|
| 단순 출력 | for (auto x : v) |
| 원본 수정 | for (auto &x : v) |
| 읽기 전용 | for (const auto &x : v) |
| 인덱스 필요 | 일반 for문 사용 |

