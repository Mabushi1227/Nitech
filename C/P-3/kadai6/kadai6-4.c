#include <stdio.h>

/*---文字列の長さを返す関数---*/
unsigned str_length(const char str[])
{
//(* ここに解答を書き加える *)
  unsigned length = 0;
  while(str[length]){
    length++;
  }
  return length;
}

void put_rstring(const char str[])
{
//(* ここに解答を書き加える *)
  int l,i;
  l = str_length(str);
  while(l){
        l--;
        printf("%c",str[l]);
  }
}

int main(void)
{
	char str[100];
	printf("文字列を入力：");
	scanf("%s",str);

	printf("逆にすると次のようになります \n");
	put_rstring(str);
         putchar('\n');
	return(0);
}
