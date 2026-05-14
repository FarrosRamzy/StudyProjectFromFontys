#include "MyQueue.hpp"

MyQueue::MyQueue(int item_size) : item_size(item_size)
{
    stack_in = new MyStack(item_size);
    stack_out = new MyStack(item_size);
}

MyQueue::~MyQueue()
{
    delete stack_in;
    delete stack_out;
}

int MyQueue::enqueue(void *obj)
{
    if (obj == nullptr)
    {
        return -1;
    }

    int push_status = stack_in->pushObject(obj);

    return (push_status == 0) ? 0 : -1;
}

int MyQueue::dequeue(void *obj)
{
    int mystack_out_element;
    int mystack_in_element;
    int mystack_pop_status = -1;
    int mystack_push_status;

    void *my_temp_obj = nullptr;

    if (obj == nullptr)
    {
        return -1;
    }

    mystack_out_element = stack_out->numberOfElements();

    if (mystack_out_element == 0)
    {
        mystack_in_element = stack_in->numberOfElements();
        my_temp_obj = new char[item_size];

        while (mystack_in_element > 0)
        {
            if (my_temp_obj == nullptr)
            {
                delete[] reinterpret_cast<char *>(my_temp_obj);
                return -1;
            }

            mystack_pop_status = stack_in->popObject(my_temp_obj);
            if (mystack_pop_status == 0)
            {
                mystack_push_status = stack_out->pushObject(my_temp_obj);
                if (mystack_push_status != 0)
                {
                    delete[] reinterpret_cast<char *>(my_temp_obj);
                    return -1;
                }
            }
            else
            {
                delete[] reinterpret_cast<char *>(my_temp_obj);
                return -1;
            }
            mystack_in_element = stack_in->numberOfElements();
        }
    }

    if (mystack_pop_status == 0)
    {
        mystack_pop_status = stack_out->popObject(obj);
        if (mystack_pop_status != 0)
        {
            delete[] reinterpret_cast<char *>(my_temp_obj);
            return -1;
        }
    }

    if (my_temp_obj != nullptr)
    {
        delete[] reinterpret_cast<char *>(my_temp_obj);
        /* code */
    }

    return 0;
}