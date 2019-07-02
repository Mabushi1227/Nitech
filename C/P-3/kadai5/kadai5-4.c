#include <stdio.h>

int main(void){
	int a,b;
	int *p;
	a=10; b=20;
/* ポインタpにaのアドレスを代入 */
//(* ここに解答を書き加える *)
p = &a;

	printf("(1) a=%3d b=%3d *p=%3d\n",a,b,*p);
//	printf("(1) &a=%3d &b=%3d p=%3d\n",&a,&b,p);
/* ポインタpの指す先の値に「30（整数値）」を代入 */
//(* ここに解答を書き加える *)
*p = 30;
	printf("(2) a=%3d b=%3d p=%3d\n",a,b,*p);
//	printf("(2) &a=%3d &b=%3d p=%3d\n",&a,&b,p);
/* aに「100（整数値）」をｂに「200（整数値）」を代入 */
//(* ここに解答を書き加える *)
a = 100;
b = 200;

	printf("(3) a=%3d b=%3d p=%3d\n",a,b,*p);
//	printf("(3) &a=%3d &b=%3d p=%3d\n",&a,&b,p);
/* ポインタpにbのアドレスを代入 */
//(* ここに解答を書き加える *)
p = &b;
	printf("(4) a=%3d b=%3d p=%3d\n",a,b,*p);
//	printf("(4) &a=%3d &b=%3d p=%3d\n",&a,&b,p);

	return (0);
}
