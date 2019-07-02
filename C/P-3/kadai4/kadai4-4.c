#include <stdio.h>

int factorial(int n)
{
//(* ここに解答を書き加える *)
  if(n == 0 || n == 1){
    return 1;
  }else{
    return factorial(n-1) * n;
  }

}

int main(void)
{
	int num;

	printf("整数を入力してください：");
	scanf("%d",&num);

	printf("\nその数の階乗は%dです。\n",factorial(num));

	return (0);
}
