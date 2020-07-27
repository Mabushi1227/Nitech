#include <iostream> 
#include <vector> 
#include <algorithm>

int main()
{

    std::vector<int> v = {3, 3, 3, 4};
    //for_each関数
    std::for_each(v.begin(), v.end(), [](int i) {std::cout << i;}); 
    std::cout << std::endl;

    //for each文
    for (auto x:v) {
        std::cout << x;
    }
    std::cout << std::endl;

    //find_if関数
    auto result = std::find_if(v.begin(), v.end(), [](int x) { return x != 3; });
    if (result == v.end()) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found: " << *result << std::endl;
    }

    //関数を使わないfind_if
    bool find = false;
    int i = 0; 
    do
    {
        if(v[i] != 3)
        {
            find = true;
        }
        i++;
    } while (!find && i != v.size());


    if(find)
    {
        std::cout << "found: " << i << std::endl;
    }
    else
    {
        std::cout << "not found" << std::endl;
    }
    
}