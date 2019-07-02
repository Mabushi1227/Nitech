/*linearqueue*/
/*同じファイルに前回の課題が含まれているため、それと区別するために若干関数名がスライドと異なります*/

#include "linearqueue.h"

//キューの初期
int LineQueueInit(LineQueue *q){
  q->num = -1;
  QueueNode *StartNode = AllocQueueNode();
  SetQueueNode(StartNode,-1,"Enpty",NULL);
  q->front = q->rear = StartNode;
  return 0;
}

//キューの後始末
void LineQueueFree(LineQueue *q){
  if(q->front != NULL){
    free(q->front);
  }
}

//キューにデータの追加
int LineQueueEnque(LineQueue *q, QueueNode *x){
  q->rear->next = x;

  int no;
  char name[NAMELEN];
  QueueNode *next;
  printf("追加する番号を入力してください:");
  scanf("%d",&no);

  printf("追加する名前を入力してください:");
  scanf("%s", name);

  SetQueueNode(x,no,name,NULL);

  q->rear = x;

  return 1;
}

//キューのデータの削除
QueueNode *LineQueueDeque(LineQueue *q){

  QueueNode *node = q->front;
  q->front = node->next;

  return node;
}

//キューのデータ数を返す
int LineQueueNo(const LineQueue *q){
  return q->num;
}

//キューが空か否かを返す
int LineQueueIsEnpty(const LineQueue *q){
  if(q->num > 0){
    return 0;
  }else{
    return 1;//空なら１
  }
}

//キュー内のノードを表示
void PrintLineQueue(const LineQueue *q){
  int i;
  QueueNode *ptr = q->front;
  while(1){
    printf("%d. %s\n",ptr->no,ptr->name);
    if((ptr = ptr->next) == NULL) break;
  }
    //printf("%d. %s\n",ptr->no,ptr->name);
}

//ノードにノード情報を書き込む
void SetQueueNode(QueueNode *x, int no, char *name, QueueNode *next){
  x->no = no;
  x->next = next;
  strcpy(x->name, name);
}

//１つ分のノードを確保
QueueNode *AllocQueueNode(void){
  return (calloc(1, sizeof(QueueNode)));
}
