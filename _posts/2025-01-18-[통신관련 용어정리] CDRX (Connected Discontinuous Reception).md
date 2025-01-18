---
layout : post
title : CDRX (Connected Discontinuous Reception)
comments : true
categories : 
- Telecommunication
tags : [Telecommunication]
---

# CDRX (Connected Discontinuous Reception)

## 1. CDRX 정의
CDRX(Connected Discontinuous Reception)는 모바일 통신 시스템에서 전력 효율성과 데이터 연결 성능을 동시에 최적화하기 위해 사용되는 기술입니다. 
CDRX는 **RRC_CONNECTED 상태**에서 UE(User Equipment)가 데이터를 간헐적으로 수신하도록 함으로써 배터리 소모를 줄이는 동시에, 네트워크와의 연결 상태를 유지합니다. 이 기술은 LTE와 5G NR 네트워크에서 널리 사용되며, 주로 스마트폰과 IoT 기기에서 채택됩니다.

---

## 2. CDRX 작동 원리
CDRX는 UE가 활성 상태와 비활성 상태를 반복적으로 전환하도록 설계되었습니다. 

1. **On-duration Timer**:
   - UE가 활성 상태로 깨어나 데이터를 수신할 준비를 하는 시간.
   - 이 기간 동안 네트워크가 데이터를 전송하면 UE는 지속적으로 깨어 있는 상태를 유지합니다.

2. **Inactive Period**:
   - 데이터 전송이 종료되면 UE는 비활성 상태로 전환하여 배터리 소모를 줄입니다.

3. **DRX Cycle**:
   - On-duration과 Inactive Period를 포함하는 주기적인 반복 구조.
   - DRX Cycle의 길이는 네트워크 설정 및 데이터 트래픽 요구에 따라 조정됩니다.

---

## 3. Idle DRX와 Connected DRX

CDRX와 관련된 주요 개념 중 하나는 DRX가 **RRC 상태**에 따라 다르게 작동한다는 점입니다. 
DRX는 크게 **Idle DRX**와 **Connected DRX**로 나뉘며, UE의 전력 관리 및 데이터 연결 방식에 차이가 있습니다.

### 3.1 Idle DRX
Idle DRX는 UE가 네트워크와 **RRC_IDLE 상태**에 있을 때 동작합니다.

#### 특징
- **RRC 상태**: RRC_IDLE
- **작동 방식**:
  - UE는 특정 시간(Paging Occasion, PO)에만 깨어나 네트워크의 Paging 메시지를 확인합니다.
  - 데이터 요청이 없으면 다시 절전 상태로 전환됩니다.
- **목적**:
  - 배터리 소모를 최소화하며 네트워크에서 UE를 호출할 수 있도록 보장.

#### Idle DRX 주기
- DRX 주기는 상대적으로 길게 설정되어 전력 소모를 줄입니다.
- 일반적으로 수 초에서 수 분 단위의 주기를 가집니다.

#### 주요 응용 사례
- 스마트폰 대기 상태에서 전화 수신.
- IoT 기기(NB-IoT, LTE-M)에서 긴 배터리 수명을 요구하는 환경.

---

### 3.2 Connected DRX
Connected DRX는 UE가 네트워크와 **RRC_CONNECTED 상태**에 있을 때 동작합니다.

#### 특징
- **RRC 상태**: RRC_CONNECTED
- **작동 방식**:
  - UE는 On-duration Timer 동안 주기적으로 깨어나 데이터를 확인합니다.
  - 데이터가 없으면 절전 모드로 전환하고, 다음 DRX Cycle까지 대기합니다.
  - 데이터 전송이 발생하면 On-duration Timer가 연장되며, UE는 활성 상태를 유지합니다.
- **목적**:
  - 데이터 연결 성능을 유지하면서도 배터리 소모를 줄이는 균형 제공.

#### Connected DRX 주기
- 주기는 Idle DRX보다 짧아 지연 시간이 최소화됩니다.
- 일반적으로 수 밀리초에서 수 초 단위로 설정됩니다.

#### 주요 응용 사례
- VoLTE, 비디오 스트리밍, 실시간 애플리케이션.
- 대기 시간 감소가 중요한 서비스.

---

## 4. Idle DRX와 Connected DRX의 비교

| **항목**              | **Idle DRX**                           | **Connected DRX**                        |
|-----------------------|----------------------------------------|------------------------------------------|
| **RRC 상태**          | RRC_IDLE                              | RRC_CONNECTED                           |
| **주요 목적**         | 배터리 소모 최소화                    | 배터리 절약과 네트워크 연결 성능 균형    |
| **데이터 연결 상태**   | 데이터 연결 없음                      | 네트워크와 지속 연결                    |
| **DRX 주기 길이**     | 길게 설정 가능 (수 초~수 분)           | 짧게 설정 (수 밀리초~수 초)             |
| **데이터 처리**       | Paging 메시지 확인 후 연결 수립        | 주기적으로 깨어나 데이터 확인 및 처리   |
| **응용 사례**         | 전화 대기 상태, IoT 기기              | 스트리밍, VoLTE, 실시간 애플리케이션     |
| **Paging 메시지**     | PO에서만 수신                         | PO 개념 대신 On-duration Timer 사용      |

---

## 5. Idle DRX와 Connected DRX의 협력
Idle DRX와 Connected DRX는 UE의 상태에 따라 전환되며, 전력 절약과 데이터 연결 성능 간의 최적화를 제공합니다.

### 전환 메커니즘
1. **Idle DRX → Connected DRX**:
   - UE가 Idle 상태에서 네트워크의 Paging 메시지를 수신하면 RRC_CONNECTED 상태로 전환되어 Connected DRX로 작동합니다.

2. **Connected DRX → Idle DRX**:
   - 데이터 전송이 종료되고 일정 시간 동안 추가 트래픽이 없으면 RRC_IDLE 상태로 전환되어 Idle DRX를 시작합니다.

---

## 6. 요약
- **CDRX**는 RRC_CONNECTED 상태에서 UE의 전력 효율을 최적화하며, 데이터를 간헐적으로 수신하는 메커니즘입니다.
- **Idle DRX**와 **Connected DRX**는 DRX 작동 상태를 구분하며, 각각 배터리 절약과 데이터 연결 성능에 초점을 맞춥니다.
- 이러한 DRX 메커니즘은 모바일 및 IoT 환경에서 전력 효율성과 연결 성능을 동시에 보장하기 위한 핵심 기술로 작동합니다.
