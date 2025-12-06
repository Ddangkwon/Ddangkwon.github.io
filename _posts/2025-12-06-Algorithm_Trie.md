---
layout : post
title : Algorithm_Trie
comments : true
categories : 
- CodingTest
tags : [CodingTest, Trie]
---

# Algorithm_Trie

## 1. Trie 개요

Trie(트라이)는 문자열 집합을 다루기 위한 트리 기반 자료구조이다.  
특히 다음과 같은 상황에서 유용하다.

- 많은 문자열을 저장하고 **정확히 존재 여부를 빠르게 검사**해야 할 때
- 어떤 문자열이 **특정 접두사(prefix)** 를 가지는지 자주 물어볼 때
- 자동완성(auto-complete), 사전(dictionary), 검색어 추천과 같이 **접두사 기반 검색**이 핵심일 때

Trie의 핵심 아이디어는 문자열을 통째로 노드에 저장하지 않고,  
문자 하나하나를 **간선(edge)** 로 두고 루트에서부터 한 글자씩 내려가며 표현하는 것이다.


## 2. Trie 기본 구조

Trie는 보통 다음과 같은 정보를 가진다.

- 루트 노드 하나
- 각 노드는
  - 자식 포인터(또는 포인터 배열, map, unordered_map)
  - 해당 노드에서 문자열이 끝나는지를 표시하는 **is_end** 플래그
  - (선택) 그 아래 서브트리에 포함된 문자열 개수 등 부가 정보

예를 들어 문자열 집합이 다음과 같다고 하자.

- apple
- app
- bat

루트에서 시작해 a → p → p → l → e 와 같은 경로로 **apple** 을,  
a → p → p 지점에서 **app** 의 끝을 표시하고,  
b → a → t 경로로 **bat** 를 표현한다.


## 3. Trie의 핵심 연산

### 3.1 문자열 삽입(insert)

1. 현재 노드를 루트로 둔다.
2. 문자열의 각 문자 c에 대해
   - 현재 노드에 문자 c로 가는 자식이 없으면 새 노드를 만든다.
   - 자식 노드로 내려간다.
3. 문자열의 마지막 문자를 처리한 뒤, 해당 노드를 **is_end = true** 로 표시한다.

### 3.2 문자열 검색(exact search)

1. 현재 노드를 루트로 둔다.
2. 문자열의 각 문자 c에 대해
   - 현재 노드에 문자 c로 가는 자식이 없으면 문자열이 존재하지 않는다.
   - 있으면 자식 노드로 이동한다.
3. 마지막 문자까지 모두 이동한 후
   - 그 노드의 **is_end** 가 true이면 문자열이 존재한다고 본다.
   - false이면 해당 경로는 있지만 정확히 그 문자열은 없다(다른 문자열의 접두사).

### 3.3 접두사 검사(prefix check, starts_with)

1. 현재 노드를 루트로 둔다.
2. 접두사 문자열의 각 문자 c에 대해
   - 현재 노드에 문자 c로 가는 자식이 없으면 실패이다.
   - 있으면 자식 노드로 이동한다.
3. 모든 문자를 처리했다면 접두사를 가지는 문자열이 하나 이상 존재한다고 본다.
   - 추가로 노드에 **서브트리 문자열 개수** 를 저장해두면, 해당 접두사를 가진 문자열이 몇 개 있는지도 바로 알 수 있다.


## 4. 시간 복잡도와 공간 복잡도

- 문자열 길이를 L이라 두면
  - 삽입: O(L)
  - 검색: O(L)
  - 접두사 검사: O(L)
- 일반적인 해시 기반 자료구조는 평균 O(1)처럼 보이지만, 문자열 길이에 비례하는 해시 계산이 필요하므로 사실상 O(L)이다.  
  Trie의 강점은 **충돌이 없고, 접두사 처리에 특화**되어 있다는 점이다.

공간 복잡도는 다음에 의존한다.

- 저장할 문자열의 개수 N
- 각 문자열의 길이 L
- 사용 문자 집합의 크기(알파벳 수)

최악의 경우 O(N × L)의 노드가 필요할 수 있다.  
문자 집합이 알파벳 소문자 26개로 제한되면 각 노드마다 자식 포인터 26개를 고정 배열로 둘 수 있다.  
문자 집합이 크거나 유니코드 등을 다루면 map 또는 unordered_map을 쓰는 편이 공간 면에서 유리하다.


## 5. 구현 방식 비교

### 5.1 고정 크기 배열 사용 (예: 알파벳 소문자만)

각 노드에서 **children[26]** 형태로 포인터 배열을 두는 방식이다.

장점

- 매우 빠르다. 인덱스로 바로 접근하므로 O(1)
- 구현이 단순하다.

단점

- 문자 집합이 작을 때만 쓸 수 있다.
- 사용하지 않는 자식 포인터도 메모리를 차지한다.

### 5.2 map 또는 unordered_map 사용

각 노드에서 **문자 → 자식 노드 포인터**를 map 혹은 unordered_map으로 관리한다.

장점

- 문자 집합이 커도 낭비가 없다.
- 유니코드, 대소문자 혼용, 특수문자 등도 자연스럽게 처리 가능하다.

