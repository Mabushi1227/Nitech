/*
  入力に現れた改行の数を表示する
 */

#include <stdio.h>

int main(void)
{
  //(* ここに解答を書き加える *)
  int ch,n_count = 0;

 while((ch = getchar()) != '0'){
      if(ch == '\n'){
        n_count++;
      }
   }
  printf("行数：%d\n", n_count);
  return(0);
}
