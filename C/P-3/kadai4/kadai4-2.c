/*
  二つの値を交換する関数形式マクロ
*/
#include<stdio.h>
//(* ここに解答を書き加える *)
#define swap(type, a,b) {type t; t = a; a = b; b = t;}

int main(void)
{
  int na,nb;

  puts("二つの整数を入力せよ．");
  printf("整数Ａ:"); scanf("%d", &na);
  printf("整数Ｂ:"); scanf("%d", &nb);

  swap(int, na, nb);
  puts("\nＡとＢの値を交換");
  printf("整数Ａ=%d\n", na);
  printf("整数Ｂ=%d\n", nb);

  return (0);
}
