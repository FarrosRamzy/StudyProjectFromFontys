#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "MyStack.hpp"

class MyQueue
{
private:
    MyStack *stack_in;
    MyStack *stack_out;
    int item_size;
public:
    MyQueue(int);
    ~MyQueue();

    int enqueue(void*);
    int dequeue(void*);
};
