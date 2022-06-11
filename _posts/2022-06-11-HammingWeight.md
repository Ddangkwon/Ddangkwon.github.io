# 해밍 가중치(Hamming Weight)

길이가 모두 0인 Hamming Distance 와 동일

```C
/* Divide and Conquer */
 int OneBitCnt(int data){
   data = (data & 0x55555555) + ((data >> 1) & 0x55555555); //인접한 1비트의 분할정복
   data = (data & 0x33333333) + ((data >> 2) & 0x33333333); //인접한 2비트의 분할정복
   data = (data & 0x0f0f0f0f) + ((data >> 4) & 0x0f0f0f0f); //인접한 4비트의 분할정복
   data = (data & 0x00ff00ff) + ((data >> 8) & 0x00ff00ff); //인접한 8비트의 분할정복
   data = (data & 0x0000ffff) + ((data >> 16) & 0x0000ffff);  //인접한 16비트의 분할정복
   return data;
}
```C

1. 모든 odd bit의 1값 탐색
(data & 0x55555555) 
2. 모든 even bit의 1값 탐새
((data >> 1) & 0x55555555)
3. 결과는 각 2비트씩 쪼개서 봤을 때 1의 개수를 이진수로 표현한 것과 같다. 이를 모두 더하면 전체 비트의 1의 개수와 같다
4. 모든 하위 2비트 1값 탐색
(data & 0x33333333)
5. 모든 상위 2비트 1값 탐색
((data >> 2) & 0x33333333)
6. 결과는 각 4비트씩 쪼개서 봤을 때 1의 개수를 이진수로 표현한 것과 같다. 이를 모두 더하면 전체 비트의 1의 개수와 같다

...

반복했을 때 최종적으로 

data = (data & 0x0000ffff) + ((data >> 16) & 0x0000ffff); 

내용까지 수행하면 전체 비트의 1의 개수를 구할 수 있게 된다