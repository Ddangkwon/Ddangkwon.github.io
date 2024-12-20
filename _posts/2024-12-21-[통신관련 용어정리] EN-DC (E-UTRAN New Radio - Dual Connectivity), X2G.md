---
layout : post
title : 통신관련 용어정리 EN-DC (E-UTRAN New Radio - Dual Connectivity), X2G
comments : true
categories : 
- Telecommunication
tags : [Telecommunication]
---

# EN-DC (E-UTRAN New Radio - Dual Connectivity)


**EN-DC (E-UTRAN New Radio - Dual Connectivity)**는 LTE와 5G 네트워크를 동시에 활용하는 기술로, 사용자 단말(UE)이 LTE와 5G NR(New Radio) 기지국을 동시에 연결해 데이터 전송 속도와 네트워크 효율성을 높이는 방식이다. 이 기술은 3GPP Rel-15에서 처음 도입되었고, 5G 초기 단계의 상용화에 중요한 역할을 한다.

---

## **EN-DC의 주요 개념**

1. **Dual Connectivity**:
   - 단말이 LTE와 5G NR을 동시에 연결해 데이터를 전송한다.
   - LTE는 기본 연결(PCC, Primary Cell)을 제공하고, 5G NR은 추가적인 데이터 전송(SCC, Secondary Cell)을 처리한다.
   - 이를 통해 두 네트워크의 장점을 결합한다.

2. **LTE의 역할**:
   - LTE는 제어 신호(Control Plane)를 담당하며, 안정적이고 광범위한 커버리지를 제공한다.
   - 5G NR 기지국이 없는 지역에서도 LTE를 통해 기본 연결을 유지할 수 있다.

3. **5G NR의 역할**:
   - NR은 사용자 데이터(User Plane)를 처리하며, 초고속 데이터 전송과 낮은 지연 시간을 제공한다.
   - LTE의 보완 역할을 하며, 대역폭 확장을 통해 전체 네트워크 성능을 극대화한다.

---

## **EN-DC의 동작 원리**

1. **Primary Cell과 Secondary Cell**:
   - EN-DC는 단말이 LTE 기지국(eNB)과 5G NR 기지국(gNB)에 동시 연결되도록 한다.
   - LTE eNB는 Primary Cell(PCell)로, NR gNB는 Secondary Cell(SCell)로 작동한다.

2. **Control Plane과 User Plane 분리**:
   - LTE eNB는 네트워크와의 제어 신호를 관리하며, 안정적인 연결을 유지한다.
   - 5G NR gNB는 데이터 전송 용량을 증가시키는 데 초점을 맞춘다.

3. **Split Bearer**:
   - 데이터 전송은 LTE와 NR 간에 분할(Split Bearer)되어 이루어진다.
   - 동일한 데이터 세션이 LTE와 NR을 통해 동시에 전송되어 대역폭을 최대로 활용한다.

---

## **EN-DC의 장점**

1. **고속 데이터 전송**:
   - LTE와 5G NR을 동시에 사용해 더 넓은 대역폭을 제공하므로, 데이터 전송 속도가 크게 증가한다.

2. **기존 LTE 네트워크 활용**:
   - 기존 LTE 인프라를 활용하기 때문에 5G 네트워크 구축 비용을 절감할 수 있다.

3. **유연한 네트워크 전환**:
   - 단말은 5G NR 커버리지가 부족한 지역에서도 LTE를 통해 연결을 유지할 수 있어 안정성이 높다.

4. **점진적인 5G 도입**:
   - EN-DC를 통해 LTE와 5G를 동시에 사용할 수 있어 5G 네트워크의 점진적인 도입이 가능하다.

---

## **EN-DC의 적용 사례**

1. **초고속 모바일 브로드밴드(eMBB)**:
   - UHD 스트리밍, 온라인 게임, AR/VR 같은 대역폭을 많이 요구하는 서비스에 적합하다.

2. **산업용 IoT**:
   - 실시간 데이터 전송이 필요한 스마트 공장 및 IoT 환경에서 EN-DC를 통해 낮은 지연과 높은 데이터 전송량을 보장한다.

3. **자율주행**:
   - 자율주행 차량의 실시간 센서 데이터와 맵 데이터를 빠르게 처리하는 데 이상적이다.

---

## **EN-DC 기술 구성**

1. **eNB (LTE 기지국)**:
   - 네트워크의 제어 신호를 처리하며, EN-DC의 기반이 된다.

2. **gNB (5G NR 기지국)**:
   - 사용자 데이터 전송을 처리하며, 고속 데이터 전송 및 대역폭 확장을 담당한다.

3. **X2 인터페이스**:
   - LTE eNB와 5G gNB 간의 데이터 전송 경로를 제공하며, EN-DC의 핵심 구성 요소이다.

---

# X2G (X2 Gateway)

**X2G**는 5G 네트워크와 관련된 인터페이스 중 하나로, 기존 LTE 네트워크와 5G 네트워크 사이의 연결과 데이터 전송을 지원하는 기술이다. X2G는 **X2 Gateway**의 약자로, LTE와 5G 기지국 간의 데이터 전송을 원활하게 만드는 역할을 한다. 

---

## **X2G의 주요 역할**

1. **LTE와 5G 간의 인터페이스**:
   - X2G는 LTE 기지국(eNB)과 5G 기지국(gNB) 간의 연결을 지원한다.
   - EN-DC(E-UTRAN New Radio Dual Connectivity) 구조에서 필수적인 요소로, 데이터 및 제어 신호를 LTE와 5G 사이에 전달한다.

2. **데이터 전송 경로 관리**:
   - X2G는 사용자가 LTE와 5G를 동시에 사용할 때, 데이터가 두 네트워크를 통해 효율적으로 전송되도록 경로를 관리한다.
   - Split Bearer(데이터 분할 전송)와 같은 기능을 지원하여, 대역폭을 최적화하고 전송 속도를 높인다.

3. **호환성 유지**:
   - X2G는 기존 LTE 인프라와 5G 인프라 간의 호환성을 유지하면서, 두 기술이 통합적으로 작동할 수 있도록 지원한다.

---

## **X2G의 동작 원리**

- **LTE 기지국(eNB)**과 **5G 기지국(gNB)**은 X2G 인터페이스를 통해 연결된다.
- 데이터 트래픽은 X2G를 통해 분배되며, 사용자가 5G 커버리지 영역에 있지 않을 경우 LTE로 데이터를 전송한다.
- 사용자가 5G 커버리지 내에 있으면, 5G NR을 통해 데이터 전송을 우선 처리한다.

---

## **X2G의 장점**

1. **네트워크 전환의 원활함**:
   - 사용자가 LTE와 5G 영역을 오갈 때도 끊김 없는 연결을 제공한다.
   
2. **효율적인 자원 활용**:
   - LTE와 5G의 대역폭을 통합적으로 활용하여 네트워크 효율성을 높인다.

3. **기존 인프라 활용**:
   - 네트워크 사업자가 기존 LTE 네트워크를 계속 활용하면서 5G로 전환할 수 있는 가교 역할을 한다.

---

## **X2G의 적용 사례**

1. **EN-DC 지원**:
   - X2G는 EN-DC 환경에서 LTE와 5G 간의 데이터 분배와 관리를 수행한다.

2. **네트워크 확장**:
   - 초기 5G 구축 단계에서, LTE 인프라를 기반으로 5G 서비스를 제공하는 데 활용된다.

3. **자율주행 및 IoT**:
   - 안정적인 네트워크 전환이 필요한 자율주행 차량이나 산업 IoT에서 중요한 역할을 한다.

---