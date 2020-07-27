#include<iostream>


class ClassRoom
{
private:
    int desk; //机数
    int chair; //椅子数
    int projecter; //プロジェクタ数
    int blackbord; //黒板数

public:

    /*引数なしのコンストラクタ*/
    ClassRoom()
    {
        desk = 0;
        chair = 0;
        projecter = 0;
        blackbord = 0;

        std::cout << "引数なしのコンストラクタ" << std::endl;
    }

    /*引数なしのコンストラクタ、オーバーロード*/
    ClassRoom(int deskNumber, int chairNumber, 
                    int projecterNumber, int blackbordNumber)
    {
        desk = deskNumber;
        chair = chairNumber;
        projecter = projecterNumber;
        blackbord = blackbordNumber;

        std::cout << "引数ありのコンストラクタ" << std::endl;
    }

    void print()
    {
        std::cout<<"席数:" << chair  << "\n机数:" << desk
                 << "\nプロジェクタ数:" << projecter << "\n黒板数" << blackbord  <<std::endl;
    }
};

int main()
{
    ClassRoom null; //引数なしで初期化
    null.print();

    ClassRoom full = ClassRoom(30,30,2,3); //引数ありで初期化
    full.print();
}