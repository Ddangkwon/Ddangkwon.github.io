.---
layout : post
title : 책 리뷰(코딩의 기술)
comments : true
categories : 
- Book Review
tags : [Book Review]
---
# 책 리뷰(코딩의 기술) 

## 1장. 읽기 좋은 코드를 작성하는 기술
 
읽기 좋은 코드는 가독성을 지표로 표현할 수 있다. 이러한 코드의 가독성은 코드의 보수성에 영향을 주는데,
여기서 코드의 보수성이란 코드의 변경, 추가 테스트가 얼마나 용이한지를 의미한다.

읽기 좋은 코드를 작성하는 요령을 간단히 설명하면,
"복잡한 코드 문제를 작게 나누고, 읽기 좋은 이름을 붙여 정리하자"
이다.

### 1.2 변수와 상수
변수 이름의 경우 의도 파악 등을 위해 명확한 이름을 붙인다.
상수의 경우 우리가 글로 이해할 수 있는 이름의 열거형을 선언하여 표현하면 코드의 가독성을 높일 수 있다.

```c
typedef enum state_e{
    STATE_INIT = 0,
    STATE_STANDBY,
    STATE_GO,
    STATE_STOP
};
```
### 1.3 조건식과 계산식

### 1.3.1 설명 전용 변수 사용

if-statement와 같은 조건 문에 복잡한 조건이 사용되는 경우 설명 전용 변수를 사용한다.

```c
const bool isZero = (y != 0);
const bool isStateFail = (state == STATE_FAIL);
const bool Judge = (!isZero && !isStateFail);

if(Judge)
{

}
```

### 1.3.2 조건식 함수화

```c
bool isZero()
 {
    return y != 0;
 }

 bool isStateFail()
 {
    return state == STATE_FAIL;
 }
 bool Judge()
 {
    return (!isZero && !isStateFail);
 }
```

### 1.3.3 설명 전용 변수 사용

설명 전용 변수를 사용하여 가독성을 높인다.

```c

const int maxSpeed = FACTOR * 2.0U * MAX_WHEEL_SPEED;
const int minSpeed = FACTOR * 2.0U * MIN_WHEEL_SPEED;
if(speed > maxSpeed)
{

}
else if(speed <= maxSpeed && speed > minSpeed)
{

}
else
{

}
```

### 1.3.4 계산식 함수화

계산식을 함수화 하여 그냥 봐도 무엇을 하는 코드인지 알게한다.
```c
int FindMaxSpeed(int x)
{
    return FACTOR * x * MAX_WHEEL_SPEED;
}

int FindMinSpeed(int x)
{
    return FACTOR * x * MIN_WHEEL_SPEED;
    
}
void speedfunc()
{
    const int maxSpeed = FindMaxSpeed();
    const int minSpeed = FindMinSpeed();

    if(speed > maxSpeed)
    {

    }
    else if(speed <= maxSpeed && speed > minSpeed)
    {

    }
    else
    {

    }
}

```
## 2장. 간단할 설계를 위한 원칙과 패턴

## 3장. 소스 코드 품질 측정