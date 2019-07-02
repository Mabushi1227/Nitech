/* 符号無し整数のビットを右に回転する */
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

/* 整数xのビットをnビット右に回転 */
//(* ここに解答を書き加える *)
unsigned rrotate(unsigned x, int n){
	int bits = int_bits();
	unsigned leftestbits = (1U << (bits - 1));

 	unsigned i ,ex;
	ex = x;
  for (i = 0; i < n; i++) {
  	if(ex & 1U){
			ex >>= 1;
			ex += leftestbits;
		}else{
			ex >>= 1;
		}
  }
	return ex;
}

int main(void)
{
	unsigned nx,no;

	printf("非負の整数を入力してください：");
	scanf("%u", &nx);
	printf("何ビット回転しますか：");
	scanf("%u", &no);
	printf("\n回転前＝");
	print_bits(nx);
	printf("\n回転後＝");
	print_bits(rrotate(nx,no));
	putchar('\n');

	return (0);
}
