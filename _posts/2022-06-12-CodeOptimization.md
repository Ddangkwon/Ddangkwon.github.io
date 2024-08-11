---
layout : post
title : 코드 최적화(CodeOptimization)
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---
# 코드 최적화

최적화의 등가교환(Trade-Off)

크기 vs 속도
성능 vs 가독성

임베디드 소프트웨어의 최적화 규칙

최선의 알고리즘, 최적의 코드를 찾아라
하드웨어 특성(프로세서), 개발 툴 등을 잘 이해하고 활용하라

헤더 인클루드 중복성 제거

```c
#ifndef FUNC_H// 정의가 되어있지 않을 경우 인클루드(딱 한번만 인클루드 하게 됨)
#define FUNC_H

/* 내용 */

#endif FUNC_H
```


# C에서 최적화를 위한 표현법

## 비용이 낮은 연산자를 선택하라

어셈블리 단에서 확인해보면, 나누기 곱셈과 같은 연산보다 비트 쉬프트 연산이 더 적은 명령어를 사용한다.
따라서 2의 지수 승의 나누기 곱셈 연산을 할 때는 쉬프트 연산을 활용하는 것이 좋다

## Short Circuit 원리의 활용

&& : 첫 비교문이 거짓이면 모두 거짓이므로, 뒤의 비교문은 보지 않는다.
=> 거짓의 확률이 높은 비교문을 앞에 둔다.
|| : 첫 비교문이 참이면 모두 참이 되므로 그 뒤의 비교문은 모두 수행하지 않는다.
=> 참의 확률이 높은 비교문을 앞에 둔다.

## 연관된 표현은 묶어서 처리한다

=> 이 부분의 경우 속도와 코드의 가독성의 Trade-off 관계


## 실수 연산


### 실수의 나누기는 느리다
실수에서 나누기의 연산은 상당히 많은 연산시간을 잡아먹는다.

### 가능하면 double 자료형 대신 float 자료형을 사용하라

### Math 라이브러리 함수를 되도록 사용하지 않는다
- Math 라이브러리 함수들은 오버헤드가 크다.
- 자주 사용되는 값을 테이블로 설정하여 사용한다.

### 가능하면 고정 소수점으로 변환하여 사용하라

# 펌웨어 개발 규칙

## 숫자 대신 의미 있는 상수명 사용


### const 사용

### #define 사용

### 열거형 enum 사용

### 함수 포인터 사용

```c
#include <stdio.h>
#include <stdlib.h>

typedef void (pCallback)(uint8_t sec);

typedef struct{
    pCallback Forward;
    pCallback Backward;
}MotorCallback_t;

MotorCallback_t MC;

static void Forward(uint8_t sec)
{

}

static void Backward(uint8_t sec)
{

}

void RegisterCallback(void)
{
    MC.Forward = Forward;
    MC.Backward = Backward;
}

int main()
{
    RegisterCallback();
    MC.Forward(5);
    MC.Forward(10);
}
```


## volatile 키워드 사용


### IO 포트 접근
하드웨어 주소에 접근하는 경우 volatile을 선언한다.

### 인터럽트 핸들러와 공유하여 사용하는 global 변수
global 변수를 인터럽트 핸들러 또는 일반 프로세스보다 우선순위가 높은 스레드와 공유하여 사용하는 경우 volatile을 선언한다.


### 기능이 없어 컴파일 단계에서 무시될 수 있지만, 무시되면 안되는 경우
의미없는 for loop 를 통해 delay를 구현하려는 경우 count 변수에 volatile 이 필요하다.

### 하드웨어 접근을 위한 포인터 사용법
하드웨어 레지스터도 특정 버스 주소에 연결되어 있기 때문에 volatile 을 사용한다.

## 메모리 정렬
- __attribute__((aligned (4)))
- #pragma pack(4)

### 일반 변수