단점

- 배열 방식보다 느리다.
- 자료구조 오버헤드로 인해 메모리도 더 쓴다.


## 6. C++ 구현 예제 1: 알파벳 소문자(a~z)만 사용하는 Trie

```cpp
#include <iostream>
#include <string>
using namespace std;

struct TrieNode {
    TrieNode* child[26];
    bool is_end;

    TrieNode() {
        for (int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
        is_end = false;
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (idx < 0 || idx >= 26) {
                continue;
            }
            if (node->child[idx] == nullptr) {
                node->child[idx] = new TrieNode();
            }
            node = node->child[idx];
        }
        node->is_end = true;
    }

    bool search(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            int idx = c - 'a';
            if (idx < 0 || idx >= 26) {
                return false;
            }
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return node->is_end;
    }

    bool starts_with(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (idx < 0 || idx >= 26) {
                return false;
            }
            if (node->child[idx] == nullptr) {
                return false;
            }
            node = node->child[idx];
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;

    trie.insert("apple");
    trie.insert("app");

    cout << trie.search("apple") << " ";     
    cout << trie.search("app") << " ";       
    cout << trie.search("ap") << " ";        
    cout << trie.starts_with("ap") << " ";   
    cout << trie.starts_with("b") << " ";    

    return 0;
}
```


## 7. C++ 구현 예제 2: 임의의 문자 집합을 지원하는 Trie (unordered_map 사용)

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> child;
    bool is_end;

    TrieNode() {
        is_end = false;
    }
};

struct Trie {
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            if (node->child.find(c) == node->child.end()) {
                node->child[c] = new TrieNode();
            }
            node = node->child[c];
        }
        node->is_end = true;
    }

    bool search(const string& s) {
        TrieNode* node = root;
        for (char c : s) {
            auto it = node->child.find(c);
            if (it == node->child.end()) {
                return false;
            }
            node = it->second;
        }
        return node->is_end;
    }

    bool starts_with(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            auto it = node->child.find(c);
            if (it == node->child.end()) {
                return false;
            }
            node = it->second;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;

    trie.insert("Hello");
    trie.insert("Hell");
    trie.insert("Heap");

    cout << trie.search("Hello") << " ";     
    cout << trie.search("Hell") << " ";      
    cout << trie.search("He") << " ";        
    cout << trie.starts_with("He") << " ";   
    cout << trie.starts_with("Hi") << " ";   

    return 0;
}
```


## 8. Trie의 대표적인 응용

1. **자동완성 기능**  
   - 사용자가 몇 글자만 입력해도 해당 접두사로 시작하는 단어들을 빠르게 찾을 수 있다.
   - 각 노드에 서브트리 단어수를 저장하면, 인기 검색어 순위 같은 것도 쉽게 계산할 수 있다.

2. **사전(Dictionary) 구현**  
   - 단어 존재 여부를 빠르게 검사할 수 있다.
   - 단어 추가, 삭제, 접두사 기반 탐색 등에 유리하다.

3. **문자열 집합 문제**  
   - 예: N개의 문자열이 주어지고, M개의 쿼리 문자열 각각이 집합에 속하는지 확인하는 문제
   - 해시 대신 Trie를 쓰면 접두사 기반 추가 기능을 자연스럽게 붙일 수 있다.

4. **공통 접두사 관련 문제**  
   - 여러 문자열의 **최장 공통 접두사**를 구하는 문제 등에서 Trie를 사용할 수 있다.

5. **IP 주소, 도메인 이름 관리 등**  
   - 문자열 또는 특정 포맷의 토큰 시퀀스를 관리할 때 활용할 수 있다.


## 9. 구현 시 자주 하는 실수 정리

1. **인덱스 범위 체크 누락**  
   - 알파벳 소문자만 다루는 경우, 반드시 문자에서 'a'를 빼서 0~25 범위인지 확인해야 한다.

2. **동적 할당한 노드 해제 누락**  
   - 온라인 저지는 대개 프로그램 종료 시 메모리를 회수하지만, 실제 서비스 코드라면 소멸자에서 노드를 모두 해제해야 한다.

3. **문자 집합을 과소 또는 과대 가정**  
   - 실제 입력 문자열이 소문자만 온다는 보장이 없는 경우, 배열 기반 구현은 오류를 낸다.
   - 반대로, 문자 집합이 극도로 제한적이라면 굳이 map을 쓸 필요가 없다.

4. **접두사와 완전 일치 검색을 혼동**  
   - search 연산에서는 마지막 노드의 is_end를 반드시 체크해야 한다.
   - starts_with 연산은 is_end를 확인하지 않고, 경로가 존재하는지만 보면 된다.


## 10. 마무리

Trie는 문자열에 특화된 강력한 자료구조이다.  
특히 접두사 기반 연산이 잦은 문제에서는 해시나 정렬 기반 탐색보다 자연스럽고 직관적인 해결책을 제공한다.  
대신, 문자열 수와 길이가 매우 크면 메모리 사용량이 부담될 수 있으므로,  
입력 스펙에 따라 Trie, 해시, 정렬+이분 탐색 등을 적절히 선택하는 것이 중요하다.
