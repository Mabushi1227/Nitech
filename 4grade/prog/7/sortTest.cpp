#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

int main(){
    std::cout << "int" << std::endl;
    std::vector<int> int_v;
    int_v.push_back (3);
    int_v.push_back (1);
    int_v.push_back (2);
    std::sort(int_v.begin(), int_v.end());
    for (auto x:int_v) {
        std::cout << x << std::endl;
    }

    //doubleテスト
    std::cout << "double" << std::endl;
    std::vector<double> w_v;
    w_v.push_back (std::pow(2,1));
    w_v.push_back (std::pow(2,2));
    w_v.push_back (std::pow(2,0.5));
    std::sort(w_v.begin(), w_v.end());
    for (int i = 0; i < 3; i ++) {
        std::cout << w_v[i] << std::endl;
    }

    //randomテスト
    std::cout << "Rondom" << std::endl;
    std::vector<double> rand_v;
    for (int i = 0; i < 100; i ++) {
        //0.01~0.99をランダムで生成
        rand_v.push_back (std::rand()%100/100.0);
    }

    std::sort(rand_v.begin(), rand_v.end());
    for (int i = 0; i < 100; i ++) {
        std::cout << rand_v[i] << std::endl;
    }
}