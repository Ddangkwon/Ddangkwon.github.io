---
layout : post
title : STL_String
comments : true
categories : 
- CodingTest
tags : [CodingTest]
---

# STL_String


## string 개요

C++ 표준 라이브러리(STL, Standard Template Library)에서 제공하는 문자열 클래스로,
문자열을 보다 편리하게 다룰 수 있도록 다양한 기능과 연산자를 제공한다.

**헤더 파일**
```cpp
#include <string>
```

string 클래스는 동적 메모리를 내부적으로 관리하여 크기가 자동으로 조정된다.


## 주요 특징

- **가변 길이 문자열** 관리
- 문자열 연결, 비교, 검색, 수정 등의 다양한 기능 지원
- C 스타일 문자열(char 배열)보다 안전하고 편리함


## 기본 사용법

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str1 = "Hello";
    string str2 = "World";

    // 문자열 합치기
    string str3 = str1 + " " + str2;
    cout << str3 << endl; // Hello World

    // 문자열 길이
    cout << str3.length() << endl;

    // 부분 문자열 접근
    cout << str3[0] << endl; // 'H'

    // 문자열 비교
    if (str1 == "Hello") {
        cout << "str1 is Hello" << endl;
    }

    return 0;
}
```


## 주요 멤버 함수

### 문자열 생성 및 대입

- 기본 생성자: `string s;`
- 문자열 초기화: `string s = "text";`
- 복사 생성자: `string s2 = s1;`
- 대입 연산자: `s1 = s2;`

### 문자열 크기

- `size()`, `length()`: 문자열 길이 반환
- `empty()`: 문자열이 비었는지 확인

### 문자열 수정

- `push_back(char c)`: 문자열 끝에 문자 추가
- `pop_back()`: 문자열 끝 문자 제거
- `append(string s)`: 문자열 뒤에 추가
- `insert(pos, string)`: pos 위치에 문자열 삽입
- `erase(pos, len)`: pos 위치부터 len만큼 삭제
- `replace(pos, len, string)`: pos부터 len길이만큼 다른 문자열로 교체

### 문자열 접근

- `at(pos)`: pos 위치 문자 접근 (범위 검사 O)
- `operator[]`: pos 위치 문자 접근 (범위 검사 X)
- `front()`, `back()`: 첫 문자, 마지막 문자 접근

### 문자열 검색

- `find(string)`: 해당 문자열이 처음 등장하는 위치 반환, 없으면 string::npos 반환
- `rfind(string)`: 마지막 등장 위치 반환
- `substr(pos, len)`: pos부터 len 길이만큼 부분 문자열 반환

### 문자열 비교

- `==`, `!=`, `<`, `>` 등 연산자 지원
- `compare(string)`: 두 문자열 비교, 같으면 0, 다르면 음수 또는 양수 반환


## 주요 예제

### 문자열 연결

```cpp
string a = "abc";
string b = "def";
string c = a + b; // "abcdef"
```

### 문자열 삽입, 삭제

```cpp
string s = "abcdef";
s.insert(3, "123"); // "abc123def"
s.erase(1, 2); // "a123def"
```

### 문자열 찾기

```cpp
string s = "abcdefg";
size_t pos = s.find("cde");
if (pos != string::npos) {
    cout << "Found at: " << pos << endl;
}
```

### 부분 문자열 추출

```cpp
string s = "abcdefg";
string sub = s.substr(2, 3); // "cde"
```


## string과 C 문자열(char*) 변환

- string -> char 배열

```cpp
string s = "hello";
const char* c = s.c_str();
```

- char 배열 -> string

```cpp
const char* c = "hello";
string s(c);
```


## 요약

- string 클래스는 동적 크기 관리, 편리한 수정, 검색 기능 제공
- 다양한 연산자 오버로딩으로 직관적인 사용 가능
- C 스타일 문자열에 비해 메모리 관리와 오류 방지 측면에서 안전하다

---





## 정올 문제 풀이


## String 자료형 (C++) / Python

아래 조건을 만족하는 프로그램을 작성하시오.

ⓐ. 문자열 S와 T를 입력 받는다.

ⓑ. 문자열 S의 첫 문자부터 검열하다가 T문자열을 만나면 삭제하고 이후 문자열을 이어 붙인다.

ⓒ. 문자열 S에서 금지된 문자열 T가 발견되지 않을 때까지 ⓑ를 반복한다.

ⓓ. S의 남은 문자열을 출력한다.​ 


## 입력
첫 번째 줄에 문자열 S를 입력받으시오. (1 <= S의 길이 <= 100)

두 번째 줄에 문자열 T를 입력받으시오. (1 <=​ T의 길이 <= S의 길이)​


## 출력
문제에서 제시된 작업을 수행한 후 첫 번째 문자열 S에 남은 문자열을 출력한다. 출력할 문자열이 남아 있음을 보증한다.



```cpp

```