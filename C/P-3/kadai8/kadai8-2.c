#include <stdio.h>

int main(void)
{
	int ch;
	FILE *sfp, *dfp;
	char sname[64],dname[64];

	printf("コピー元ファイル名を入力してください：");
	scanf("%s",sname);
	printf("コピー先ファイル名を入力してください：");
	scanf("%s",dname);

	if((sfp = fopen(sname,"r")) == NULL)
		printf("コピー元ファイルをオープンできません。\n");
	else{
		/* ファイルから読み込み */
		if((dfp = fopen(dname,"w")) == NULL)
			printf("コピー先ファイルをオープンできません。\n");
		else{
//(* ここに解答を書き加える *)
        while((ch = fgetc(sfp)) != EOF){
          fputc(ch,dfp);
          printf("%c",ch);
        }fclose(dfp);
        fclose(sfp);
      }
	}

	return (0);
}
