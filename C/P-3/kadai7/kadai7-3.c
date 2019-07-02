#include <math.h>
#include <stdio.h>
/* ２乗値を求める */
#define sqr(n)((n) * (n))

/* 点 */
typedef struct{
	/* Ｘ座標 */
	int x;
	/* Ｙ座標 */
	int y;
}point;

/* 3辺の長さを格納する構造体 */
typedef struct{
	/* 点１と点２の長さ*/
	double ab;
	/* 点２と点３の長さ*/
	double bc;
	/* 点３と点１の長さ*/
	double ca;
}tri_point;

/* 点paとpbの距離を返す */
double distanceof(point pa, point pb)
{//(* ここに解答を書き加える *)
  return sqrt(sqr(pa.x-pb.x) + sqr(pa.y-pb.y));
}

/* 3辺から三角形の面積を返す */
double triangleof(tri_point tri)
{
    double s = (tri.ab + tri.bc + tri.ca) / 2;
    return sqrt(s * (s - tri.ab) * (s - tri.bc) * (s - tri.ca));
}

int main(void)
{
	point p1,p2,p3;
	tri_point tp;

	scanf("%d", &p1.x);
	printf("点１のＸ座標：%d\n",p1.x);

	scanf("%d", &p1.y);
	printf("　　　Ｙ座標：%d\n",p1.y);

	scanf("%d", &p2.x);
	printf("点２のＸ座標：%d\n",p2.x);

	scanf("%d", &p2.y);
	printf("　　　Ｙ座標：%d\n",p2.y);

	scanf("%d", &p3.x);
	printf("点３のＸ座標：%d\n",p3.x);

	scanf("%d", &p3.y);
	printf("　　　Ｙ座標：%d\n",p3.y);

	/* 3辺の長さを構造体に格納 */
//(* ここに解答を書き加える *)
  tp.ab = distanceof(p1,p2);
  tp.bc = distanceof(p2,p3);
  tp.ca = distanceof(p3,p1);

	printf("それらの点によって作られる三角形の面積は%.2fです。\n", triangleof(tp));

	return (0);
}
