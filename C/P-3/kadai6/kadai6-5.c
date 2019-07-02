/* 二つの文字列が何文字一致しているかカウント */

#include <stdio.h>


int str_equalnum(const char *s1, const char *s2)
{//(* ここに解答を書き加える *)
  int n = 0;
  while(*s1){
    while(*s1++ == *s2++){
      n++;
    }
  }
  return n;
}

int main(void)
{
	char str1[32], str2[32];
	int n;

	printf("文字列1を入力してください：");
	scanf("%s", str1);

	printf("文字列2を入力してください：");
	scanf("%s", str2);

	n = str_equalnum(str1, str2);

	printf("文字列1と文字列2は%d文字一致しています\n", n);

	return(0);
}
