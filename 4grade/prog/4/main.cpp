#include<iostream>
#include"stack.hpp"

int main()
{
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout<<"要素数:" << stack.fill() <<std::endl;

    stack.add();
    stack.add();

    printf("%d\n",stack.pop());
}