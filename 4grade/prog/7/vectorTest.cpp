#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstdlib>


int main() {
    //intテスト
    std::cout << "int" << std::endl;
    std::vector<int> int_v;
    int_v.push_back (1);
    int_v.push_back (2);
    int_v.push_back (3);
    for (int i = 0; i < 3; i ++) {
        std::cout << int_v[i] << std::endl;
    }

    //stringテスト
    std::cout << "string" << std::endl;
    std::vector<std::string> str_v;
    str_v.push_back ("おはよう");
    str_v.push_back ("こんにちは");
    str_v.push_back ("こんばんは");
    std::sort(str_v.begin(), str_v.end());
    for (auto x:str_v) {
        std::cout << x << std::endl;
    }

}