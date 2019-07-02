#include <stdio.h>

int main(void)
{
  int a,b;

  printf("二つの整数を入力してください。\n");
  printf("整数Ａ：\n");
  scanf("%d", &na);

  printf("整数Ｂ：\n");
  scanf("%d", &nb);

  printf("Ａの値はＢの%f％です。\n",(double)na/ (double) nb*100);

  return 0;
}
