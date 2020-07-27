#include<iostream>

#define PI 3.14159265359 //円周率

/* 継承元クラス */
class Object
{
public:
    virtual double area() = 0; //純粋仮想関数,面積を返す

};

/* 長方形を示すObjectの派生クラス */
class Rectangle: public Object
{
private:
    int* point1; //点１
    int* point2; //点２

public:
    Rectangle(int x1, int y1, int x2, int y2)
    {
        point1 = new int[2];
        point1[0] = x1;
        point1[1] = y1;
        point2 = new int[2];
        point2[0] = x2;
        point2[1] = y2;
    }
    double area()
    {
        return std::abs( (point1[0] - point2[0]) * (point1[1] - point2[1]) );
    }

};

/* 円を示すObjectの派生クラス */
class Circle: public Object
{
private:
    int* center; //中心
    int radius; //半径

public:
    Circle(int x, int y, int r)
    {
        center = new int[2];
        center[0] = x;
        center[1] = y;
        radius = r;
    }

    double area()
    {
        return radius*radius*PI;
    }
};

int main()
{
    Rectangle rect(0,0,3,4);
    std::cout << "長方形rectの面積:" << rect.area() << std::endl;

    Circle cir(0,0,3);
    std::cout << "円cirの面積:" << cir.area() << std::endl;
}