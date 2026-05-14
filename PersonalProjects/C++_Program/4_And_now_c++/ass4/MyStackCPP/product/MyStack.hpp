#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

class MyStack
{
private:
    struct StackObject
    {
        void *obj;
        StackObject *next;
        StackObject(): obj(nullptr), next(nullptr) {};
        ~StackObject(){delete[] static_cast<char*>(obj);};
    };

    StackObject *stack;
    size_t objsize;
    int numelem;

public:
    MyStack(size_t);
    ~MyStack();

    int pushObject(void *);
    int popObject(void *);
    int numberOfElements() const;
};