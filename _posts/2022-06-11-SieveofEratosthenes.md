---
layout : post
title : 에라토스테네스의 체(Sieve of Eratosthenes)
comments : true
categories : 
- Algorithm
tags : [Algorithm]
---
# Sieve of Eratosthenes(에라토스테네스의 체)

소수 판별 알고리즘으로 주로 시간 제한이 걸려있는 소수 판별 문제에 사용한다
그리고 대량의 숫자 범위 내의 소수 판정에 사용한다.

기존 소수 판별 알고리즘 즉 그리디 방식의 경우 시간복잡도는 o(N^(1/2)) ~ o(N)

기존 방식
```c
#include <stdio.h>
#include <math.h>

bool isPrime(int x)
{
    int range = sqrt(x); // 두 숫자의 곱으로 표현될 때 각 약수들은 대칭을 이루기 때문에 제곱근까지만 파악하면 됨
    for(int i = 2; i <= range; i++)
    {
        if(x % i == 0)
            return False;
    }
    return True;

}

int main(void)
{
    printf("%d\n". isPrime(123124));
    return 0;
}
```


에라토스테네스의 체 알고리즘 방식은 대략적으로 다음과 같다

1. 배열을 선언하고 탐색하고자 하는 범위내의 자연수를 넣는다.
2. 2부터 시작하여 해당 숫자의 배수의 숫자들은 모두 지운다.(자기 자신은 지우지 않는다.)

```c
void PrimeSieve(int *arr)
{
    for(int i = 2; i < 100; i++)
    {
        if(arr[i] == 0)
            continue;
        for(int j = 2 * i; j < 100; j += i)
        {
            arr[j] = 0;
        }
    }
    return ;
}


int main(void)
{
    int arr[100] = { 0 };
    for(int i = 2; i  < 100; i++)
    {
        arr[i] = i;
    }
    PrimeSieve(arr);
    for(int i = 2; i  < 100; i++)
    {
        printf("%d\n". arr[i]);
    }
    return 0;
}

```