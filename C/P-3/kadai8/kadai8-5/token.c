/* token.c
   1行の文字列をトークンに分解して，分類する．
（１）関数tokeizer
     １行分のの文字列 line[] をトークンと呼ぶ単語に分解する．
（２）関数setTokens
　　　各トークンを分類し，その種別と値を設定する．
ここで，トークンとは，区切り文字（空白，タブ，カンマ）で区切られた一連の文字列である．
たとえば，文字列"load  FNAME1,0x10\n"は，"load","FNAME3","0x10"の３つのトークンに分解できる．
トークンの種別は，整数（１０進数または１６進数（数字の列の先頭に#を付与)），keyword.hであらかじめ定
義されたキーワード，ラベル(大文字英字ではじまり，大文字英字または数字８文字以内のキーワード以外の文
字列），未定義（その他の文字列）の４種類とする．
また，１０進数と１６進数の場合は，符号なし整数値，キーワードの場合はキーワードの識別子，ラベルの場合
は文字数をトークンの値として設定する．
上の例では，"load"は種別はキーワードで値が３，"FNAME3"は種別はラベルで値は６，"0x100"は種別は整数で
値は１６である．

トークンの処理に関する定数，データ型はtoken.hの定義を用いる．また，キーワードの定義表は，関数
setTokenの引数(KeyWD k[])を用いる．

*/

#include <stdio.h>
#include "token.h"

/* char nextChar(char line[], int *lineindex)
   文字列lineから１文字読み出して返し，ポインタlineindexを１だけ進める．
   読み出した文字が\n（改行）または0XD（CR(復帰)または \0（文字列の終わり）の場合は，
   \0を返し，ポインタはそのままにする
   戻り値　\0（\nまたは\0を読み出した場合）
 　読み出した文字（その他の文字を読み出した場合
*/
char nextChar(char line[], int *lineindex)
{
  char ch=line[*lineindex];

  if(ch == '\n' || ch == 0xd || ch == '\0')
  {
	  return '\0';
  }

 (*lineindex)++;
 return ch;
}

/* int getToken(char line[], int *lineindex, char *str)
   文字列lineからトークンを１つ読み出して，文字列strに書き込む．
   トークンは' '（空白）または','（カンマ）または'\t'（タブ）)で区切られた文字列である．
   トークンの文字列の最大値はTOKENSIZE　
   戻り値　文字数
           0（文字列が空（先頭が\0）の場合）　
*/
int getToken(char line[], int *lineindex, char *str)
{
    char ch, d1=' ', d2=',', d3='\t';
    int found=0;
    while ((ch = nextChar(line,lineindex)) != '\0') {
/* 読み込んだ文字列lineからトークンを１つ読み出して，文字列strに最大TOKENSIZE文字数まで書き込む．
   ただし, 文字数が0でなく' '（空白）または','（カンマ）または'\t'（タブ）を読み込んだらbreak;
*/
//(* ここに解答を書き加える *)
      if(((ch == d1 || ch == d2 || ch == d3 ) && found != 0 )|| found >= TOKENSIZE){
        break;
      }else{
        *str++ = ch;
        found++;
      }

    }
    *str= '\0';
    return(found);
}

/*  int tokenizer(char line[], token token[])
    文字列lineをトークンに分解して,各token[]のdataに格納する．
    トークンは' '（空白）または','（カンマ）で区切られた文字列である．
    トークンの文字列の最大値はTOKENSIZE　
    戻り値　トークンの数（非負）
    　　　　-1（エラーの場合)
*/
int tokenizer(char line[], token token[])
{
    int lineindex=0;
    int i=0;
    int n=getToken(line, &lineindex, token[i].data);
    while (n!=0 && n < MAXTOKEN){
	i++;
	n=getToken(line, &lineindex, token[i].data);
    }
    return(i);
}

/* int dectoi(char *s)
   非負１０進数の文字列を整数に変換する
   戻り値　変換結果（正しく変換した場合）
   　　　　-1（エラー（数値以外の文字があった場合））
*/
int dectoi(char *s)
{
    int n = 0;
    while (*s != '\0'){
	if ((*s >='0') && (*s <= '9'))  n = n * 10 + (*s -'0');
	else return(-1);
	s++;}
    return(n);
}

