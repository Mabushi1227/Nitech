#include<stdio.h>

int main(void)
{
    unsigned max;
    printf("Fizz Buzzを実行します\n");
    printf("上限を入力してください：");

    scanf("%u", &max);

    for (int i = 1; i <= max; i++)
    {
        printf("%u : ",i);

        if(i % 3 == 0)
        {
            if(i % 5 == 0)
            {
                printf("Fizz Buzz\n");
            }
            else
            {
                printf("Fizz\n");
            }
                
        }
        else if(i % 5 == 0)
        {
            printf("Buzz\n");
        }
        else
        {
            printf("%u \n",i);    
        }
        
    }
    
    return (0);
}