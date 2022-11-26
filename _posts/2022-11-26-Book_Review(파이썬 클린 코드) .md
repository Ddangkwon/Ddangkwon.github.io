---
layout : post
title : 책 리뷰(파이썬 클린 코드)
comments : true
categories : 
- Book Review
tags : [Book Review]
---
# 책 리뷰(파이썬 클린 코드) 

## 파이썬의 코딩 스타일 

### PEP-8의 특징

#### 검색 효율성

코드에서 토큰을 grep 할 수 있는 기능. 즉, 특정 파일이나 파일의 일부에서 특정 문자열을 찾는 기능

#### 일관성

코드가 일정한 포맷을 가져 가독성을 높인다.

#### 코드 품질

코드를 구조화 하여 살펴보면 한 눈에 코드를 이해하고 버그와 실수를 쉽게 찾을 수 있다.



### docstring

주석을 다는 것이 아닌 코드의 특정 컴포넌트에 대한 문서화를 말한다. 
파이썬의 경우 동적 타이핑을 하기 때문에 타입 등의 정의를 미리 docstring 을 통해 표현해두면 실수를 줄일 수 있다.


### annotation

기본 아이디어는 코드 사용에게 함수 인자로 어떤 값이 와야 하는지 힌트를 주는 것
annotation 을 사용하게 되면 __annotations__ 라는 특수한 속성이 생긴다. 이 속성을 통해 어노테이션 이름과 값을 매핑한 사전 타입의 값을 확인할 수 있다.

```python
class Hello:
    def world(self, num : int) -> int:
        return num
```


## Pythonic Code

### 인덱스와 슬라이스

```python
numbers = [1, 2, 3, 4, 5, 6, 7]

numbers[-1]

numbers[2:5] # 3, 4, 5

numbers[:3] # 4, 5, 6, 7

numbers[::] # 1, 2, 3, 4, 5, 6, 7

numbers[1:7:2] # 2 4 6
```