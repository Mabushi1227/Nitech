/*Linearqueue.h */
/*同じファイルに前回の課題が含まれているため、それと区別するために若干関数名がスライドと異なります*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 10

/*---ノード---*/
typedef struct ___node{
  int no; /*会員番号*/
  char name[NAMELEN]; /*名前*/
  struct ___node *next; /*後続ノードへのポインタ*/
}QueueNode;

/*---キューを実装する構造体---*/
typedef struct {
  int num;  /*現在の要素数*/
  QueueNode *front;  /*先頭要素へのポインタ*/
  QueueNode *rear;  /*末尾要素へのポインタ*/
}LineQueue;

//キューの初期化
int LineQueueInit(LineQueue *q);

//キューの後始末
void LineQueueFree(LineQueue *q);

//キューにデータの追加
int LineQueueEnque(LineQueue *q, QueueNode *x);

//キューのデータの削除
QueueNode *LineQueueDeque(LineQueue *q);

//キューのデータ数を返す
int LineQueueNo(const LineQueue *q);

//キューが空か否かを返す
int LineQueueIsEnpty(const LineQueue *q);

//キュー内のノードを表示
void PrintLineQueue(const LineQueue *q);

//１つのノードを確保
QueueNode *AllocQueueNode(void);

void SetQueueNode(QueueNode *x, int no, char *name, QueueNode *next);
