//ファイル内の文字のうち，アルファベットだけカウントする
#include <stdio.h>

int main(void){
	FILE	*fp;
	int		ch;
	char filename[60];

	int		count = 0;
	scanf("%s",filename);

	printf("入力ファイル名：%s\n",filename);
	//ファイルオープン処理
//(* ここに解答を書き加える *)
  fp = fopen(filename,"r");
  if(fp == NULL)

{
		printf("Cannot open %s\n", filename);
		return 0;
	}
	//文字数カウント処理
//(* ここに解答を書き加える *)
else{

  while((ch = fgetc(fp)) != EOF){
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        count++;
    }
  }fclose(fp)
}

	printf("Number of Alphabet in %s is %d \n", filename, count);
	fclose(fp);

	return 0;
}
