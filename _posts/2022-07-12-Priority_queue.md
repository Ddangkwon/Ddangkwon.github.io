---
layout : post
title : 우선순위 큐(Priority_queue)
comments : true
categories : 
- Algorithm
tags : [Algorithm]
---
# 우선순위 큐(Priority_queue)

## 우선순위 큐란?
큐의 모든 원소 중에서 가장 큰 값이 Top 위치에 위치하도록 우선순위가 크도록 설계되어 있는 큐를 말한다.
내부적으로는 Heap 자료구조를 사용한다.


## C++에서 우선순위 큐의 메소드

### 추가 및 삭제
push() : 우선순위 큐에 원소를 추가한다
pop()  : 우선순위 큐에서 Top의 원소를 제거한다

### 서칭
top() :  우선순위 큐에서 Top에 있는 원소 즉 우선순위가 높은 원소를 반환한다

### Etc.
empty() : 우선순위 큐가 비어있으면 True를 반환하고 그렇지 않으면 False를 반환한다
size() : 우선순위 큐에 포함되어 있는 원소의 수를 반환한다


## 선언

priority_queue<자료형, Container, 비교함수> 변수명

ex) 오름차순으로 정렬되는 우선순위 큐
```c
priority_queue<int , vector<int>, greater<int>> pq;
```