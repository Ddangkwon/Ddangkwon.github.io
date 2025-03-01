---
layout : post
title : union 의 word alignment
comments : true
categories : 
- C
tags : [C]
---


# union 의 word alignment

CPU 의 처리 단위(한 번에 처리 가능한 데이터의 크기) 로 정의된 변수는 워드 경계에 배치된다. 따라서 union을 사용하여 배열의 선두를 강제적으로 워드 경계 어드레스에 배치시킬 수 있다.

```c
typedef union {
    char dummy[10];
    long int var;
} aligntest_t;
```