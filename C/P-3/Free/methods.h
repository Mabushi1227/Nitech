#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 10
#define swap(type,x,y) do {type t = x; x = y; y = t; } while (0)

void print(){
  clock_t start,end;
  start = clock();
  printf("%d\n", 123456789);
  end = clock();
  printf("評価時間：%f s\n" ,(double)(end-start)/1000000);
}

void print_a(int a[],int l){
  int i;
  for (i = 0; i < l; i++) {
    printf("%d, ",a[i]);
  }
  printf("\n");
}

//phaseを変更するメソッド
int receive_phase(int phase){
  int select;
  do{
    if(phase == 0){
      printf("\n現在は数値生成フェーズです。\n");
      printf(" ・(0)ソートする値を生成し直す\n");
      printf(" ・(1)確認フェーズへ進む\n");
      printf(" ・(2)ソート過程フェーズへ進む\n");
      printf(" ・(-1)終了する\n");
    }else if(phase == 1){
      printf("\n現在は確認フェーズです。\n");
      printf(" ・(0)ソートする値を生成し直す\n");
      printf(" ・(1)確認を続ける\n");
      printf(" ・(2)ソート過程フェーズへ進む\n");
      printf(" ・(-1)終了する\n");
    }else if(phase == 2){
      printf("\n現在はソート過程フェーズです。\n");
      printf(" ・(0)ソートする値を生成し直す\n");
      printf(" ・(1)確認フェーズに戻る\n");
      printf(" ・(2)他のソート過程を見る\n");
      printf(" ・(-1)終了する\n");
    }

    printf("以上の数値から選択し、入力してください：");
    scanf("%d",&select);
  }while(select < -1 || select > 2);

  return select;
}

//functionを変更するメソッド
int receive_function(int phase){
  int select;
  int range_flag = 0;
  do{
    if(phase == 1){
      printf("\n(アルゴリズムや、現在扱っている数値の確認ができます)\n");
      printf(" ・(0)ソート性能の表示する\n");
      printf(" ・(1)ソートアルゴリズムの説明を表示する\n");
      printf(" ・(2)現在扱っている数値の表示する\n");
      printf(" ・(-1)ソート過程フェーズに進む\n");
    }else if(phase == 2){
      printf("\n(ソート過程表示を表示します)\n");
      printf(" ・(0)バブルソート\n");
      printf(" ・(1)セレクションソート\n");
      printf(" ・(2)ヒープソート\n");
      printf(" ・(3)マージソート\n");
      printf(" ・(-1)確認フェーズに戻る\n");
      printf(" ・(-2)プログラムを終わる\n");
    }
    printf("以上の数値から選択し、入力してください：");
    scanf("%d",&select);

    if(phase == 1){
      if(select >= -1 && select <= 2){
        range_flag = 1;
      }
    }else if(phase == 2){
      if(select >= -2 && select <= 3){
        range_flag = 1;
      }
    }
  }while(range_flag == 0);

  return select;
}

//ランダムに値が入った配列を生成
void random_def(int *a,int n){
    printf("乱数を生成します:");
    srand(time(NULL));

    int i=0;
    while(i < n){
      *a = rand() % 100;
      printf("%d, ",*a++);
      i++;
    }
    printf("\n以上の数値のソートを行います。\n");
}

void sort_info(){
    printf("info");
}

void explain(){
    printf("explain\n");

    FILE *fp;
    char name[100];
    char o[100];
    char algorithm[400];

    if((fp = fopen("algorithms.txt","r")) == NULL){
        printf("ファイルをオープンできません");
    }else{
        while(fscanf(fp, "%s%s%s", name,o,algorithm) == 3){
            printf("%s %s \n  %s\n", name,o,algorithm);
        }
        fclose(fp);
    }
}

void array_status(int *a, int n){
    int i = 0;
    while(i < n){
      printf("%d, ",*a++);
      i++;
    }
    printf("\n");
}
