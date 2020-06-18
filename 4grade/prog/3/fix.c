#include <stdio.h>
struct Person //struct P
{
    char* name; //char* n;
    int number; //int a;
};

//void f(struct P* p, char* _n)
void set_personName(struct Person* person, char* _name)
{
    person->name = _name;
}

//void g(struct P* p, int _a)
void set_personNumber(struct Person* person, int _number)
{
    person->number = _number;
}

//void u(struct P* p)
void print_personName(struct Person* person)
{
    printf("%s\n", person->name);
}

//void v(struct P* p)
void print_personNumber(struct Person* person)
{
    printf("%d\n", person->number);
}


int main(void)
{
    /*
    struct P p[2];
    f(&p[0], "Taro");
    g(&p[0], 21);
    f(&p[1], "Hanako");
    g(&p[1], 20);
    for (int i = 0; i < 2; i++) {
        u(&p[i]);
        v(&p[i]);
    }
    */
    struct Person people[2];
    set_personName(&people[0], "Taro");
    set_personNumber(&people[0], 21);
    set_personName(&people[1], "Hanako");
    set_personNumber(&people[1], 20);
    for (int i = 0; i < 2; i++) {
        print_personName(&people[i]);
        print_personNumber(&people[i]);
    }

}