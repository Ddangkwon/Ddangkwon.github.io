---
layout : post
title : Embedded C 프로그래밍
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---
# 스타트업(Startup) 코드란?

프로그램이 작동되기 위해서 필요한 준비 과정을 위한 코드로 여러 초기화 작업과 C에서 사용할 메모리(스택, 힙) 등을 할당하고 마지막에 main() 함수를 호출하여 프로그램을 동작하게 한다.


```
운영체제(OS)가 있는 경우의 main 호출 과정

1. Shell 상에서 프로그램 수행
2. fork로 새로운 프로세스 복사
3. 시스템 콜 함수 sys_execve() 호출
=> 사용자 모드에서 커널 모드로 전환
4. do_execve() => open_exec()로 파일 정보를 읽어 적합한 binary handler 실행
5. flush_old_exec()가 기본 프로세스 정보를 삭제하고 현재 프로세스를 current 로 설정
6. 새로운 프로세스에 사용할 메모리 레이아웃 설정
7. 동적 링커 메모리에 로딩
8. start_thread()=> elf  인터프리터 실행
9. sys_execve() 종료 => 커널 모드에서 사용자 모드로 전환
10. reschedule() => context switching 수행
11. _start_ 코드로 main 호출

```


```
운영체제(Non-OS)가 없는 경우의 main 호출 과정

프로그램이 작동되기 전 하드웨어의 초기화는 부트 코드에서, 임베디드 코드의 초기화는 스타트업 코드에서 처리한다

1. 모든 인터럽트 중지
2. 초기화된 데이터를 ROM to RAM 복사
3. 초기화되지 않은 데이터 영역 0으로 초기화
4. 스택을 위한 공간을 할당하고 초기화
5. 프로세서의 스택 포인터 초기화
6. 힙을 생성하고 초기화
7. 인터럽트 활성화
8. main() 함수 호출

세부 설명
1. 모든 인터럽트 중지
=> 스타트업 코드 실행 중에 인터럽트가 발생하여 ISR(Interrput Service Routine)으로 분기하면 해당 동작이 어떤 결과를 초래하는지 예측하기 어렵다
따라서 인터럽트나 워치독(Watchdog)을 Disable 시킨다

2. 초기화된 데이터를 ROM to RAM 복사
=> ROM에 있는 data segment를 RAM으로 복사한다
bss segment의 경우 0으로  초기화 한다

최종적으로 해당 과정들을 통해 임베디드 프로그램(C 프로그램) main()을 호출하고 스타트업 코드로 돌아오게 한다
그 다음코드는 레이블 0만 반복하여 메모리가 임의의 주소로 빠지는 일을 막는다 
```