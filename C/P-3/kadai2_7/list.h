#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  Term, Insert, Append, Delete, n_Insert, n_Delete, Print, Clear
} Menu;

typedef struct __node {
  int no; /*会員番号*/
  char name[10]; /*名前*/
  struct __node *next; /*後続ノードへのポインタ*/
} Node;

void SetNode(Node *x, int no, char *name, Node *next);

Node *AllocNode(void);

void InsertNode(Node **top, int no, char *name);

void AppendNode(Node **top, int no, char *name);

void DeleteNode(Node **top);

void ClearList(Node **top);

void PrintList(Node **top);

void InitList(Node **top);

void TermList(Node **top);

Node Read(char *message);

Menu SelectMenu(void);

/*リストのn番目にノードを挿入(課題１)*/
void InsertNodeNth(Node **top, int n, int no, char *name);

/*リストのn番目のノードを削除(課題１)*/
void DeleteNodeNth(Node **top, int n);
