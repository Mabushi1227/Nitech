#include <stdio.h>

#define STACK_SIZE 50

struct Stack
{
    int array[STACK_SIZE];
    int pos;
};

struct Stack stack;

void push(int in);
int pop();
void add();

int main()
{
    stack.pos = 0;

    push(1);
    push(2);
    push(3);

    add();
    add();

    printf("%d\n",pop());
}

void push(int in)
{
    stack.array[stack.pos] = in;
    stack.pos++;
    //return 0;
}

int pop()
{
    if(stack.pos >= 0)
    {
        stack.pos--;
        int out = stack.array[stack.pos];
        return out;
    }
    else
    {
        return -1;
    }
}

void add()
{
    if(stack.pos > 1)
    {
        stack.array[stack.pos-2] = stack.array[stack.pos-2] + stack.array[stack.pos-1];
        stack.pos--;
        stack.array[stack.pos] = 0;
    }
}