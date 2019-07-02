/* token-test.c
次の２つの関数を用いて，１行の文字列をトークンに分解して，トークンにデータ種別と
値を設定する．
（１）tokenizer(line,token)
　lineをトークンに分解する．
　入力引数　char line[MAXTOKEN], token token[MAXTOKEN]
　戻り値　　トークンの個数．
（２）setTokens(token,nt,KWDT,KeyWDlen)
　トークンにデータ種別(type)と値(value)を設定
　入力引数　token token[MAXTOKEN], int nt, keyWD KWDT[NUMKW], int KeyWDlen
   nt=トークン個数, KWDT=キーワード定義表，KeyWDlen=KWDTの長さ（キーワードの数）
　戻り値　　なし
　トークンの処理に関する定数，データ型はtoken.hの定義を用いる
　キーワードの定義表KWDTは，keyword.hの定義を用いる
*/
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "keyword.h"

int main(void)
{
static token token[MAXTOKEN];
static char line[MAXLINE];
char filename[20];
int i=0,nt;
int KeyWDlen=sizeof(KWDT)/sizeof(KeyWD);
FILE *fp;

/* （０)標準入力からファイル名を読込み，オープンする．*/
puts("ファイル名を入力しなさい：　");
//printf("ファイル名を入力しなさい：　");  /* メッセージをstdoutに出力 */
scanf("%s",filename);
if ((fp = fopen(filename,"r")) == NULL) {

printf("ファイル%sをオープンできません\n",filename);
exit(1);}

/* （１)ファイルから文字列を１行だけ読込み，標準出力に印字する．*/
fgets(line,MAXLINE,fp);  /* fp　から１行読込んでlineに格納 */
fputs(line,stdout);      /* lineをstdoutに出力 */

/* （２）関数tokeizerにより１行の文字列をトークンと呼ぶ単語に分解する．*/
nt=tokenizer(line,token);/* lineをトークンに分解．nt=トークンの個数 */
if (nt==0) {printf("トークンはありません\n"); exit(1);}

/* （３）tokenizerの結果を表示する．*/
for (i=0; i<nt; i++){
printf("\ntoken[%d]: data=%s",i,token[i].data);
}
puts("\n"); /* 出力調整用の改行 */

/* （４）関数setTokensにより，各トークンにデータ種別(type)と値(value)を設定する */
setTokens(token,nt,KWDT,KeyWDlen);

/* （５）setTokensの結果を表示する．*/
for (i=0; i<nt; i++){
switch(token[i].type){  /* トークンのデータ種別(type)で分類して出力 */
case TKNKWD:               /* キーワードのトークン */
fputs("Keyword: ",stdout);
switch(token[i].value){
case _clear: fputs("[clear] ",stdout); break; /* キーワードがclearのとき */
case _load: fputs("[load] ",stdout); break;   /* キーワードがloadのとき */
case _step: fputs("[step] ",stdout); break;   /* キーワードがstepのとき */
}
break;
case TKNINT:               /* 符号なし整数のトークン */
fputs("Integer: ",stdout); break;
case TKNLBL:               /* ラベルのトークン */
fputs("Label: ",stdout); break;
case TKNUNDEF:             /* 未定義のトークン */
fputs("Undefined: ",stdout); break;
}
/* トークンのデータ，データ種別，値を出力 */
printf("data=%s type=%d value=%d\n",
token[i].data,token[i].type,token[i].value);
}

}
