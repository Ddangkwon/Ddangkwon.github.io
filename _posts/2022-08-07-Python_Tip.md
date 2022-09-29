---
layout : post
title : python Tip
comments : true
categories : 
- python
tags : [python]
---
# python Tip


## Pycharm 에서 코드 내 pip install 명령어 사용하기 

1. subprocess.check_call() 함수 사용하기
```python
import subprocess

subprocess.check_call([sys.executable, "-m", "pip", "install", 'numpy'])
subprocess.check_call([sys.executable, "-m", "pip", "install", 'pandas==1.3.5'])

```

2. os.system() 함수 사용하기
```python
import os

os.system("pip install numpy")

```


## 파이썬을 파이썬 답게

해당 내용은 프로그래머스에 '파이썬을 파이썬 답게' 라는 교육프로그램을 요약한 것입니다.

### 2차원 배열 각 행 길이 반환

```python
def solution(mylist):
    return list(map(len, mylist))
```


### 몫과 나머지 함수

파이썬의 divmod와 unpacking을 이용하여 몫과 나머지를 다음과 같이 구할 수 있다.

```python
a = 9
b = 2
print(*divmod(a, b))
```

n진법으로 표기된 string을 10진법 숫자로 변환하기 - int 함수

파이썬의 경우 int 함수에서 다음과 같이 진법 변환을 지원한다.
 int(x, base=10)
 
```python
num = '3212'
base = 5
answer = int(num, base)
```

### 문자열 정렬함수

문자열 좌측, 중앙, 우측 정렬에 관련된 함수는 다음과 같다.

```python
s = '가나다라'
n = 7

s.ljust(n) # 좌측 정렬
s.center(n) # 가운데 정렬
s.rjust(n) # 우측 정렬

```

파이썬에는 알파벳을 출력하는 별도의 함수가 있다.

```python

import string 

string.ascii_lowercase # 소문자 abcdefghijklmnopqrstuvwxyz
string.ascii_uppercase # 대문자 ABCDEFGHIJKLMNOPQRSTUVWXYZ
string.ascii_letters # 대소문자 모두 abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
string.digits # 숫자 0123456789

```

### 원본을 유지한채 정렬된 리스트 구하기

원래대로라면 깊은 복사 수행 후 sort 함수 사용


```python
list1 = [3, 2, 5, 1]
list2 = copy.deepcopy(list1)
list2.sort()
```

다음과 같이 sorted 함수를 사용하면 해당 문제를 해결할 수 있음
```python
list1 = [3, 2, 5, 1]
list2 = sorted(list1)
```


### zip 함수에 대해...

zip 함수를 이용한 2차원 배열 뒤집기를 예로 들면,

기존 스타일의 2차원 배열 뒤집기의 경우 다음과 같이 표현될 수 있다.

```python
mylist = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
new_list = [[], [], []]

for i in range(len(mylist)):
    for j in range(len(mylist[i])):
        new_list[i].append(mylist[j][i])

```

다음과 같이 unpacking과 zip 함수를 사용하여 구현할 수 있다.
```python
mylist = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
new_list = list(map(list, zip(*mylist)))
```

1. 리스트 언패킹으로 괄호 제거
([1, 2, 3] [4, 5, 6] [7, 8, 9])
2. zip([], [], []) : zip 함수 내에 3개씩의 정수를 가진 세 개의 리스트가 들어가있는 형태
3. 각각의 리스트에서 한개씩 꺼내 3개의 튜플을 반환
([(1, 4, 7), (2, 5, 8), (3, 6, 9)])
4. map 함수로 리스트화
[[1, 4, 7], [2, 5, 8], [3, 6, 9]]

#### packing 과 unpacking

packing : 인자로 받은 여러개의 값을 하나의 객체로 합쳐서 받을 수 있도록 한다.

```python
def sum_func(*num):
    result = 0
    for num in num:
        result += num
    return result

print(sum_all(1, 2, 3)) # 6
print(sum_all(1, 2, 3, 4, 5, 6)) # 21
```

unpacking : 여러개의 객체를 포함하고 있는 하나의 객체를 풀어준다.

packing의 경우 매개변수에 *를 붙이고 unpacking의 경우 인자 앞에 붙여서 사용한다.

```python
def sum_func(x, y, z):
    return x + y + z

numbers = [1, 2, 3]

print(sum(*numbers)) # 출력 : 6
```


### zip 함수 세부 활용법
zip 함수 설명
=> zip(*iterables)는 각 iterables 의 요소들을 모으는 이터레이터를 만듭니다.
튜플의 이터레이터를 돌려주는데, i 번째 튜플은 각 인자로 전달된 시퀀스나 이터러블의 i 번째 요소를 포함합니다.

사용 예 #1 - 여러 개의 Iterable 동시에 순회할 때 사용

```python
list1 = [1, 2, 3, 4]
list2 = [100, 120, 30, 300]
list3 = [392, 2, 33, 1]
answer = []
for number1, number2, number3 in zip(list1, list2, list3):
   print(number1 + number2 + number3)
```

사용 예 #2 - Key 리스트와 Value 리스트로 딕셔너리 생성하기
파이썬의 zip 함수와 dict 생성자를 이용하면 코드 단 한 줄로, 두 리스트를 합쳐 딕셔너리로 만들 수 있습니다.

```python
animals = ['cat', 'dog', 'lion']
sounds = ['meow', 'woof', 'roar']
answer = dict(zip(animals, sounds)) # {'cat': 'meow', 'dog': 'woof', 'lion': 'roar'}
```

index를 활용하여 원소에 접근하는 방법 대신 zip 함수 활용 케이스

인접한 list 내부 변수끼리의 차 계산

```python
def solution(mylist):
    answer = []
    for i in range(len(mylist)-1):
        answer.append(abs(mylist[i] - mylist[i+1]))
    return answer

if __name__ == '__main__':
    mylist = [83, 48, 13, 4, 71, 11]    
    print(solution(mylist))
```


```python
def solution(mylist):
    answer = []
    for number1, number2 in zip(mylist, mylist[1:]):
        answer.append(abs(number1 - number2))
    return answer

if __name__ == '__main__':
    mylist = [83, 48, 13, 4, 71, 11]    
    print(solution(mylist))
```


### 모든 멤버의 type 변환하기 - map

```python
list1 = ['1', '100', '33']
list2 = list(map(int, list1))
```