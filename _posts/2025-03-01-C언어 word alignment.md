---
layout : post
title : C언어 word alignment
comments : true
categories : 
- C
tags : [C]
---

# C 언어 Union을 활용한 Word Alignment

## 1. Word Alignment란?

Word Alignment(워드 정렬)는 메모리에서 데이터를 효과적으로 정렬하여 접근 속도를 향상시키는 기법입니다. CPU는 특정 주소에서 데이터를 읽고 쓸 때 정렬된 주소(예: 4바이트 정렬, 8바이트 정렬)에서 수행하는 것이 더 효율적입니다. 

정렬되지 않은 데이터는 추가적인 연산이 필요할 수 있어 성능 저하를 유발할 수 있습니다.

## 2. C 언어에서 Union을 활용한 Word Alignment

C 언어의 `union`을 사용하면 메모리를 공유하여 정렬을 맞추는 데 유용하게 활용할 수 있습니다. 이를 통해 구조체 내에서 자동으로 정렬을 조정할 수 있습니다.

### 2.1 예제 코드

```c
#include <stdio.h>
#include <stdint.h>

// Word Alignment를 맞추기 위한 Union 활용
union WordAligned {
    uint32_t aligned; // 4바이트 정렬
    struct {
        uint16_t lower;
        uint16_t upper;
    } parts;
};

int main() {
    union WordAligned data;
    
    data.aligned = 0x12345678;
    
    printf("Full word: 0x%X\n", data.aligned);
    printf("Lower 16 bits: 0x%X\n", data.parts.lower);
    printf("Upper 16 bits: 0x%X\n", data.parts.upper);
    
    return 0;
}
```

### 2.2 코드 설명

- `union WordAligned`는 4바이트 정렬을 유지하면서, 내부적으로 16비트(lower, upper) 단위로 접근할 수 있도록 설계되었습니다.
- `aligned` 변수는 32비트(4바이트) 정렬을 유지합니다.
- `parts` 구조체를 사용하여 하위 16비트(`lower`)와 상위 16비트(`upper`)를 접근할 수 있습니다.
- 이 방식은 Word Alignment를 유지하면서도 개별 바이트 조작이 필요한 경우 유용합니다.

## 3. Union을 활용한 패딩 문제 해결

일반적으로 구조체를 사용할 때, 정렬을 맞추기 위해 추가적인 패딩이 발생할 수 있습니다. 하지만 `union`을 활용하면 메모리를 공유하여 불필요한 패딩을 줄일 수 있습니다.

### 예제 코드

```c
#include <stdio.h>
#include <stdint.h>

// 패딩을 줄이기 위한 Union 활용
union PackedData {
    uint32_t value;  // 4바이트 정렬 유지
    struct {
        uint8_t byte1;
        uint8_t byte2;
        uint8_t byte3;
        uint8_t byte4;
    } bytes;
};

int main() {
    union PackedData data;
    data.value = 0xAABBCCDD;

    printf("Byte 1: 0x%X\n", data.bytes.byte1);
    printf("Byte 2: 0x%X\n", data.bytes.byte2);
    printf("Byte 3: 0x%X\n", data.bytes.byte3);
    printf("Byte 4: 0x%X\n", data.bytes.byte4);

    return 0;
}
```

### 코드 설명
- `union PackedData`는 4바이트 정렬을 유지하면서도 바이트 단위로 접근할 수 있도록 합니다.
- 이를 통해 바이트 단위로 데이터를 조작하면서도 Word Alignment를 유지할 수 있습니다.

## 4. 결론

C 언어에서 `union`을 활용하면 Word Alignment를 유지하면서도 메모리 접근을 유연하게 할 수 있습니다. 이를 통해 데이터 정렬을 효율적으로 관리하고, 불필요한 패딩을 줄이며, 메모리 공간을 절약할 수 있습니다.

이러한 기법은 시스템 프로그래밍, 네트워크 패킷 처리, 임베디드 시스템에서 유용하게 활용됩니다.
