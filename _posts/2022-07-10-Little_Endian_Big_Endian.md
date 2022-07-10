---
layout : post
title : Little Endian, Big Endian
comments : true
categories : 
- Embedded Engineering
tags : [Embedded Engineering]
---

# Little Endian, Big Endian

모든 프로세서들은 Little Endian, Big Endian 둘 중 하나의 order 를 따른다.

Little Endian의 경우 상위 bit 주소(MSB)에 상위 주소를 저장한다.
Big Endian의 경우 하위 bit 주소(LSB)에 상위 주소를 저장한다.

대표적인 프로세서 중 하나인 ARM Procesor의 경우 Little Endian, Big Endian 모두를 지원하지만 default는 Little Endian이다.
