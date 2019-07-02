/* 翌日を求める関数 */
#include <stdio.h>
/* 閏年とそうでない年の月毎の日数を保持 */
int day[2][13] = {
{ 0,31,28,31,30,31,30,31,31,30,31,30,31 },
{ 0,31,29,31,30,31,30,31,31,30,31,30,31 },
};
//(* ここに解答を書き加える *)
int isleap(int y){
  if((y % 4) == 0){
    if((y % 100 == 0) && (y % 400 != 0)){
      return 0;
    }else{
      return 1;
    }
  }else{
    return 0;
  }
}

void tomorrow(int *y, int *m, int *d){
  int r_isl = isleap(*y);

  //その日が月の最終日かそうでないか
  if(*d == (day[r_isl][*m])){
    *d = 1;
    if(*m == 12){
      *y += 1;
      *m = 1;
    }else{
      *m += 1;
    }
  }else{
    *d += 1;
  }
}

int main(void)
{
int y, m, d;
int ay, am, ad;
int by, bm, bd;

printf("年："); scanf("%d",&y);
printf("月："); scanf("%d",&m);
printf("日："); scanf("%d",&d);

ay = by = y;
am = bm = m;
ad = bd = d;

tomorrow(&ay, &am, &ad); /* 次の日 */

printf("次の日：%d年%d月%d日\n", ay, am, ad);

return (0);
}
