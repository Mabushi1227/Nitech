#include <stdio.h>
#define NUMBER 16

/* 整数ｘをｙで割った商を返す */
int get_div(unsigned x,int y)
{
//(* ここに解答を書き加える *)
 return x/y;
}

/* 整数ｘをｙで割った余りを返す */
int get_mod(unsigned x,int y)
{
//(* ここに解答を書き加える *)
  return x%y;
}

/* 整数ｘを16進数で表した時の桁数を返す */
/* 例 x=3のときの値:1, x=17のときの値：2, x=300のときの値：3 */
int count_digits(unsigned x)
{
//(* ここに解答を書き加える *)
  int bits = 0;
  while(x){
    if(x & ~0U) bits++;
    x >>= 4;
  }
  return bits;
}

/* 整数baseのｘ乗の値を返す */
/* 例 base=2,x=3のときの値:8, base=5,x=5のときの値：3125 */
int get_pow(int base,int x)
{
//(* ここに解答を書き加える *)
  int i;
  int ex = 1;
  for (i = 0; i < x; i++) {
    ex = ex * base;
  }
  return ex;
}

int main(void)
{
	unsigned nx;
	int lim,ny,nz;

	lim = NUMBER;
	printf("非負の整数を入力してください：");
	scanf("%u", &nx);
	putchar('\n');

	ny = count_digits(nx);
	while(get_div(nx,lim) || ny > 1){
		nz = get_pow(NUMBER,ny - 1);
		printf("%X",get_div(nx,nz));
		nx = get_mod(nx,nz);
		ny--;
	}
	printf("%X",get_mod(nx,lim));

	putchar('\n');

	return (0);
}
//
