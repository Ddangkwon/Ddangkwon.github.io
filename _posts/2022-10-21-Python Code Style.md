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

## 제네레이터 내포 표기

```python
def g():
	for i range(10):
		yield i

ca = g()

g = (i for i in range(10))

print(type(g)) # 튜플이 아닌 제네레이터 타입이 된다.
```

## 예외 처리

try~except~finally 형태로 표현

```python
l = [1, 2, 3]

try:
	l[i]
except IndexError as ex:
	print("don't worry : {}".format(ex))
except Exception as ex:
	print("other:{}".format(ex))
else:
	print(done) # 에러 발생하지 않을 때 출력
finally:
	print('clean up') # 어떠한 상황에서도 마지막에 출력할 내용
```

## 독자 예외 작성

```python
# 독자적으로 선언한 에러
class UppercaseError(Exception):
	pass

def word_check():
	words = ['APPLE', 'orange', 'banana']
	for word in words:
		if word.isupper():
			raise UppercaseError(word) # 이 경우일 때 해당 에러 raise
		
try:
	check()
except UppercaseError as exc:
	print('upper case error occured!')
```

## Import 문과 as

파이썬 package 에는 __init__.py 파일이 반드시 필요하다. 

예를 들어

personal_package
=> utils.py
=> __init__.py

와 같은 파일구조를 가지고 있을 때

```python
import personal_package.utils # 주로 이와 같이 call path를 모두 불러오는 것이 코드가 길어지더라도 어디에서 불러오는지 명확하게 알 수 있음
from personal_package import utils
from personal_package import utils as u # utils 를 줄여서 u로 표현하는 방법
```

### 패키지(package)란?

패키지(Packages)는 도트(.)를 사용하여 파이썬 모듈을 계층적(디렉터리 구조)으로 관리할 수 있게 해준다. 
패키지 구조로 파이썬 프로그램을 만드는 것이 공동 작업이나 유지 보수 등 여러 면에서 유리하다. 또한 패키지 구조로 모듈을 만들면 다른 모듈과 이름이 겹치더라도 더 안전하게 사용할 수 있다.

##  __init__.py, __all__ 의 의미

__init__.py 파일은 해당 디렉터리가 패키지의 일부임을 알려주는 역할을 한다.

 python3.3 버전부터는 __init__.py 파일이 없어도 패키지로 인식한다(PEP 420). 하지만 하위 버전 호환을 위해 __init__.py 파일을 생성하는 것이 안전한 방법이다.

__all__이 의미하는 것은 패키지 디렉터리에서 * 기호를 사용하여 import할 경우 이곳에 정의된 __all__ 내 선언된 모듈에 대해서만 import된다는 의미이다.

## setup.py

Pycharm IDE 에서는 Tools=> Create setup.py 를 통해 setup 파일을 생성할 수 있다.

```python
from setuptools import setup

setup(
    name='digit-recognizer',
    version='1.0.0',
    packages=[''],
    url='',
    license='Free',
    author='dram1',
    author_email='',
    description='digit package'
)
 

```

그리고  Tools=> Run setup.py task를 선택하고, sdist를 선택 및 command line에서 그냥 ok를 눌러주면 dist 폴더 내 패키지 파일이 생성된다.


### 관련 내용에 대한 자세한 정리 참고...

#### Setuptools
지난 글에서 파이썬의 표준 적인 설치 관행에 대해 살펴봤습니다. 기본적인 setup.py 파일도 제작했고요. 오늘은 Distutils 을 떠나, Setuptools 로 작업을 확장합니다. 지금 소개해 드리는 관행이 실제로 저희가 사용하고 있는 것인데 다음과 같은 기능들을 setup.py 에 추가하게 됩니다.

모듈 의존성 관리 — install_requires
비공개 모듈 설치 — dependency_links
콘솔 스크립트 설치 — entry_points
개발 모드 디플로이 — setup.py develop
전과 마찬가지로 Flowdas Books 라는 장고 애플리케이션을 사용해서 설명 드리겠습니다.

#### setup.py
Setuptools 를 사용하도록 수정된 setup.py 은 이렇게 됩니다.
```python
from setuptools import setup, find_packages

setup_requires = [
    ]

install_requires = [
    'django==1.6b4',
    'markdown==2.3.1',
    'pyyaml==3.10',
    'pillow==2.1.0',
    'lxml==3.2.3',
    'beautifulsoup4==4.3.1',
    ]

dependency_links = [
    'git+https://github.com/django/django.git@stable/1.6.x#egg=Django-1.6b4',
    ]

setup(
    name='Flowdas-Books',
    version='0.1',
    description='Flowdas Books',
    author='Flowdas',
    author_email='spammustdie@flowdas.com',
    packages=find_packages(),
    install_requires=install_requires,
    setup_requires=setup_requires,
    dependency_links=dependency_links,
    scripts=['manage.py'],
    entry_points={
        'console_scripts': [
            'publish = flowdas.books.script:main',
            'scan = flowdas.books.script:main',
            'update = flowdas.books.script:main',
            ],
        },
    )
```
#### setup(), find_packages()
Setuptools 에서 제공하는 두 개의 함수 setup() 과 find_packages() 를 사용합니다. setup() 은 표준 라이브러리에 포함된 Distutils 의 setup() 을 대체하는 것입니다. Distutils 의 것에 비해 더 다양한 옵션들을 처리합니다.

