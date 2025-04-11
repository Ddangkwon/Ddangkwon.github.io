---
layout : post
title : STL_Vector
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---

# STL_Vector 

## 1. 개요
vector는 C++ STL(Standard Template Library)의 대표적인 시퀀스 컨테이너로, 동적 배열(dynamic array)을 제공한다. 메모리 크기를 자동으로 조절하면서 데이터를 저장할 수 있으며, 배열처럼 임의 접근(random access)이 가능하다.

---

## 2. 헤더와 선언

```cpp
#include <vector>
using namespace std;

vector<int> v;                // 기본 생성자
vector<int> v2(10);           // 10개의 요소를 0으로 초기화
vector<int> v3(5, 100);       // 5개의 요소를 100으로 초기화
vector<int> v4 = {1, 2, 3};   // 초기화 리스트
```

---

## 3. 주요 멤버 함수

### 3.1 요소 삽입

```cpp
v.push_back(10);        // 마지막에 삽입
v.insert(v.begin(), 5); // 맨 앞에 삽입
```

### 3.2 요소 삭제

```cpp
v.pop_back();               // 마지막 요소 삭제
v.erase(v.begin());         // 첫 번째 요소 삭제
v.erase(v.begin() + 1, v.end()); // 일부 구간 삭제
v.clear();                  // 전체 삭제
```

### 3.3 접근

```cpp
v[i];           // 인덱스 접근 (범위 검사 없음)
v.at(i);        // 인덱스 접근 (범위 검사 있음)
v.front();      // 첫 번째 요소
v.back();       // 마지막 요소
```

---

## 4. 용량 관련 함수

```cpp
v.size();       // 현재 요소 개수
v.capacity();   // 현재 할당된 용량
v.resize(20);   // 크기 변경 (자동 초기화됨)
v.reserve(100); // 용량 미리 확보
v.shrink_to_fit(); // 여유 메모리 반환
```

---

## 5. 반복자(iterator)

```cpp
vector<int>::iterator it = v.begin();
for (it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
}
```

### 범위 기반 for 문

```cpp

for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

for (int x : v) {
    cout << x << " ";
}
```

---

## 6. 복사 및 비교

```cpp
vector<int> a = {1, 2, 3};
vector<int> b = a;       // 복사
bool equal = (a == b);   // 비교
```

---

## 7. 2차원 vector

```cpp
vector<vector<int>> matrix(3, vector<int>(4, 0)); // 3x4 2차원 벡터 0으로 초기화
```

---

## 8. vector와 포인터

```cpp
vector<int*> ptrVec;
int a = 10;
ptrVec.push_back(&a);
```

주의: 포인터를 사용한 vector는 메모리 관리를 수동으로 해야 함.

---

## 9. vector의 내부 동작

- **vector**는 동적 배열을 사용한다
- 용량(capacity)이 부족할 때는 더 큰 메모리를 할당하고 기존 데이터를 복사한다
- **push_back** 시 capacity가 늘어날 수 있으며, 복사 비용이 발생한다
- 메모리 증가 방식은 구현체마다 다르지만 일반적으로 1.5~2배씩 증가함

---

## 10. vector 사용 시 주의사항

- 중간 삽입/삭제는 비효율적이다 (O(n))
- 메모리 할당/복사 오버헤드 고려 필요
- iterator는 재할당 후 무효화될 수 있다

---

## 11. 정리

- vector는 임의 접근(random access)이 가능하고 크기 조절이 자동인 배열
- 삽입/삭제는 끝에서 할 때 가장 효율적
- 다양한 STL 알고리즘과 함께 사용할 수 있는 범용 컨테이너이다

