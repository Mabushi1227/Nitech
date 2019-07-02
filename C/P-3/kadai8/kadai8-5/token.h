/* token.h
token.c(コマンドライン（１行の文字列）の分解と解析)のためのヘッダファイル
*/
/* コマンドラインの最大文字数　*/
#define MAXLINE 120

/* コマンドラインのトークンの定義　*/
/* 1コマンドラインのトークン個数の最大値　*/
#define MAXTOKEN 10
/* トークンデータの最大文字数　*/
#define TOKENSIZE 40

/* トークンのデータ型の定義　*/
typedef struct{
char data[TOKENSIZE];  /* トークンデータ（文字列）*/
int type;       /* トークン種別*/
int value;      /* トークンの値*/
} token;

/* コマンドラインのトークン種別の定義　*/
#define TKNUNDEF 0 /*　未定義の文字列 */
#define TKNKWD 1  /*　キーワード表に定義された名前 */
#define TKNINT 2  /* 整数（１０進数または１６進数）*/
#define TKNLBL 3  /* キーワード表に定義されていないラベル*/

/* コマンドラインの解析結果コードの定義　*/
#define TKNOK 0
#define TKNERR 1

/* キーワードのデータ構造の定義　*/
typedef struct{
char name[10];  /* キーワード名　*/
int id;         /* キーワードの識別子　*/
} KeyWD;

int tokenizer(char line[], token token[]);
void setTokens(token token[],int nt, KeyWD k[], int KeyWDlen);
