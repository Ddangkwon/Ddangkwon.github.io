---
layout : post
title : Algorithm_Hash
comments : true
categories : 
- CodingTest
tags : [CodingTest, Algorithm]
---

# Algorithm_Hash


**Hash(해시)** 는 어떤 데이터를 **고정된 크기의 숫자 값으로 변환**하는 방법이다.  
예를 들어 문자열 "apple" → 1234 처럼 바꾸는 함수가 **Hash Function(해시 함수)** 이다.

이 숫자를 **배열의 인덱스**처럼 사용하면 데이터를 빠르게 찾을 수 있다.  
이 개념을 이용한 자료구조가 **Hash Table(해시 테이블)** 이다.

---

# Hash Table 기본 구조

Hash Table은 **Key → Value** 형태로 데이터를 저장한다.  
1. **Hash Function**으로 Key를 숫자로 변환  
2. **Bucket 배열**의 인덱스로 사용  
3. 같은 인덱스에 여러 데이터가 들어올 경우 **충돌(Collision)** 이 발생  

충돌은 보통 **체이닝(Chaining)** 방식으로 해결한다.  
(같은 인덱스에 여러 값을 **리스트로 저장**)

---

# 간단한 예시로 보는 Hash Function

```cpp
#include <iostream>
#include <string>
using namespace std;

// 간단한 문자열 해시 함수
int simpleHash(const string& key, int tableSize) {
    int hashValue = 0;
    for (char c : key)
        hashValue += c; // 문자 아스키값의 합
    return hashValue % tableSize; // 테이블 크기로 나눈 나머지
}

int main() {
    cout << "apple → " << simpleHash("apple", 10) << "\n";
    cout << "banana → " << simpleHash("banana", 10) << "\n";
    cout << "peach → " << simpleHash("peach", 10) << "\n";
}
```

**출력 예시**
```
apple → 0
banana → 9
peach → 3
```

문자열을 숫자로 바꿔서 테이블 인덱스로 쓰는 구조이다.

---

# 간단한 Hash Table 구현

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// 문자열 해시 함수
int hashFunc(const string& key, int tableSize) {
    int hashValue = 0;
    for (char c : key)
        hashValue = (hashValue + c) % tableSize;
    return hashValue;
}

class HashTable {
    vector<list<pair<string, string>>> table; // 체이닝 구조
    int size;
public:
    HashTable(int s) : size(s) {
        table.resize(s);
    }

    void insert(const string& key, const string& value) {
        int idx = hashFunc(key, size);
        for (auto& kv : table[idx]) {
            if (kv.first == key) {
                kv.second = value; // 업데이트
                return;
            }
        }
        table[idx].push_back({key, value});
    }

    string find(const string& key) {
        int idx = hashFunc(key, size);
        for (auto& kv : table[idx]) {
            if (kv.first == key)
                return kv.second;
        }
        return "(not found)";
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            for (auto& kv : table[i])
                cout << "[" << kv.first << ":" << kv.second << "] ";
            cout << "\n";
        }
    }
};

int main() {
    HashTable ht(5);
    ht.insert("apple", "red");
    ht.insert("banana", "yellow");
    ht.insert("grape", "purple");
    ht.insert("melon", "green");

    ht.print();

    cout << "find(banana): " << ht.find("banana") << "\n";
    cout << "find(peach): " << ht.find("peach") << "\n";
}
```

**출력 예시**
```
0: [banana:yellow] 
1: [melon:green] 
2: 
3: [grape:purple] 
4: [apple:red] 
find(banana): yellow
find(peach): (not found)
```

---

# 핵심 요약

| 개념 | 설명 |
|------|------|
| Hash Function | 데이터를 숫자로 바꾸는 함수 |
| Collision | 서로 다른 키가 같은 인덱스로 해시될 때 |
| Chaining | 같은 인덱스에 리스트로 여러 값을 저장 |
| Load Factor | 저장된 개수 / 테이블 크기 |
| Rehash | 테이블이 가득 차면 크기를 늘려 다시 해시 |

---

# 정리

- Hash Table은 평균 **O(1)** 속도로 탐색이 가능하다.  
- 좋은 해시 함수일수록 **충돌이 적고 빠르다.**
- 해시 테이블 크기는 소수로 잡야야 충돌이 일어날 가능성이 적어진다.
- C++에서는 직접 구현할 필요 없이 **unordered_map** 을 많이 사용한다.

```cpp
#include <unordered_map>
unordered_map<string, string> color;
color["apple"] = "red";
cout << color["apple"];
```

Hash의 원리를 이해하고 직접 구현해보면,  
unordered_map의 내부 구조를 쉽게 이해할 수 있다.
