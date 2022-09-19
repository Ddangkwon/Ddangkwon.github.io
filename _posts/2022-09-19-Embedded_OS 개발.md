---
layout : post
title : Embedded OS 개발
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---
# Embedded OS 개발 프로젝트

## 1장. 임베디드 운영체제

### 임베디드 운영체제와 펌웨어

 임베디드 운영체제는 임베디드 시스템에서 동작하는 펌웨어의 일종으로서 하드웨어 성능이 일정 수준으로 올라온 현재 임베디드 장치에도 임베디드 운영체제를 많이 사용하고 있다.

펌웨어란 임베디드 운영체제 유무에 상관없이 임베디드 시스템 용 전체 소프트웨어를 지칭한다.

임베디드 운영체제 역시 일반 운영체제와 마찬가지로 프로세스 관리, 저장장치 관리, 네트워킹 관리, 사용자 관리, 디바이스 드라이버 등을 포함한다.

여기서 디바이스 드라이버란 운영체제 안에서 하드웨어를 추상화(HAL)하는 계층을 말한다.

RTOS(RealTime Operating System)

운영체제 

## 3장. 기초 설정

### 리셋 벡터

ARM 코어에 전원이 들어가면 가장 먼저 수행하는 것은 리셋 벡터(reset vector)를 실행시킨다. 리셋 벡터란 0x00000000 번지 메모리 주소를 말하는 것으로 이곳에서 여러 하드웨어 세팅 등을 수행하면서 프로그램 실행을 위한 초기화 및 기초 세팅 작업을 수행한다.

## 4장. 부팅

실행 파일(ELF)는 메모리를 크게 세 가지로 나누어 사용한다.

.text 영역 : 코드가 있는 영역

.data 영역 : 초기화된 전역 변수가 있는 공간

.bss 영역 : 초기화되지 않은 전역 변수가 있는 공간 ⇒ 초기화되지 않은 전역 변수 이므로 파일에는 심벌과 크기만 들어있다.(변수가 실행 파일 메모리를 거의 잡아 먹지 않는다.)

데이터의 형태 : 동작 모드별 스택, 태스크 스택, 전역 변수, 동적 메모리 할당

데이터의 속성 : 성능 중시 데이터, 큰 공간이 필요한 데이터, 공유 데이터\

데이터의 형태와 속성에 따라 .data 영역에 할당할지, .bss 영역에 할당할지를 고민한다.

### 메모리 설계

### 익셉션 벡터 테이블(Exception Vector Table)

인터럽트 및 예외 처리를 위한 주소를 모아놓은 테이블을 말한다. 

ARM 에는 7가지 Exception, 7가지 동작 모드가  있다

Abort(ABT)

Fast Interrupt Request(FIQ)

Interrupt Request(IRQ)

Supervisor(SVC)

System(SYS)

Undefined(UND)

USER(USR)

ABT, FIQ, IRQ, SVC, UND 모드는 exception이 발생할 때 자동으로 변경되는 동작모드

SYS와 USR는 프로세서의 일반적인 동작 모드

| 예외 | 동작모드 |
| --- | --- |
| Prefetch Abort | ABT |
| Data Abort |  |
| FIQ | FIQ |
| IRQ | IRQ |
| Reset | SVC |
| SWI |  |
| Undefined | Undefined |
