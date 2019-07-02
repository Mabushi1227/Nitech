#include <stdio.h>

int main(void)
{
	int i;
	int tensu[5];       /* 5人の学生の点数 */
	int sum = 0;        /* 合計点 */
	double ave;         /* 平均点 */
	double var = 0.0;   /* 分散 */

	puts("点数を入力してください。");
	for (i = 0; i < 5; i++) {
		printf("%2d番：", i + 1);
		scanf("%d", &tensu[i]);
		sum += tensu[i];
	}
	/* 平均を ave に格納 */
//
  ave = (double)sum / i;

	/* 学生の点数と平均から分散を var に計算 */
//
  for (i = 0; i < 5; i++) {
    var += (tensu[i] - ave)*(tensu[i] - ave);
  }

  var /= 5;

	printf("合計点：%5d\n", sum);
	printf("平均点：%5.1f\n", ave);
	printf("分　散：%5.1f\n", var);
}
//