/* int hextoi(char *s)
   １６進数の文字列を整数に変換する.
   ｓは，先頭が'#'で，その後に数字が続く文字列．
   戻り値　変換結果（正しく変換した場合）
   　　　　-1（エラー（先頭に１６進数指定がない場合，または１６進数以外の文字があった場合））
*/
int hextoi(char *s)
{
    int n=0;
    if (*s =='#'){/* 先頭に'#'があるか？ */
	s++;        /* Yes.先頭に'#'がある*/
	while (*s != '\0'){
	    if ((*s >='0') && (*s <='9'))   n = n*16 + (*s -'0');
	    else {
		if ((*s >='a') && (*s <='f'))  n = n*16+10+(*s -'a');
		else if ((*s >='A') && (*s <='F')) n = n*16+10+(*s -'A');
		else return(-1); /* not Hex */
	    }
	    s++;
	}
	return(n); /* Hex. */
    }
    else return(-1); /* not Hex */
}

/* int isLabel(char *s)
   ラベルの文字列か調べる
   ラベルは，先頭が大文字の英字，２文字目以降は英大文字，または数字で，
   ８文字以下．
   戻り値　正（ラベルの文字列長）
   　　　　 0（その他）
*/
int isLabel(char *s)
{
    int n=0;
    if ((*s >='A') && (*s <='Z')) { /* 先頭が大文字英字か？ */
	s++; n++;               /* Yes. */
	while (*s != '\0'){
	    if ((n<8) && (((*s >='A') && (*s <='Z')) ||
			  ((*s >='0') && (*s <='9')))) {
		        s++;n++;}
	    else return(0);}
	return(n); /* ラベル */
    }
    else return(0);
}

/* int strcmp(const char *s1, const char *s2)
   ２つの文字列を比べる．
   戻り値：0：等しい　正の整数：s1>s2 負の整数：s2>s1
*/
int strcmp(const char *s1, const char *s2)
{
    while (*s1 == *s2){
	     if (*s1 == '\0') return (0);
	     s1++; s2++;
    }
    return( (unsigned char)*s1 - (unsigned char)*s2);
}

/* int kwtoi(char *s, KeyWD k[], int KeyWDlen)
   文字列ｓをキーワード定義表k[](長さKeyWDlen)にある名前のキーワードの識別子に
   変換する
   戻り値　変換結果（正しく変換した場合）
   　　　　-1（エラー（キーワード定義表に名前ｓのエントリーが存在しない)
*/
int kwtoi(char *s, KeyWD k[], int KeyWDlen)
{
    int next;
    for (next=0; next<KeyWDlen; next++){
	if (strcmp(s, k[next].name)==0) return(k[next].id);
    }
    return(-1);
}

/*  void setTokens(token token[],int nt, KeyWD k[], int KeyWDlen)
    　トークンtoken[]にデータ種別(type)と値(value)を設定する
    　nt=トークン個数, KWDT=キーワード定義表，KeyWDlen=KWDTの長さ（キーワードの数）
    　戻り値　　なし

    　トークン種別 　type    　　 value
    　未定義        TKNUNDEF　　　未定義
    　キーワード    TKNKWD　      キーワードの識別子
    　整数          TKNINT　　　  整数値
    　ラベル　　　  TKNLBL        ラベルの文字数
*/
void setTokens(token token[],int nt, KeyWD k[], int KeyWDlen)
{
    int i=0,x;
    while (i<nt){
	token[i].type=TKNUNDEF;
	x = kwtoi(token[i].data,k,KeyWDlen);
	if (x >= 0){
	    token[i].type=TKNKWD;
	    token[i].value=x;}
//(* ここに解答を書き加える *)
  else{
      x = dectoi(token[i].data);
      if(x >= 0){
        token[i].type=TKNINT;
  	    token[i].value=x;
		  }else{
        x = hextoi(token[i].data);
        if(x >= 0){
          token[i].type=TKNINT;
          token[i].value=x;
        }else{
            x = isLabel(token[i].data);
            if(x > 0){
              token[i].type=TKNLBL;
              token[i].value=x;
            }else{
              token[i].value=0;
          }
        }

    }
  }
	i++;
    }
}
