#include <iostream> 
#include <functional>

std::function<double(double)> nest(int n, std::function<double(double)> f)
{
    auto x = f;
    for (int i = 1; i < n; i++)
    {
        x = [=](double a) {return f(x(a));};
    }
    
    return x;
}


int main() {
    auto f3 = nest(3,[](double a){return a + 1/a;});
    //(1+1) -> (2+1/2) -> (2.5+ 1/2.5)
    std::cout << f3(1) << std::endl;

    std::cout << 2.5 + 1/2.5 << std::endl;
}