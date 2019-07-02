#include <stdio.h>
//(* ここに解答を書き加える *)
void mul(int ma[2][3],int mb[3][2],int mc[2][2]){
  int i,j;
    for (i = 0; i < 2; i++) {
      for ( j = 0; j < 2; j++) {
        mc[i][j] = ma[i][0]*mb[0][j] + ma[i][1]*mb[1][j] + ma[i][2]*mb[2][j];
      }
    }
}

int main(void){
	int i,j;
	int x[2][3] ={0};
	int y[3][2] ={0};
	int z[2][2] = {0};

	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			printf("x[%d][%d]：",i,j);
			scanf("%d",&x[i][j]);
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			printf("y[%d][%d]：",i,j);
			scanf("%d",&y[i][j]);
		}
	}

	mul(x,y,z);

	for(i=0;i<2;i++){
		for(j=0;j<2;j++)
		printf("%3d",z[i][j]);
		putchar('\n');
	}

	return (0);
}
