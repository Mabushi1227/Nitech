#include <iostream>
#include <vector>
#include <functional>

//加算
auto add = [](int x, int y){
    return x+y;
};

//Aをn回出力するラムダ式
auto f = [](int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << "A";
    }
    std::cout << std::endl;
};

int main() 
{
    int x = 8;
    int y = 11;

    std::cout << x << "+" << y  << "="<< add(x,y) << std::endl;

    f(8);
}