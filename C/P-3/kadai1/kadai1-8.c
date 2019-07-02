#include <stdio.h>
int main(void)
{
	int i;
	int sum = 0;

for (i = 1; i <= 5; i++) {
  sum += i;
}

printf("1から5までを足した値は%dです．\n",sum);

return (0);
}