#### find_packages()
예전에는 packages 옵션에 패키지 이름들을 일일이 적어주었습니다. 최상단 패키지만 적어주어야 한다면 크게 문제될 것이 없지만, 하위 패키지들을 많이 만드는 방식의 프로그래밍을 하시는 분들은 영 불편해합니다. Setuptools 가 제공하는 find_packages() 함수는 폴더를 뒤져서 패키지들의 목록을 만들어 줍니다. 혹 뒤져야 할 폴더가 다른 곳에 있거나, 포함시키지 말아야 할 패키지가 있다면 인자로 지정할 수 있습니다.

#### install_requires
가장 중요한 부분은 이 프로젝트가 사용하는 패키지들을 지정하는 것인데, install_requires 옵션을 사용합니다. 전부 6개의 패키지를 지정했는데, 모두 django==1.6b4 와 같이 구체적인 버전을 지정했습니다. 처음부터 버전을 지정하지는 않고, 어느 정도 호환성 확인이 된 후에 버전을 확인하여 고정하게 됩니다. 버전 확인에는 pip freeze 명령을 사용하면 됩니다. 패키지 이름의 대소문자는 중요하지 않습니다.

#### setup_requires
install_requires 에 지정하는 것은 프로젝트를 위해 필요한 패키지들인데, 때로 setup.py 자신을 위해 필요한 패키지가 있을 수 있습니다. 이런 패키지들은 setup_requires 옵션을 사용하여 지정합니다. 이런 경우에 해당하는 패키지의 예는 setuptools_git 가 있습니다만, 저희는 사용하지 않기 때문에 자리만 마련하고 비워둡니다.

#### dependency_links
이 글을 쓰는 시점에 PyPI 에 등록된 장고의 최신 버전은 1.5.4 입니다. 때문에 위에서 지정한 1.6b4 버전은 PyPI 에서 발견할 수 없고, 당연히 setup.py 를 실행할 때 오류가 발생합니다. dependency_links 옵션은 PyPI 외의 장소에 있는 패키지를 설치할 수 있도록 합니다. 여러 가지 형태가 있습니다만 git 저장소를 사용하는 방법을 예시합니다. 장고의 git 저장소 주소인 https://github.com/django/django.git 앞에 git+ 를 붙여 URL 을 구성합니다. 여기에 1.6b4 버전이 들어있는 브랜치 stable/1.6.x 를 지정하는 @stable/1.6.x 를 붙입니다. 그냥 hash 를 붙여도 됩니다. 마지막으로 =Django-1.6b4 를 붙여서 패키지 이름과 버전을 지정합니다. 이 부분이 앞서 install_requires 에 지정된 부분과 일치해야 합니다.

이 방법을 소개하는 이유는, 같은 방법으로 여러분의 회사가 사용하는 git 저장소도 지정할 수 있기 때문입니다. 모든 패키지를 PyPI 에 올려놓을 수 없는 분들은 이 방법을 사용하면 됩니다.


## import 순서 예시

파이썬 표준라이브러리, 서드파티 라이브러리, 직접 정의한 패키지, local python 파일 순으로 import를 수행하는 것을 선호한다.
그리고 각자를 구분하기 위해 한 줄씩 공백을 두고 구분을 수행한다.
```python
# 파이썬 표준 라이브러리
import collections
import os
import sys
# 서드파티 라이브러리
import numpy
# 직접 정의한 패키지
import lesson_package
# local python 파일 순
import config


print(collections.__file__)
```

__file__ 을 통해 해당 패키지가 어디에 위치하고 있는지 확인할 수 있다.

## __name__ 과 __main__

__name__은 모듈의 이름이 저장되는 변수이며 import로 모듈을 가져왔을 때 모듈의 이름이 들어가게 된다.

```python
print(__name__) #  __main__
```

```python
# hello.py
print('hello 모듈 시작')
print('hello.py __name__:', __name__)    # __name__ 변수 출력
print('hello 모듈 끝')

```

```python

# main.py
import hello    # hello 모듈을 가져옴
print('main.py __name__:', __name__)    # __name__ 변수 출력

```

해당 코드의 결과는 다음과 같다.

### 실행결과
hello 모듈 시작
hello.py __name__: hello
hello 모듈 끝
main.py __name__: __main__

파이썬에서 import로 모듈을 가져오면 해당 스크립트 파일이 한 번 실행된다. 따라서 hello 모듈을 가져오면 hello.py 안의 코드가 실행됩니다. 따라서 hello.py의 __name__ 변수에는 'hello'(import된 모듈은 모듈의 이름(파일명))가 들어가고, main.py의 __name__ 변수에는 '__main__'이 들어간다.

즉 우리가 흔히 사용하는 if __name__=="__main__" 의 조건문의 경우 해당 파이썬 파일을 직접 실행하는 경우 즉, 프로그램의 시작점일 경우에만 실행된다.

