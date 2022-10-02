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


### sequence 멤버를 하나로 이어붙이기 - join

join 함수를 사용하여 문자열을 concat 할 수 있음
```python
my_list = ['1', '100', '33']
answer = ''
for value in my_list:
    answer += value

```

```python
my_list = ['1', '100', '33']
answer = ''.join(my_list) # '110033'

```

### sequence type의 * 연산

파이썬에서는 * 연산자를 통해 반복 리스트나 문자열을 만들 수 있다.

```python
n = 3
answer = 'abc' * n # 'abcabcabc'
```

```python
n = 3
answer= [123, 456] * n # [123, 456, 123, 456, 123, 456]

``` 


### 곱집합(Cartesian product) 구하기 - product

파이썬에서는 itertools.product를 이용하면, for 문을 사용하지 않고도 곱집합을 구할 수 있다.

```python
import itertools

iterable1 = 'ABCD'
iterable2 = 'xy'
iterable3 = '1234'

print(list(itertools.product(iterable1, iterable2, iterable3)))
```

### 2차원 리스트를 1차원 리스트로 만들기(Flatten) - from_iterable

```python
my_list = [[1, 2], [3, 4], [5, 6]]

# 방법 1 - sum 함수
answer = sum(my_list, [])

# 방법 2 - itertools.chain
import itertools
list(itertools.chain.from_iterable(my_list))

# 방법 3 - itertools와 unpacking
import itertools
list(itertools.chain(*my_list))

# 방법 4 - list comprehension 이용
[element for array in my_list for element in array]

# 방법 5 - reduce 함수 이용 1
from functools import reduce
list(reduce(lambda x, y: x+y, my_list))

# 방법 6 - reduce 함수 이용 2
from functools import reduce
import operator
list(reduce(operator.add, my_list))

# 방법 7 - numpy 라이브러리의 flatten 이용
import numpy as np
np.array(my_list).flatten().tolist()
```


### 순열과 조합 - combinations, permutations

순열과 조합에 관한 파이썬에서의 함수 설명

```python
import itertools

pool = ['A', 'B', 'C']
print(list(map(''.join, itertools.permutations(pool)))) # 3개의 원소로 순열 만들기
print(list(map(''.join, itertools.permutations(pool, 2)))) # 2개의 원소로 순열 만들기

print(list(map(''.join, itertools.combinations(pool)))) # 3개의 원소로 순열 만들기
print(list(map(''.join, itertools.combinations(pool, 2)))) # 2개의 원소로 순열 만들기
```

### 가장 많이 문자, 숫자 찾기 - Counter

파이썬의 collections.Counter 클래스를 사용하면 해당 문제를 간단하게 해결할 수 있음


```python
import collections
my_list = [1, 2, 3, 4, 5, 6, 7, 8, 7, 9, 1, 2, 3, 3, 5, 2, 6, 8, 9, 0, 1, 1, 4, 7, 0]
answer = collections.Counter(my_list)

print(answer[1]) # = 4
print(answer[3])  # = 3
print(answer[100]) # = 0

```


### flag 대신 for-else 사용하기

flag 옵션을 사용해서 문제를 해결하는 경우 

```python
import math

if __name__ == '__main__':
    numbers = [int(input()) for _ in range(5)]
    multiplied = 1
    flag = True
    for number in numbers:
        multiplied *= number
        if math.sqrt(multiplied) == int(math.sqrt(multiplied)):
            flag = False
            print('found')
            break

    if flag:
        print('not found')
```


```python
import math

if __name__ == '__main__':
    numbers = [int(input()) for _ in range(5)]
    multiplied = 1
    for number in numbers:
        multiplied *= number
        if math.sqrt(multiplied) == int(math.sqrt(multiplied)):
            print('found')
            break
    else:
        print('not found') # for 구문이 break 등으로 중간에 빠져나오지 않고 끝가지 실행 됐을 때 else 문 실행

```

### 두 변수의 값 바꾸기 - swap

파이썬의 경우 다른 언어와 다르게 temp 라는 swap을 위한 임시 변수 없이 바로 두 변수의 값을 바꿀 수 있음

```python
a = 3
b = 'abc'

temp = a
a = b
b = temp
```

```python
a = 3
b = 'abc'

a, b = b, a # 다음과 같이 값 스왑 가능
```

### 이진 탐색하기 - binary search

파이썬에는 이진 탐색 알고리즘 모듈이 있어 해당 메소드를 사용하여 이진 탐색을 수행할 수 있다.

```python
import bisect
mylist = [1, 2, 3, 7, 9, 11, 33]
print(bisect.bisect(mylist, 3)) # 3이라는 값의 위치를 찾아 반환

```

### 클래스 인스턴스 출력하기 - class의 자동 string casting

기존처럼 클래스 인스턴스를 출력(print)하기 위해서 별도의 print 메서드를 선언하고 사용해야 한다.


```python

class Coord(object):
    def __init__(self, x, y):
        self.x, self.y = x, y

point = Coord(1, 2)
print( '({}, {})'.format(point.x, point.y) ) 

# 또는
def print_coord(coord):
    print( '({}, {})'.format(coord.x, coord.y) )
print_coord(point)

```

```python
class Coord(object):
    def __init__ (self, x, y):
        self.x, self.y = x, y
    def __str__ (self):
        return '({}, {})'.format(self.x, self.y)

point = Coord(1, 2) 
print(point)# __str__ 호출
```


### 가장 큰 수, inf
MAX 값 등을 할당 할때 사용


```python
min_val = float('inf')
max_val = float('-inf')
```

### with-as 구문을 이용한 파일 입출력

기존 방식은 EOF를 만날 때까지, 파일 읽기를 라인 바이로 반복한다.

```python
f = open('myfile.txt', 'r')
while True:
    line = f.readline()
    if not line: 
        break
    raw = line.split()
    print(raw)
f.close()
```
파이썬에서는 with-as 구문을 이용하여 코드를 간결하게 만들 수 있다.

별도의 file close 함수를 호출 할 필요가 없고, readlines가 EOF 까지 읽으므로, EOF 체크가 불필요하다.
```python
with open('myfile.txt') as file:
    for line in file.readlines():
        print(line.strip().split('\t'))

```