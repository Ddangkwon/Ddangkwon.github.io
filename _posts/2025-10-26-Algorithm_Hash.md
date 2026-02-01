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


# C++ unordered_map 활용

C++에서는 직접 Hash Table을 구현하기보다 unordered_map을 많이 사용한다.  
평균적으로 탐색, 삽입, 삭제가 **O(1)** 이지만, 해시 충돌이 극단적으로 많으면 최악 **O(N)** 이 될 수 있다.

---

## 기본 예시

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, string> color;

    color["apple"] = "red";
    color["banana"] = "yellow";

    cout << color["apple"] << "\n";
    return 0;
}
```

---

## 자주 나오는 실수 1: operator[]가 원소를 만든다

operator[]는 키가 없으면 기본값으로 새 원소를 생성한다.  
존재 여부만 확인하고 싶으면 find를 쓰는 편이 안전하다.

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;

    // 여기서 "ghost" 키가 없는데도 생성되고 값 0이 들어간다
    cout << m["ghost"] << "\n";

    // 존재 여부 확인은 find가 더 안전하다
    if (m.find("ghost2") == m.end()) {
        cout << "ghost2 not found\n";
    }

    return 0;
}
```

---

## 빈도 카운팅 패턴 (코테 최다 출현)

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    vector<int> a = {1, 3, 3, 7, 1, 3};

    unordered_map<int, int> cnt;
    for (int x : a) cnt[x]++;

    cout << "count(1) = " << cnt[1] << "\n";
    cout << "count(3) = " << cnt[3] << "\n";
    cout << "count(7) = " << cnt[7] << "\n";
    return 0;
}
```

---

## 성능 팁: reserve와 max_load_factor

데이터가 많아지면 rehash가 반복되면서 시간 비용이 커질 수 있다.  
대략 원소 개수를 예측할 수 있으면 reserve로 미리 버킷을 준비하는 편이 유리하다.

```cpp
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    unordered_map<int, int> m;

    // 대략 200000개쯤 들어갈 예정이라면 미리 예약한다
    m.reserve(200000);

    // 충돌을 더 줄이고 싶다면 로드 팩터도 낮출 수 있다
    m.max_load_factor(0.7f);

    for (int i = 0; i < 200000; i++) m[i] = i;

    cout << m[199999] << "\n";
    return 0;
}
```

---

## 커스텀 키: pair를 키로 쓰는 방법

unordered_map은 기본적으로 pair에 대한 해시가 없다.  
pair<int,int> 같은 키를 쓰려면 해시 함수를 직접 제공해야 한다.

```cpp
#include <iostream>
#include <unordered_map>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // 흔히 쓰는 결합 방식 중 하나이다
        // (충돌을 완전히 막는 것은 아니고 분산을 좋게 만들기 위함이다)
        size_t h1 = (size_t)p.first;
        size_t h2 = (size_t)p.second;
        return h1 * 1315423911u + h2;
    }
};

