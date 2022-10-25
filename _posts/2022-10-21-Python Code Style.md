---
layout : post
title : Python Code Style
comments : true
categories : 
- python
tags : [python]
---
# Python Code Style


## 연산

```python
17 // 3 # 몫 3
17 % 3 # 나머지 2
5 ** 2 # 자승 표현 25
round(3.141414, 2) # 반올림하여 두번 째 자리까지 표현
```

```python
print(r'c:\user\folder') # raw 데이터라는 표시로 문자열 그대로 출력
print("""
line 1
line 2
line 3
""")
```

문자열 슬라이싱
```python
word = 'python'

print(word[0:2]) # py
print(word[2:]) # thon
print(word[-1]) # n
```

### f-strings

```python
name = 'Jun'
family = 'orei'

print(f'My name is {name}. My family name is {family})

```

## 리스트

### 리스트 메소드

```python
r = [1, 2, 3, 4, 5, 1, 2, 3]
print(r.index(3, 3))  # 3을 3번째 인덱스(4) 부터 검색해서 찾고 그 위치를 반환하세요 답 : 7
print(r.count(3)) # 3의 개수를 세서 반환하세요 => 2

r.sort() # 오름 차순으로 반환
r.sort(reverse=True) # 내림 차순으로 반환
r.reverse() # 정렬 이전 원본 상태로 되돌리기

s = 'my name is kwon'
to_split = s.split(' ') # 공백란을 기준으로 총 4개의 문자열로 반환
x = ' '.join(to_split) # join 함수를 사용하여 s 문자열로 복원
```

### 수치 전달과 참조 전달

수치 전달의 경우 수치만 전달하는 것이기 때문에 id값(주소값) 이 다르다.(변수)
반대로 참조 전달의 경우 주소를 복사하고 전달하는 것이기 때문에 id값이 같다.(리스트)



## 튜플(Tuple)

리스트의 경우 대괄호 [] 를 통해 표현하지만, 튜플은 소괄호 () 로 표현한다.

튜플은 값의 대입이 안된다.(immutable => 수치 변경 불가능)
인덱싱 및 슬라이싱은 지원한다.


### 튜플의 언패킹

```python
num_tuple = (10, 20)
x, y = num_tuple

print(x, y) # 10, 20
```


## 사전형(Dictionary)


## 집합형(Set)


## for else 문

주로 for 문에서 특정 경우 flag 를 활용하여 break문으로 탈출하고 하는 경우 for else문으로 대체하여 사용한다.


```python
for fruit in ['apple', 'banana', 'orange']
	print(fruit)
else:
	print('finish') # for 문에서 break로 빠지지 않는 이상 출력


```

## enumerate 함수

```python
for i, fruit in enmuerate(['apple', 'banana', 'orange'])
	print(i, fruit) # 0 apple 1 banana ...
```

## zip 함수

```python
a = [1, 2, 3]
b = ['a', 'b', 'c']

for x, y in zip(a, b):
	print(x, y) # 1 'a' \n 2 'b'...
```

## 사전형을 for 문으로 처리하기

```python
dict = {'appple' : 1, 'banana' : 200}
for k, v in dict.items():
	print(k, ':', v)
```


## Docstrings
함수 내 함수의 의미 및 Argument, return 값들을 알려주는 주석

```python
def ex_func(param1, param2):
	def ex_func(param1, param2):
    """
    
    :param param1: 
    :param param2: 
    :return: 
    """

	return True
ex_func.__doc__ # 함수의 doc string을 출력해볼 수 있음
```

## 함수 내 함수
주로 특정 함수 내에서만 쓰이는 함수를 정의할 때 함수 내 함수를 정의한다.
```python
def calc(a, b):
	def plust(c, d):
		return c + d
	r1 = plus(a, b)
	
	return r1
```

## 클로저
이렇게 함수를 둘러싼 환경(지역 변수, 코드 등)을 계속 유지하다가, 함수를 호출할 때 다시 꺼내서 사용하는 함수를 클로저(closure)라고 한다.
```python

def outer(a, b):

	def inner():
		return a+b
	return inner

	
f = outer(1, 2)
r = f() # 3

```


```python

def circle_area(pi):
	
	def area(rad):
		return pi * rad * rad
	return area

# outer 함수 호출
ca1 = circle_area(3.14)
ca2 = circle_area(3.141414)

# inner 함수 호출
print(ca1(10))
print(ca2(10))
```

## 데코레이터


## 람다

람다 함수의 경우 ㅎ함수를 딱 한줄로 표현하게 해주는 형식을 말한다.
람다 함수의 표현 형태는 다음과 같다

lambda 매개변수 : 표현식 
```python
date = ['MON', 'TUE', 'WED', 'THU', 'FRI']

def change_words(words, func):
	for word in words:
		print(funct(word))

def sample_func(word):
	return word.capitalize() #  문자열에서 첫문자를 대문자로 만들어 리턴

sample_func2 = lambda word : word.capitalize()
change_words(date, sample_func) 
change_words(date, lambda word:word.capitalize()) 

```


## 제네레이터

```python

def test_generator():
     print('yield 1 전')
     yield 1
     print('yield 1과 2사이')
     yield 2
     print('yield 2와 3사이')
     yield 3
     print('yield 3 후')

g = test_generator()
next(g) # yield 1 전
next(g) # yield 1과 2사이
next(g) # yield 2와 3사이
next(g) # yield 3 후

```

yield from 으로 for 문 대체

```python

def three_generator():
    a = [1, 2, 3]
     for i in a:
		yield i
 
gen = three_generator()


def three_generator_after():
    a = [1, 2, 3]
    yield from a
gen = three_generator()

gen1 = three_generator_after()
```

## 사전 내포 표기

아래 dictionary 자료형의 for 반복문 표현을 다음과 같이 축약할 수 있다.
```python
w = ['a', 'b', 'c']
f = [1, 2, 3]

d = {}
for x, y in zip(w, f):
	d[x] = y

d = {x : y for x, y in zip(w, f)} 

```