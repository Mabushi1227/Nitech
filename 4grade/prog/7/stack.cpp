#include<iostream>
#include<string>
#include<vector>

template <typename T>
/* テンプレートで実装した汎用stackクラス*/
class Stack
{
public:
    void Push(T value)
    {
        stack_.push_back(value);
    }

    T Pop()
    {
        T x = stack_[stack_.size()-1];
        stack_.pop_back();
        return x;
    }

private:
    std::vector<T> stack_;
};

int main()
{
    //intテスト
    Stack<int> int_stack;

    int_stack.Push(1);
    int_stack.Push(2);
    int_stack.Push(3);

    std::cout << int_stack.Pop() << std::endl;
    std::cout << int_stack.Pop() << std::endl;
    std::cout << int_stack.Pop() << std::endl;

    //stringテスト
    Stack<std::string> string_stack;

    string_stack.Push("おはよう");
    string_stack.Push("こんにちは");
    string_stack.Push("こんばんは");

    std::cout << string_stack.Pop() << std::endl;
    std::cout << string_stack.Pop() << std::endl;
    std::cout << string_stack.Pop() << std::endl;

}