## Timer 관련 참고 코드

__enter__, __exit__ 은 with 구문의 시작과 종료에 호출된다.
```python
import time

class Timer():
    def __init__(self):
        pass

    def __enter__(self):
        self.start_time = time.time()
    def __exit__(self, type, value, traceback):
        self.end_time = time.time() - self.start_time

with Timer():
    time.sleep(5)
```

## 클래스 생성자와 소멸자


```python
class Person(object):

    def __init__(self, name):
        self.name = name
    def __del__(self):
        print('bye')

person = Person('Alex')

del person # 소멸자 호출

```

## 클래스의 계승

```python
class Car(object):
    def run(self):
        print('run')

class HyundaiCar(Car):
    pass

class TeslaCar(Car):
    def auto_run(self):
        print('auto_run')

car = Car()
car.run()

# Car class를 계승했으므로 Car 메서드들을 사용할 수 있게된다.
hcar = HyundaiCar()
hcar.run()


tcar = TeslaCar()
tcar.run()
tcar.auto_run()
```


## 메서드 오버라이드 및 super

super 명령어는 이런 상속 관계에서 상속의 대상인 부모 클래스를 호출하는 함수

super()의 인자로는 두 개가 전달되며, 하위클래스의 이름과 하위클래스의 객체(object)가 필요
```python
class Car(object):
    def __init__(self, model=None)
        self.model = model
    def run(self):
        print('run')

class HyundaiCar(Car):
    # Method Override
    def run(self):
        print('fast run')

class TeslaCar(Car):
    def __init__(self, model='Model 3', enable_auto_run=False)
        # self.model = model
        super.__init__(model)
        self.enable_auto_run = enable_auto_run
    # Method Override
    def run(self):
        print('super fast run')
    def auto_run(self):
        print('auto_run')

car = Car()
car.run()

# Car class를 계승했으므로 Car 메서드들을 사용할 수 있게된다.
hcar = HyundaiCar()
hcar.run()


tcar = TeslaCar('Model S')
tcar.run()
tcar.auto_run()
```

## Property

주로 파이썬 class 변수에서 다음과 같은 조건으로 변수명을 작성한다.

1. 외부에서도 자유롭게 사용 가능할 때
```python
self.var = 1
```
2. 외부에서는 특정 조건에서만 읽고 쓰는 것이 가능하게 하고 싶을 때
```python
self._var = 1
```
3. 내부에서만 사용하는 변수로 사용하고 싶을 때
```python
self.__var = 1
```

```python
class Car(object):
    def __init__(self, model=None)
        self.model = model
    def run(self):
        print('run')

class HyundaiCar(Car):
    # Method Override
    def run(self):
        print('fast run')

class TeslaCar(Car):
    def __init__(self, model='Model 3', enable_auto_run=False, passwd = '123')
        # self.model = model
        super.__init__(model)
        self.enable_auto_run = enable_auto_run
        self.passwd = passwd
    @property # getter 
    def enable_auto_run(self):
        return self._enable_auto_run
    # setter를 통해 값 설정이 가능해짐
    @enable_auto_run.setter # setter
    def enable_auto_run(self, is_enable):
        # 값을 덮어쓸 때 제약을 걸고 싶을 때 property 와 setter를 사용한다.
        if self.passwd == '456'
            return self._enable_auto_run = is_enable
        else:
            raise ValueError
    # Method Override
    def run(self):
        print('super fast run')
    def auto_run(self):
        print('auto_run')

car = Car()
car.run()

# Car class를 계승했으므로 Car 메서드들을 사용할 수 있게된다.
hcar = HyundaiCar()
hcar.run()


tcar = TeslaCar('Model S', passwd='456')
tcar.run()
tcar.auto_run()
tcar.enable_auto_run = True # Error property를 붙이게 되면 private 변수 성질을 가진다.
```

## 덕타이핑
덕 타이핑은 실제 타입(클래스)은 상관하지 않고, 구현된 메서드로만 판단하는 방식

덕 타이핑은 "만약 어떤 새가 오리처럼 걷고, 헤엄치고, 꽥꽥거리는 소리를 낸다면 나는 그 새를 오리라 부르겠다."라는 의미

즉 해당 메서드를 호출할 수만 있다면 어떤 클래스이건 가리지 않고 호출하는 방식을 말하고 파이썬은 이를 지원한다.

```python

class Person(object):
    def __init__(self, age=1):
        self.age = age
    def drive(self):
        if self.age >= 18:
            print('ok')
        else
            raise Exception('No drive')

class Baby(Person):
    def __init__(self, age=1):
        if age < 18:
            super().__init__(age)
        else:
            raise ValueError

class Adult(Person):
    def __init__(self, age=1):
        if age < 18:
            super().__init__(age)
        else:
            raise ValueError

baby = Baby()
adult = Adult()
class Car(object):
    def __init__(self, model=None)
        self.model = model
    def run(self):
        print('run')
    # 파이썬의 덕타이핑
    def ride(self, person):
        person.drive()

car = Car()
car.ride(adult) # ok
```

## 추상 클래스