int main() {
    unordered_map<pair<int, int>, int, PairHash> mp;

    mp[{1, 2}] = 10;
    mp[{3, 4}] = 20;

    cout << mp[{1, 2}] << "\n";
    return 0;
}
```


# unordered_map STL API 정리

unordered_map에서 가장 많이 쓰는 API(Application Programming Interface)를 코테 관점으로 정리했다.  
아래 표의 복잡도는 평균 기준이며, 충돌이 극단적이면 최악 O(N)이 될 수 있다.

## 1) 생성, 상태 확인

| API | 의미 | 평균 복잡도 |
| --- | --- | --- |
| **unordered_map<K,V> m;** | 기본 생성이다. | - |
| **m.empty()** | 비어있는지 확인한다. | O(1) |
| **m.size()** | 원소 개수를 반환한다. | O(1) |
| **m.clear()** | 전부 삭제한다. | O(N) |

### 생성 예시

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;           // 기본 생성
    unordered_map<string, int> m2 = m;      // 복사
    unordered_map<string, int> m3(move(m2)); // 이동

    cout << m3.empty() << "\n";
    cout << m3.size() << "\n";
    return 0;
}
~~~

---

## 2) 조회 API

| API | 의미 | 특징 |
| --- | --- | --- |
| **m.find(key)** | key를 찾는다. | 없으면 end를 반환한다. |
| **m.count(key)** | key 존재 여부를 0 또는 1로 반환한다. | unordered_map은 키 중복이 없어서 0 또는 1이다. |
| **m.contains(key)** | key 존재 여부를 bool로 반환한다. | C++20부터 지원이다. |
| **m.at(key)** | key에 대응하는 값을 반환한다. | 없으면 예외가 발생한다. |
| **m[key]** | key에 대응하는 값을 참조로 반환한다. | 없으면 기본값 원소가 생성된다. |

### find, count 예시

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;
    m["a"] = 10;

    auto it = m.find("a");
    if (it != m.end()) cout << it->second << "\n";

    cout << m.count("a") << "\n";  // 1
    cout << m.count("b") << "\n";  // 0
    return 0;
}
~~~

### at vs operator[] 차이 예시

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;
    m["a"] = 10;

    // at는 없으면 예외가 난다
    try {
        cout << m.at("b") << "\n";
    } catch (...) {
        cout << "at: not found\n";
    }

    // operator[]는 없으면 원소를 만든다
    cout << m["b"] << "\n";     // 0 출력, 동시에 b가 생성된다
    cout << m.size() << "\n";   // 2
    return 0;
}
~~~

---

## 3) 삽입 API

| API | 의미 | 특징 |
| --- | --- | --- |
| **m.insert({k,v})** | (k,v) 삽입을 시도한다. | 이미 있으면 삽입되지 않는다. |
| **m.emplace(k,v)** | (k,v) 삽입을 시도한다. | 불필요한 복사를 줄이는 편이다. |
| **m.try_emplace(k, args...)** | 키가 없을 때만 value를 생성해 삽입한다. | value 생성 비용이 큰 경우 유리하다. |
| **m.insert_or_assign(k, v)** | 있으면 덮어쓰고 없으면 삽입한다. | 업데이트 패턴에 편하다. |

### insert의 반환값 활용

insert는 pair<iterator, bool>을 반환한다. bool은 실제 삽입 성공 여부이다.

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;

    auto r1 = m.insert({"a", 10});
    cout << r1.second << "\n"; // 1

    auto r2 = m.insert({"a", 20});
    cout << r2.second << "\n"; // 0, 이미 존재해서 실패

    cout << m["a"] << "\n";    // 10
    return 0;
}
~~~

### insert_or_assign 예시

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;

    m.insert_or_assign("a", 10);
    m.insert_or_assign("a", 30);

    cout << m["a"] << "\n"; // 30
    return 0;
}
~~~

---

## 4) 삭제 API

| API | 의미 | 특징 |
| --- | --- | --- |
| **m.erase(key)** | key를 삭제한다. | 삭제된 개수(0 또는 1)를 반환한다. |
| **m.erase(it)** | iterator 위치 원소를 삭제한다. | 반복 중 삭제에 유리하다. |

### 반복 중 삭제 패턴

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    m["c"] = 3;

    for (auto it = m.begin(); it != m.end(); ) {
        if (it->second % 2 == 1) it = m.erase(it); // 홀수 제거
        else ++it;
    }

    cout << m.size() << "\n";
    return 0;
}
~~~

---

## 5) 순회 API

| API | 의미 |
| --- | --- |
| **m.begin(), m.end()** | iterator로 전체 순회한다. |
| **m.cbegin(), m.cend()** | const iterator로 순회한다. |
| **range based for** | 전체 순회한다. |

unordered_map은 정렬된 순서를 보장하지 않는다. 출력 순서가 실행마다 달라질 수 있다.

~~~cpp
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, int> m;
    m["apple"] = 3;
    m["banana"] = 5;

    for (auto& kv : m) {
        cout << kv.first << " " << kv.second << "\n";
    }
    return 0;
}
~~~

---

## 6) 버킷, 로드 팩터 관련 API

hash 성능은 충돌과 관련이 있고, 충돌은 로드 팩터와 버킷 수에 영향을 받는다.

| API | 의미 |
| --- | --- |
| **m.bucket_count()** | 버킷 개수를 반환한다. |
| **m.bucket(key)** | key가 들어갈 버킷 번호를 반환한다. |
| **m.load_factor()** | 현재 로드 팩터를 반환한다. |
| **m.max_load_factor(x)** | 최대 로드 팩터를 설정한다. |
| **m.rehash(b)** | 최소 b개의 버킷을 확보하도록 재해시한다. |
| **m.reserve(n)** | n개 원소를 넣어도 재해시가 덜 나게 버킷을 준비한다. |