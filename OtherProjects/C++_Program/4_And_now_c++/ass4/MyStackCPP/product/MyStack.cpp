#include "MyStack.hpp"
/**
 * @brief Construct a new My Stack:: My Stack object
 * 
 * @param obj_size 
 */
MyStack::MyStack(size_t obj_size) : stack(nullptr), objsize(obj_size), numelem(0) {}

/**
 * @brief Destroy the My Stack:: My Stack object
 * 
 */
MyStack::~MyStack()
{
    while (stack != nullptr)
    {
        StackObject *temp_stack = stack;
        stack = stack->next;
        delete temp_stack;
    }
}

/**
 * @brief Pushes an object to the stack by the handler.
 * 
 * @param obj the object variable for the stack.
 * @return int 0 if success, -1 if fails.
 */
int MyStack::pushObject(void *obj)
{
    if (obj == nullptr)
    {
        return -1;
    }

    StackObject *new_element = new StackObject;

    if (new_element == nullptr)
    {
        return -1;
    }

    new_element->obj = new char[objsize];

    if (new_element->obj == nullptr)
    {
        delete new_element;
        return -1;
    }

    memcpy(new_element->obj, obj, objsize);

    new_element->next = stack;
    stack = new_element;

    numelem++;
    return 0;
}

/**
 * @brief Pops an object from the stack identified by the handler.
 * 
 * @param obj the object variable from the stack.
 * @return int 0 if success, -1 if fails.
 */
int MyStack::popObject(void *obj)
{
    if (stack == nullptr || obj == nullptr)
    {
        return -1;
    }

    StackObject *temp_stack = stack;
    StackObject *prev_stack = nullptr;

    while (temp_stack->next != nullptr)
    {
        prev_stack = temp_stack;
        temp_stack = temp_stack->next;
    }

    if (prev_stack != nullptr)
    {
        prev_stack->next = nullptr;
    }
    else
    {
        stack = nullptr;
    }

    memcpy(obj, temp_stack->obj, objsize);
    delete temp_stack;

    numelem--;
    return 0;
}

/**
 * @brief Giving the number of elements within the stack.
 * 
 * @return int number of element in a stack (-1 if no stack is available)
 */
int MyStack::numberOfElements() const
{
    if (stack != nullptr)
    {
        return numelem;
    }
    else
    {
        return -1;
    }
}