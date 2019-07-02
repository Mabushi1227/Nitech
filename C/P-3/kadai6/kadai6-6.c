#include <stdio.h>

void del_digit(char str[])
{//(* ここに解答を書き加える *)
  //char *ptr = &str[0];
  int n = 0;
  while(str[n]){
    if(str[n] >= '0' &&  str[n] <= '9'){
      int i = n;
      while(str[i]){
        str[i] = str[i+1];
        i++;
      }
    }else{
      n++;
    }
  }
}

int main(void)
{
	char str[100];
	printf("文字列strを入力！：str = 　");
	scanf("%s",str);

	printf("数字の削除！\n");

	del_digit(str);

	printf("str = %s\n",str);

	return(0);
}
