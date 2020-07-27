#include<iostream>

template<typename T>

//テンプレート、大きい方を返す関数
T max(T value1, T value2)
{
    if(value1 >= value2)
    {
        return value1;
    }
    else
    {
        return value2;
    }
}

int main()
{
    //intテスト
    int n1 = 1;
    int n2 = 2;

    std::cout << max(n1,n2) << std::endl;

    //floatテスト
    float f1 = 1.414;
    float f2 = 1.732;

    std::cout << max(f1,f2) << std::endl;

    //doubleテスト
    double d1 = 3.14;
    double d2 = 2.72;

    std::cout << max(d1,d2) << std::endl;
}