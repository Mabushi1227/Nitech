#include "queue.h"

//キューの確保,初期化,
int QueueAlloc(Queue *q, int max){
  q->front = 0;
  q->full = 0;

  if((q->que = calloc(max,sizeof(int))) == NULL) {
    q->max = 0;
    return (-1);
  }
  q->max = max;
  return(0);
}

//キューの解放,破棄
void QueueFree(Queue *q){
  if(q->que != NULL){
    free(q->que);
  }
}

//キューにデータの追加
int QueueEnque(Queue *q, int x){
  if(QueueIsFull(q)){
    printf("キューが満杯です\n");
    return(-1);
  }
  q->que[q->rear] = x;
  q->rear = (q->rear+1) % q->max;
  if(q->rear == q->front){
    q->full = 1;
  }
  return(0);
}

//キューのデータの削除
int QueueDeque(Queue *q, int *x){
  if(QueueIsEnpty(q)){
    printf("キューが空です\n");
    return(-1);
  }

  *x = q->que[q->front];
  q->front = (q->front+1) % q->max;
  if(q->full == 1){
    q->full = 0;
  }
  return(0);
}

//キューの大きさを返す
int QueueSize(const Queue *q){
  return(q->max);
}

//キューのデータ数を返す
int QueueNo(const Queue *q){
  if(q->front < q->rear){
    return (q->rear - q->front);
  }else if(q->front > q->rear){
    return (q->max - q->front + q->rear);
  }else{
    if(q->full){
      return q->max;
    }else{
      return 0;
    }
  }
}

//キューが空か否かを返す
int QueueIsEnpty(const Queue *q){

  int enp = 0;
  if(q->full == 0 && q->front == q->rear){
    enp = 1; //空なら1を代入
  }

  return enp;
}

//キューが満杯か否かを返す
int QueueIsFull(const Queue *q){
  return q->full;
}

//キューの状態を表示
void printq(const Queue *q){
  int i = q->front;
  printf("現在の列\n");

  //満杯の時に、下のwhile文を抜けてしまうことを防ぐ
  if(q->full){
    printf("  %d  ",q->que[i]);
    i = (i+1) % (q->max);
  }

  while(i != q->rear){
    printf("  %d  ",q->que[i]);
    i = (i+1) % (q->max);
  }

}
