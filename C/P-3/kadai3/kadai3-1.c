/* 符号無し整数のビットを表示する */
#include <stdio.h>

/* 整数ｘ中のセットされたビット数を返す */
int count_bits(unsigned x)
{
	int count = 0;

	while (x){
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
//(* ここに解答を書き加える *)
  int i;
  for (i = int_bits()-1; i >= 0; i--) {
    putchar(((x >> i) & 1U) ? '1' : '0');
  }

}

int main(void)
{
	unsigned nx;

	printf("非負の整数を入力してください：");
	scanf("%u", &nx);
	printf("\n");

	print_bits(nx);
	putchar('\n');

	return (0);
}
