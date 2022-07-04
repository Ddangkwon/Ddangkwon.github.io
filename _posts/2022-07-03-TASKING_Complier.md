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
