---
layout : post
title : Embedded C 디자인 패턴
comments : true
categories : 
- C
tags : []
---
# Embedded C 디자인 패턴


## Finite State Machine (FSM): 
This pattern is used to organize code for systems that have a limited number of states and transitions between those states.

```c

typedef enum {
    STATE_A,
    STATE_B,
    STATE_C
} state_t;

state_t current_state = STATE_A;

void update_state(state_t new_state) {
    current_state = new_state;
}

void state_machine() {
    switch (current_state) {
        case STATE_A:
            // Do something
            if (condition) {
                update_state(STATE_B);
            }
            break;
        case STATE_B:
            // Do something else
            if (condition) {
                update_state(STATE_C);
            }
            break;
        case STATE_C:
            // Do something different
            if (condition) {
                update_state(STATE_A);
            }
            break;
    }
}

```
## Command-Query Separation (CQS):
This pattern separates the code that changes the state of a system from the code that reads the state of a system, making the code more readable and maintainable

```c

bool is_alarm_enabled = false;

void set_alarm(bool enabled) {
    is_alarm_enabled = enabled;
}

bool get_alarm() {
    return is_alarm_enabled;
}
```
## Singleton 
프로그램 전체에서 오직 하나의 인스턴스만을 생성하도록 하는 패턴입니다.
```c
typedef struct {
    int value;
} singleton_t;

singleton_t *singleton_instance = NULL;

singleton_t *get_singleton() {
    if (singleton_instance == NULL) {
        singleton_instance = (singleton_t *)malloc(sizeof(singleton_t));
    }
    return singleton_instance;
}
```
## Template Method:
알고리즘의 구조를 정의하면서 하위 클래스에서 세부적인 구현을 결정하도록 하는 패턴입니다
```c
typedef struct {
    void (*init)();
    void (*run)();
    void (*cleanup)();
} algorithm_t;

void init() {
    // Do something
}

void run() {
    // Do something
}

void cleanup() {
    // Do something
}

algorithm_t algorithm = {
    init,
    run,
    cleanup
};
```

## Observer: 
객체 간의 일대다 관계를 정의하여 하나의 객체의 변화를 여러 객체에 알립니다.

```c
typedef struct observer_s observer_t;
struct observer_s {
    void (*notify)(observer_t*, int);
    observer_t* next;
};

typedef struct subject_s subject_t;
struct subject_s {
    observer_t* head;
    int value;
};

void subject_attach(subject_t* s, observer_t* o) {
    o->next = s->head;
    s->head = o;
}

void subject_set_value(subject_t* s, int value) {
    s->value = value;
    observer_t* o = s->head;
    while (o) {
        o->notify(o, value);
        o = o->next;
    }
}
```

## Factory Method: 
객체를 생성하는 공장 클래스를 정의하면서 객체의 생성 과정을 캡슐화하여 인터페이스를 통일시킵니다.

```c
typedef struct {
    void (*print)();
} object_t;

void print_a() {
    printf("I am object A\n");
}

void print_b() {
    printf("I am object B\n");
}

object_t* create_object(char type) {
    object_t* object = malloc(sizeof(object_t));
    if(type == 'A') {
        object->print = print_a;
    } else {
        object->print = print_b;
    }
    return object;
}
```



