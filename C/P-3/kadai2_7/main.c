#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "linearqueue.h"
#include "queue.h"

int main(void){
  int program;
  printf("(0)前回課題のプログラム(修正版)\n(1)課題1のプログラム\n(2)課題２のプログラム\n以上から選択してください:");
  scanf("%d",&program);

  if(program == 1){  /* 1を選択したとき実行 */
    printf("線形リストのプログラムを実行します\n");
    Menu menu;
    Node *list = AllocNode();
    int count = 0; //ノードの数
    Node x;
    int n = 0;

    do{
      switch (menu = SelectMenu()) {
        case Insert:
          x = Read("挿入");
          InsertNode(&list, x.no, x.name);
          count++;
          PrintList(&list);
          break;
        case Append:
          x = Read("追加");
          AppendNode(&list, x.no, x.name);
          count++;
          PrintList(&list); break;
        case Delete:
          DeleteNode(&list);
          count--;
          PrintList(&list); break;
        case n_Insert:
          printf("現在%d個のノードがあります。\n何番目を挿入しますか？:",count);
          scanf("%d",&n);
          x = Read("挿入");
          count++;
          if(n > 1 && n <= count){
            InsertNodeNth(&list,n,x.no,x.name);
          }else if(n == 1){
            InsertNode(&list,x.no,x.name);
          }else if(n == count+1){
            AppendNode(&list,x.no,x.name);
          }else{
            printf("挿入に失敗しました。");
            count--;
          }
          PrintList(&list); break;
        case n_Delete:
          printf("現在%d個のノードがあります。\n何番目を削除しますか？",count);
          scanf("%d",&n);

          if(n > 1 && n <= count){
            DeleteNodeNth(&list,n);
            count--;
          }else if(n == 1){
            DeleteNode(&list);
            count--;
          }else{
            printf("挿入に失敗しました。\n");
          }
          PrintList(&list); break;
        case Print:
          PrintList(&list);
          break;
        case Clear:
          ClearList(&list);
          count = 0;
          PrintList(&list); break;
        default: menu = Term; break;

      }
    }while(menu != Term);

    TermList(&list);

  }else if(program == 2){ /* 2を選択したとき実行 */
    printf("線形リストを用いたキューのプログラムを実行します\n");
    LineQueue que;
    int select,d; //動作を受け取る変数,デキューで取り出した数,
    QueueNode *x = AllocQueueNode();

    LineQueueInit(&que);
    printf("キューを生成しました\n");

    do{
      printf("\n(0)終了,(1)末尾に追加,(2)先頭の取り出し,(3)キューの状態表示\n");
      printf("以上からキューに対する操作を選択してください:");
      scanf("%d", &select);
      switch (select){
        case 1:
          x = AllocQueueNode();
          if(LineQueueEnque(&que,x)){
            printf("%d. %sを追加しました。\n",x->no,x->name);
            que.num++;
            if(que.num == 0){
              x = LineQueueDeque(&que);
              que.num = 1;
            }
          }else{
            printf("追加に失敗しました。\n");
          }
          PrintLineQueue(&que); break;
        case 2:
          if(que.num > 0){
            x = LineQueueDeque(&que);
            printf("%d. %sを取り出しました。\n",x->no,x->name);
            que.num--;
          }else{
            printf("取り出しに失敗しました。\n");
          }
          if(que.num == 0){
            LineQueueInit(&que);
            que.num = -1; break;
          }
          PrintLineQueue(&que); break;
        case 3:
          if(LineQueueIsEnpty(&que)){
            printf("現在、キューは空です。\n");
          }else{
            printf("現在、キューには%d個のデータが入っています。\n",LineQueueNo(&que));
          }
          PrintLineQueue(&que); break;
        default:
          printf("終了します\n");
          select = 0;
          break;
      }
    }while(select != 0);

    LineQueueFree(&que);

  }else if(program == 0){ /* 0を選択したとき実行 */
    printf("前回課題のリングバッファ(修正版)を実行します\n");
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
          if(QueueIsEnpty(&que)){
            printf("現在、キューは空です。\n");
          }else{
            printf("現在、キューは空ではありません。\n");
          }
          if(QueueIsFull(&que)){
            printf("現在、キューは満杯です。\n");
          }else{
            printf("現在、キューは満杯ではありません。\n");
          }
          break;
        default:
          printf("終了します\n");
          select = 0;
          break;
      }
    }while(select != 0);

    QueueFree(&que);

  }
  return(0);
}
