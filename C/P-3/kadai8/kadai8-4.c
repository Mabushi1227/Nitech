/* 身長と体重をファイルから読み込み身長順にソート */
#include <stdio.h>
#include <string.h>

/* 個人データ */
typedef struct{
	char name[100];
	double height;
	double weight;
}member;
//(* ここに解答を書き加える *)
 #include <stdlib.h>
 int cmp(const void *p,const void *q){
   return ((member*)p)->height - ((member*)q)->height;
 }

int main(void)
{
	FILE *fp;
	member ma[10];

	char str[10];
	int i = 0;

	char filename[60];

	scanf("%s",filename);
	//ファイルを開く
	//ファイルがオープンできなかったらtrueとなる
//(* ここに解答を書き加える *)
  if((fp = fopen(filename,"r")) == NULL){
		printf("ファイルをオープンできません。\n");
  }
	else{
		//ファイルがオープンできた時の処理
		int j;
		int k;
		while(fscanf(fp, "%s%lf%lf",ma[i].name,&(ma[i].height),&(ma[i].weight)) == 3){

			printf("%-10s %5.1f %5.1f\n",ma[i].name,ma[i].height,ma[i].weight);
			i++;
		}

		//ソートを行う
//(* ここに解答を書き加える *)
    j = i;
    qsort(ma, j, sizeof(member),cmp);
		//ソート結果を表示
		printf("----------SortResult----------\n");
		for(i=0;i<j;i++)
			printf("%-10s %5.1f %5.1f\n",ma[i].name,ma[i].height,ma[i].weight);
		fclose(fp);
	}

	return (0);
}
