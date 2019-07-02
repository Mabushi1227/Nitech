#include <stdio.h>
/* ----- 三乗値を返す関数cube ------*/
//(* ここに解答を書き加える *)
  int cube(int x){
    return x*x*x;
  }

int main(void){
	int no;

	printf("整数を入力してください：");
	scanf("%d",&no);

	printf("その数の三乗値は%dです。\n",cube(no));

	return (0);
}
//
