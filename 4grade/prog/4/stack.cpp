#include"stack.hpp"

Stack::Stack()
{
    pos = 0;
}

void Stack::push(int in)
{
    array[pos] = in;
    pos++;
    //return 0;
}

int Stack::pop()
{
    if(pos >= 0)
    {
        pos--;
        int out = array[pos];
        return out;
    }
    else
    {
        return -1;
    }
}

void Stack::add()
{
    if(pos > 1)
    {
        array[pos-2] = array[pos-2] + array[pos-1];
        pos--;
        array[pos] = 0;
    }
}

int Stack::fill()
{
    return pos;
}