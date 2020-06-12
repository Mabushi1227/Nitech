#include<stdio.h>

int main(void)
{
    unsigned max;
    printf("Fizz Buzzを実行します\n");
    printf("上限を入力してください：");

    scanf("%u", &max);

    int i = 0;
loop:
    i++;
    if(i > max) goto end;
    
    printf("%u : ",i);

    if(i % 3 != 0) goto X3;

    if(i % 5 != 0) goto O3X5;
    printf("Fizz Buzz\n");
    goto loop;
X3:
    if(i % 5 != 0) goto X3X5;
    printf("Buzz\n");
    goto loop;

O3X5:
    printf("Fizz\n");
    goto loop;

X3X5:
    printf("%u \n",i);  
    goto loop;
        
end:    
    return (0);
}