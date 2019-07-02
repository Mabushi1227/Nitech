#include <stdio.h>

int main(void)
{
	int no;
	int i;
	int flag;  /* 1回でも割り切れたかどうかをあらわすフラグ */
	int max;   /* 与えられた自然数 */

	printf("自然数を入力してください：");
	scanf("%d", &max);

	printf("%dまでの素数を出力\n",max);

  for (i = 2; i <= max; i++) {
    flag = 0;

    int j;
    for (j = 2; j < i-1; j++) {
      if (i % j == 0) {
        flag = 1;
      }
    }
    if (flag == 0) {
      printf("%d\n",i);
    }
  }

  return 0;
}
