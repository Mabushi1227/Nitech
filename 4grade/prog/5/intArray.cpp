#include <iostream>

/* 継承元のクラス */
class IntArray
{
protected:
    int size;
    int* array;
public:
    IntArray(int _size)
    {
        size = _size;
        array = new int[size];
        for (int i = 0; i < size; i++) array[i] = 0;
    }

    ~IntArray()
    {
        delete[] array;
        printf("destructor called\n");
    }
    
    void print_array()
    {
        for (int i = 0; i < size; i++) printf("%d: %d\n",i,array[i]);
    }
};

/* IntArrayを継承したクラス */
class NewIntArray: public IntArray
{
public:
    /* コンストラクタ */
    NewIntArray(int _size): IntArray(_size){}

    /* idにvalueを代入 */
    void set(int id, int value)
    {
        if(0 <= id && id < size)
        {
            array[id] = value;
        }
    }

    /* 合計を返す */
    int sum()
    {
        int sumValue = 0;
        for(int i = 0; i < size; i++)
        {
            sumValue += array[i];
        }
        return sumValue;
    }

    int array_size()
    {
        return size;
    }

};

int main()
{
    NewIntArray a(4); //継承した側のクラスで作成
    a.print_array();

    for (int i = 0; i < a.array_size(); i++)
    {
        a.set(i,i); //インデックスを代入
    }
    
    a.print_array();
    a.sum();
}