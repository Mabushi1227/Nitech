#include <stdio.h>

int main(void)
{
	int i, no;

	printf("正の整数を入力してください：");
	scanf("%d",&no);

  for (i = 1; i <= no; i++) {
    printf("%d ", i);
  }

  return 0;
}
