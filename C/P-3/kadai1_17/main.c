/* main.c */
#include <stdio.h>
#include "queue.h"

int main(){
  Queue que;
  int select,n,d,x;

  printf("キューを生成します");
  printf("要素数を入力してください:");
  scanf("%d", &n);
  QueueAlloc(&que, n);
  do{
    printq(&que);
    printf("\n(0)終了,(1)末尾に追加,(2)先頭の取り出し,(3)キューの状態表示\n");
    printf("以上からキューに対する操作を選択してください:");
    scanf("%d", &select);
    switch (select){
      case 1:
        printf("追加する数字を選択してください:");
        scanf("%d", &x);
        if(QueueEnque(&que,x) == 0){
          printf("%d を追加しました。\n",x);
        }else{
          printf("追加に失敗しました。\n");
        }
        break;
      case 2:
        if(QueueDeque(&que,&d) == 0){
          printf("%d を取り出しました。\n",d);
        }else{
          printf("取り出しに失敗しました。\n");
        }
        break;
      case 3:
        printf("キューの大きさは%dです。\n",QueueSize(&que));
        printf("現在、キューには%d個のデータが入っています。\n",QueueNo(&que));
        if(QueueIsEnpty(&que) == 0){
          printf("現在、キューは空ではありません。\n");
        }else{
          printf("現在、キューは空です。\n");
        }
        if(QueueIsFull(&que) == 0){
          printf("現在、キューは満杯ではありません。\n");
        }else{
          printf("現在、キューは満杯です。\n");
        }
        break;
      default:
        printf("終了します\n");
        select = 0;
        break;
    }
  }while(select != 0);

  QueueFree(&que);
  return(0);
}
