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
This pattern ensures that a class has only one instance and provides a global point of access to that instance.
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
This pattern defines the skeleton of an algorithm in a base class, allowing subclasses to fill in the details.
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
This pattern allows objects to be notified when the state of other objects changes, without having to tightly couple the objects.

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
This pattern allows a class to delegate the creation of objects to its subclasses, providing a level of abstraction.

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


## Model-View-Controller (MVC): 
This pattern separates the code that defines the structure of a system (the model) from the code that defines the user interface (the view) and the code that handles user input (the controller).

```c

```
