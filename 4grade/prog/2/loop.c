#include<stdio.h>

int main(void)
{
    int loop = 10;
    for (int i = 0; i <= loop; i++)
    {
        for (int j = 0; j <= loop; j++)
        {
            for (int k = 0; k <= loop; k++)
            {
                printf("%2d %2d %2d\n", i, j, k);
                //if((i == 7) && (j == 7) && (k == 7)) goto end; 
                if((i == 7) && (j == 7) && (k == 7)) break;
            }
            if((i == 7) && (j == 7)) break;
        }
        if(i == 7) break;
    }
    
end:
    printf("end\n");
    return (0);
}