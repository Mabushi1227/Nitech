#include<iostream>
#include<string>

class Person
{
private:
    std::string name;
    int number;
public:
    Person(std::string personName, int personNumber)
    {
        name = personName;
        number = personNumber;
    }
    void show()
    {
        std::cout<<"学籍番号:" << number << ", 氏名:" << name <<std::endl;
    }
};

int main()
{
    Person I = Person("秋田一樹", 29119001);
    I.show();
    return 0;
}