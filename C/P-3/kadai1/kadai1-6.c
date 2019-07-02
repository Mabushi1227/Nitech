#include <stdio.h>

int main(void)
{
  int na,nb;
  puts("二つの整数を入力してください。");
  printf("整数Ａ：\n");	scanf("%d", &na);
  printf("整数Ｂ：\n");	scanf("%d", &nb);

  if (na%nb == 0) {
    printf("ＢはＡの約数です。\n");
  }else{
    printf("ＢはＡの約数ではありません。\n");
  }

  return 0;
}
