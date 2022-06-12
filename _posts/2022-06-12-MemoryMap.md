---
layout : post
title : Memory Map 에 관하여...
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---
# Memory Map 에 관하여...

## Symbol 이란?
Symbol은 Memory Map에서 Linker가 알아볼 수 있는 최소 단위를 말한다
Linker의 Linking 과정 이후에 자신만의 주소를 갖게되는 단위를 말한다

ELF File 형식에서 Linker에 의해 Symbol table을 두며 파일 단위의 관점에서 볼 때 참조되는 모든 Symbol의 이름과
주소가 들어있고, 외부에서 선언된 Symbol은 없어 해당 Object에서 Symbol table은 불완전하다

변수 관점에서는 Symbol은 Global 변수들을 나타낸다고 볼 수 있다.
=> 고유한 주소를 가지고 경우에 따라 다른 파일의 함수에서도 직접 접근하여 사용가능하다.


Symbol을 성질에 따라 ZI, RO, RW 로 구별한다.

ZI(Zero Initialization) : 초기 값이 0인 전역 변수(.bss)
RO(Read Only) : 수정이 불가능한 const 전역변수와 text인 code(.text, .constdata)
RW(Read Write) : 초기 값이 있는 전역 변수(.data)