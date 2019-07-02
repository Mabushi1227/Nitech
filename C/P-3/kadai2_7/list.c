#include "list.h"

void SetNode(Node *x, int no, char *name, Node *next){
  x->no = no;
  x->next = next;
  strcpy(x->name, name);
}

Node *AllocNode(void){
  return (calloc(1, sizeof(Node)));
}


void InsertNode(Node **top, int no, char *name){
  Node *ptr = *top;
  *top = AllocNode();
  SetNode(*top, no, name, ptr);
}

void AppendNode(Node **top, int no, char *name){
  if(*top == NULL){
    InsertNode(top, no, name);
  }else{
    Node *ptr = *top;
    while(ptr->next != NULL){
      ptr = ptr->next;
    }
    ptr->next = AllocNode();
    SetNode(ptr->next, no, name, NULL);
  }
}

void DeleteNode(Node **top){
  if(*top != NULL){
    Node *ptr = (*top)->next;
    free(*top);
    *top = ptr;
  }
}

void ClearList(Node **top){
  while (*top != NULL){
    DeleteNode(top);
  }
}

void PrintList(Node **top){
  Node *ptr = *top;
  puts("[一覧表]");
  while(ptr->next != NULL){
    printf("%5d %-10.10s\n", ptr->no, ptr->name);
    ptr = ptr->next;
  }
}

void InitList(Node **top){
  *top = NULL;
}

void TermList(Node **top){
  ClearList(top);
}

Node Read(char *message){
  Node temp;

  printf("%sするデータを入力してください\n" , message);

  printf("番号:"); scanf("%d", &temp.no);
  printf("名前:"); scanf("%s", temp.name);

  return (temp);
}

Menu SelectMenu(void){
  int ch;

  do{
    puts("(1) 先頭にノードを挿入 (2)末尾にノードを追加");
    puts("(3) 先頭のノードを削除 (4)n番目にノードを挿入");
    puts("(5) n番目のノードを削除 (6)全てのノードを表示");
    puts("(7) 全てのノードを削除 (0)処 理 終 了");
    scanf("%d", &ch);
  }while(ch < Term || ch > Clear);

  return ((Menu)ch);
}


/*リストのn番目にノードを挿入(課題１)*/
void InsertNodeNth(Node **top, int n, int no, char *name){
  if(n == 1){
    InsertNode(top, no, name);
  }else{
    Node *add = AllocNode();
    add->no = no;
    strcpy(add->name,name);
    Node *ptr = *top;

    int l;
    for (l = 1; l < n-1; l++) {
      ptr = ptr->next;
    }

    add->next = ptr->next;
    ptr->next = add;
  }
}

/*リストのn番目のノードを削除(課題1)*/
void DeleteNodeNth(Node **top, int n){
  int i;
  Node *ptr = *top;
  Node *del;
  for (i = 1; i < n-1; i++) {
    ptr = ptr->next;
  }
    del = ptr->next;
    ptr->next = del->next;
    free(del);

}
