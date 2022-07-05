---
layout : post
title : TASKING Compiler
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---
# TASKING Compiler


## 빌드 옵션

### clear, noclear

초기화되지 않은 전역 변수의 경우 .bss 섹션에 저장된다.
=> 이 경우 Startup 코드에서 0으로 clear되는 것이 일반적

초기화 되는 전역변수인 .data 섹션의 경우 noclear에 해당한다.

이러한 clear와 no clear 를 빌드 옵션으로 지정할 수 있다.

```c
#include <stdio.h>
#pragma noclear
int init_data
#pragma clear
```

위의 예시에서 pragma 명령어를 통해 init_data를 프로그램 시작 시 전역에서 초기화 시키지 않고 이전 값을 유지하기 위하여 코드를 
다음과 같이 설정했다.
=> .bss 섹션에 해당하는 변수이므로 Startup 코드에서 초기화되어야 하지만 그렇지 않은 것


## Section

1. 코드 영역
=> 모든 코드의 경우 .text 섹션으로 정의한다.
2. 변수 영역

2.1 데이터 영역(.data)
=> 초기값이 있는 전역 변수가 이에 해당하고 ROM에 원본이 있고 RAM으로 copy하여 사용한다.
2.2 .bss 
=> 초기값이 없는 전역 변수로 RAM에만 세팅되어 사용된다
2.3 .rodata
=> const 변수로 ROM에만 세팅된다

또한 각 타입별로 3가지 접근 방식을 가질수 있고 그 내용은 다음과 같다.

1. __far
=> 기본 타입으로 어떤 주소 번지에든 위치할 수 있다.
2. __near
=> 섹션 타입 앞에 z가 붙고 각 세그먼트의 앞 16kb 에만 위치 가능
3. 레지스터 타입(__a0, __a1)
=> 각 레지스터 타입 별 기준 주소가 존재하고 그 주소를 기준으로 16bit offset 공간에 위치 가능

near 타입의 경우 가장 적은 어셈 라인으로 변수를 Read/Write 할 수 있다.
=> 속도 면에서 가장 효과적인 섹션 타입

### 섹션 타입 지정 방법
```cpp

char __far ch1;
char __a0 ch2;
int __near var1;


#pragma default_near_size
int var1;
int var2;
#pragma default_near_size default
```


