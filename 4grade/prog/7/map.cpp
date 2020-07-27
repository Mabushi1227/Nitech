#include <iostream>
#include <map>

int main()
{
    std::map<int,std::string> student;

    student[29119001] = "秋田一樹";

    //valueの表示
    std::cout << student[29119001] << std::endl;
    //mapサイズの出力
    std::cout << student.size() << std::endl;
    //key:29119001で検索
    std::cout << student.at(29119001) << std::endl;

    //mapをfor eachでなぞる
    for (auto& [key, value] : student){
        std::cout << value << " : " << key << "\n";
    }
}