#include <stdio.h>
#include <iostream>
#include<string>

/* 継承元クラス */
class Comparable
{
public:
    /* 純粋仮想関数 */
    virtual void print() = 0;
    virtual bool LTE(Comparable* a) = 0; //less than equal
};

/* valueにboubleを持つ派生クラス */
class Double: public Comparable
{
private:
    double val;
public:
    Double(double v) {val = v;}
    bool LTE(Comparable* a) {
        if (val <= (static_cast<Double*>(a)->val)) return true;
        else return false;
    }
    void print() {printf("%f\n", val);}
};

/* valueにcharを持つ派生クラス */
class Char: public Comparable
{
private:
    char val;
public:
    Char(char c){val = c;}

    bool LTE(Comparable* a) {
        if (val <= (static_cast<Char*>(a)->val)) return true;
        else return false;
    }
    void print() {printf("%c\n", val);}

};

/* valueにnameとyearを持つ派生クラス */
class Person: public Comparable
{
private:
    std::string name; //名前
    int year; //年齢
public:
    Person(std::string PersonName, int PersonYear)
    {
        name = PersonName;
        year = PersonYear;
    }

    bool LTE(Comparable* a) {
        if (year <= (static_cast<Person*>(a)->year)) return true;
        else return false;
    }
    void print() {
        std::cout << "最年少は" << name << "で" << year << "才です" << std::endl;
    }

};

Comparable* x[10];

void find_min()
{
    Comparable* min = x[0];
    for (int i = 1; i < 10; i++) {
        if(x[i]->LTE(min))
        {
            min = x[i];
        }
    }
    min->print();
}
int main()
{
    //Doubleクラスの動作確認
    for (int i = 0; i < 10; i++) {
        //{10,5,2,1,2,5...37}
        x[i] = new Double((i-3)*(i-3)+1);
    }
    find_min();

    //Charクラスの動作確認
    for (int i = 0; i < 10; i++) {
        //{a,b,c,...,j}
        x[i] = new Char('a' + i);
    }
    find_min();

    //Personクラスの動作確認
    x[0] = new Person("太郎",20);
    x[1] = new Person("一郎",18);
    x[2] = new Person("次郎",22);
    x[3] = new Person("三郎",33);
    x[4] = new Person("四郎",60);
    x[5] = new Person("五郎",32);
    x[6] = new Person("六郎",21);
    x[7] = new Person("七郎",42);
    x[8] = new Person("八郎",88);
    x[9] = new Person("九郎",28);

    find_min();
}