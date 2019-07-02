#include <stdio.h>
int main(void)
{
	int i,j,k;
	int mx[2][3] = { 0};
	int my[3][2] = { 0};
	int mz[2][2] = { 0};

	printf("mx:\n");
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			scanf("%d",&mx[i][j]);
		}
	}

	printf("my:\n");
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			scanf("%d",&my[i][j]);
		}
	}

//(* ここに解答を書き加える *)
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
       for (k = 0; k < 3; k++) {
         mz[i][j] += mx[i][k] * my[k][j];
       }
    }
  }


	for(i = 0; i < 2; i++) {
		for(j = 0; j < 2; j++)
			printf("%3d", mz[i][j]);
		putchar('\n');
	}
return (0);
}
//
