#include <iostream>
#include <string>

//srting型を引数をとる関数
void print(std::string str)
{
    std::cout << "関数を通して出力しています:" << str << std::endl;
}

int main() {
    std::string a("hello");
    std::string b,c;
    b = "world\n";
    c = a + b; //文字列の連結
    std::cout << b;

    //文字列比較
    if(b != c)
    {
        std::cout << c;
    }
    
    print(c);
}