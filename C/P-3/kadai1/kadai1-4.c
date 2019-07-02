#include <stdio.h>

int main(void)
{
  int no1,no2,no3;

  printf("三つの整数を入力してください。\n");
  printf("整数１：");
  scanf("%d", &no1);

  printf("整数２：");
  scanf("%d", &no2);

  printf("整数３：");
  scanf("%d", &no3);

  printf("それらの和は%dです。\n", no1+no2+no3);
  return 0;
}
