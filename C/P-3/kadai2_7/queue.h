/* queue.h */
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int max;
  int num;
  int front;
  int rear;
  int full;
  int *que;
} Queue;

//キューの確保,初期化,
int QueueAlloc(Queue *q, int max);

//キューの解放,破棄
void QueueFree(Queue *q);

//キューにデータの追加
int QueueEnque(Queue *q, int x);

//キューのデータの削除
int QueueDeque(Queue *q, int *x);

//キューの大きさを返す
int QueueSize(const Queue *q);

//キューのデータ数を返す
int QueueNo(const Queue *q);

//キューが空か否かを返す
int QueueIsEnpty(const Queue *q);

//キューが満杯か否かを返す
int QueueIsFull(const Queue *q);

void printq(const Queue *q);
