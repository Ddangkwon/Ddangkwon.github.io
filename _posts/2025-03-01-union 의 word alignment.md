---
layout : post
title : union 의 word alignment
comments : true
categories : 
- C
tags : [C]
---

# Union을 활용한 Word Alignment 최적화

## Word Alignment(단어 정렬)란?

CPU가 메모리를 접근할 때, 특정 크기(예: 2, 4, 8 바이트) 단위로 정렬된 데이터에 더 빠르게 접근할 수 있습니다. 정렬되지 않은 데이터에 접근하면 **패딩(padding)이 추가되거나, 추가적인 연산이 발생하여 성능이 저하될 수 있습니다.**

목표는 변수를 워드 크기의 정수배 어드레스에 배치하는 것

예를 들어, struct을 사용할 때 멤버의 크기 때문에 **자동으로 패딩이 추가**될 수 있습니다.

---

## Word Alignment 문제 예제

다음 구조체를 보겠습니다.

```c
#include <stdio.h>

struct Data {
    char a;   // 1바이트
    int b;    // 4바이트
    short c;  // 2바이트
};

int main() {
    printf("Size of struct Data: %zu bytes\n", sizeof(struct Data));
    return 0;
}
```

**출력 예시 (시스템에 따라 다름)**:
```
Size of struct Data: 12 bytes
```



---

## Union을 활용한 Word Alignment 최적화

union을 사용하면 **모든 멤버가 같은 메모리 공간을 공유**하므로, 메모리 정렬을 최적화할 수 있습니다.

### 방법 1: 구조체 안에 `union` 사용

```c
#include <stdio.h>

union DataAlign {
    int b;     // 가장 큰 데이터 크기에 맞춰 정렬됨 (4바이트)
    struct {
        char a;
        short c;
    };
};

int main() {
    printf("Size of union DataAlign: %zu bytes\n", sizeof(union DataAlign));
    return 0;
}
```

**출력 결과 (예시)**:
```
Size of union DataAlign: 4 bytes
```

**메모리 절약 효과**  
- union 내부에서 가장 큰 데이터(int b)의 크기인 4바이트를 기준으로 정렬됨
- char a 와 short c는 int와 동일한 메모리를 사용하므로 **추가 패딩 없이 정렬됨**
- 일반 구조체보다 메모리를 덜 사용

---

### 방법 2: 더 큰 바이트 정렬 기준 적용

```c
#include <stdio.h>

union WordAligned {
    char bytes[8];   // 8바이트 정렬 기준
    struct {
        int a;       // 4바이트
        short b;     // 2바이트
        char c;      // 1바이트
        char d;      // 1바이트 (패딩 없이 저장 가능)
    } data;
};

int main() {
    printf("Size of union WordAligned: %zu bytes\n", sizeof(union WordAligned));
    return 0;
}
```

**출력 결과**:
```
Size of union WordAligned: 8 bytes
```



```c
#include <stdio.h>

union WordAligned {
    char bytes[16];   // 16바이트 정렬 기준
    struct {
        long long a;  // 8바이트
        int b;        // 4바이트
        short c;      // 2바이트
        char d;       // 1바이트
        char e;       // 1바이트 (패딩 없이 저장 가능)
    } data;
};

int main() {
    printf("Size of union WordAligned: %zu bytes\n", sizeof(union WordAligned));
    return 0;
}
```

**출력 결과**:
```
Size of union WordAligned: 16 bytes
```

**효율적인 데이터 저장**  
- `bytes[16]`을 활용하여 **16바이트 정렬 기준**을 맞춤
- `long long`, `int`, `short`, `char`들이 **추가적인 패딩 없이** 저장됨
- CPU가 **한 번의 연산으로 16바이트 접근 가능**하여 성능 향상

**효율적인 데이터 저장**  
- `bytes[8]`을 활용하여 **8바이트 정렬 기준**을 맞춤
- `int`, `short`, `char`들이 **추가적인 패딩 없이** 저장됨
- CPU가 **한 번의 연산으로 8바이트 접근 가능**하여 성능 향상

---

## 정리

| 기법 | 메모리 사용량 | 장점 |
|------|--------------|------|
| 일반 구조체 (struct) | **패딩 포함** 크기 증가 | 코드 가독성 유지 |
| union을 이용한 정렬 | **최적화된 크기** | 메모리 절약, 빠른 접근 |
| union + 더 큰 정렬 기준 (배열) | **CPU 접근 최적화** | 바이트 단위 조작 용이 |

union을 활용하면 **불필요한 패딩을 줄이고**, CPU의 정렬 기준을 맞출 수 있어 **메모리 절약 및 성능 최적화**가 가능합니다.
