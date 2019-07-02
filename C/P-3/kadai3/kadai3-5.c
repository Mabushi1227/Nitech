#include <stdio.h>

/* 整数ｘ中のセットされたビット数を返す */
int count_bits(unsigned x)
{
	int count = 0;

	while (x) {
		if(x & 1U) count++;
		x >>= 1;
	}

	return (count);
}

/* unsigned型のビット数を返す */
int int_bits(void)
{
	return (count_bits(~0U));
}

/* unsigned型のビット内容を表示 */
void print_bits(unsigned x)
{
	int i;

	for(i=int_bits()-1;i>=0;i--)
		putchar(((x >> i) & 1U) ? '1' : '0');
}

//(* ここに解答を書き加える *)
unsigned lsft(unsigned x, int n){
  return x <<= n;
}
unsigned set_n(unsigned x, int pos, int n){
  int seebit = pos;
  int i;
  for ( i = 0; i < n; i++) {
    if((x >> (seebit-1)) & 1U){

    }else{
      unsigned a = lsft(1U,seebit-1);
      x += a;
    }
    seebit++;
  }
  return x;
}

int main(void)
{
	unsigned nx;
	int pos,no;

	puts("符号無し整数ｘのposビット目からno個のビットを操作します。");
	printf("非負の整数ｘを入力してください：");
	scanf("%u", &nx);
	printf("操作するビット位置posを入力してください：");
	scanf("%d", &pos);
	printf("操作するビット数noを入力してください：");
	scanf("%d", &no);

	printf("\nx＝");
	print_bits(nx);
	printf("\nset_n(x,pos,no)＝");
	print_bits(set_n(nx,pos,no));
	putchar('\n');

	return (0);
}