```c
int gVar __attribute__((aligned (4)));
```
### 구조체 변수
char 같은 경우 aligned 4를 사용하게 되면 메모리 낭비가 이루어질 수 있으므로 자주 사용되는 변수에만 사용하여 소요 시간 절감을 이루면서 메모리 낭비를 막는다.
```c

typedef struct
{
    int var __attribute__((aligned (4)));
    char ch __attribute__((aligned (4)));
}var_t;
```
### 함수

```c
__attribute__((aligned (4))) void func()
{

}
```

## 실수 사용시 고료사항

### 실수의 연산속도
별도의 FPU 와 같은 하드웨어가 없을 경우 연산 처리 속도가 10배 이상 느려질 수 있다. 따라서 고정 소수점을 사용하거나 정수 연산을 많이 사용하고, 필요한 경우에만 부동 소수점 연산을 사용한다.

### 실수 변수들의 비교 주의
실수 변수들끼리 비교연산을 사용할 때 == 과 같은 같다 비교 연산은 되도록 사용하지 않도록 한다. 사용할 경우 특정 값을 곱해 고정 소수점 연산으로 비교하는 방법으로 사용해도 좋다.

## 태스크의 병렬처리

### 인터럽트 핸들러와 임계 영역(Critical Section)
- 여러 태스크가 동시에 접근한는 공유자원을 같이 쓰고 읽어 간섭이 일어날 수 있는 영역을 임계 영역(Critical Section) 이라고 한다.
- 임계 영역을 처리하는 기본적인 방식은 한 태스크가 공유자원을 점유할 때 다른 태스크가 접근하지 못하도록 세마포어(Semaphore), 뮤텍스(Mutex) 와 같은 방법을 사용한다.

- 일반 펌웨어 동작과 인터럽트 핸들러와 관련해서는 공유자원을 사용하는 경우 Interrupt 비활성화를 수행한다.


```c
int gVar = 0;
/* 공유자원 접근 */

void test_func()
{
    __disable_irq();
    gVar = 1;
    __enable_irq();
}


```
## 기타 성능 규칙

### register 지시자 사용

- register 지시자는 C 언어에서 변수를 CPU 레지스터에 저장하도록 컴파일러에게 힌트를 주는 역할을 한다. 레지스터에 저장된 변수는 메모리에서 값을 읽거나 쓰는 것보다 훨씬 빠르기 때문에, 매우 빈번하게 접근하는 변수에 사용하면 성능을 최적화할 수 있다.

- 그러나 현대 컴파일러들은 최적화를 자동으로 수행하기 때문에, register 지시자를 사용하는 것은 거의 필요하지 않으며, 실제 성능 차이는 미미할 수 있다. 또한, register 지시자는 주소 연산(&)을 사용할 수 없다. 이는 레지스터에 저장된 변수의 주소를 알 수 없기 때문이다.
```c
#include <stdio.h>

int main() {
    // register 지시자를 사용하여 변수 i를 레지스터에 저장하도록 요청
    register int i;
    int sum = 0;

    for (i = 0; i < 1000; i++) {
        sum += i;
    }

    printf("Sum: %d\n", sum);

    return 0;
}
```

### 나눗셈 연산 대신 비트 사용
- 비트 연산을 사용하여 나눗셈 연산을 구현할 수 있다. 특히, 2의 거듭제곱으로 나누는 경우, 비트 시프트 연산을 사용하는 것이 매우 효율적입니다. 아래는 이를 활용한 예시이다.
```c
#include <stdio.h>

int main() {
    int dividend = 40;
    int divisor = 8;

    // 비트 시프트를 이용한 나눗셈 (divisor가 2의 거듭제곱일 때만 사용 가능)
    int quotient = dividend >> 3;  // 40을 8로 나누는 것과 동일 (8은 2^3이므로 오른쪽으로 3비트 시프트)

    printf("Quotient using bit shift: %d\n", quotient); // 결과 5

    return 0;
}

```

### 인자의 포인터 전달

### 반복문 사용




## 펌웨어의 양산 및 유지 보수

### 버전 관리

### 디버깅 레벨에 따른 printf 함수 관리