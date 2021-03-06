#include "utils/mat.h"
#include "utils/mat_util.h"
#include "utils/simd_util.h"
#include <math.h>
#include <unistd.h>

//課題12
inline void __attribute__((always_inline)) rot(double a, double b, double &x, double &y, double radian)
{
	x = a * cos(radian);
	y = b * sin(radian);
}

//課題27
void _mm256_transpose_8x8_ps(__m256* dst, const __m256* src)
{
	__m256  tmp[8], tmpp[8];

	for (int i = 0; i < 8; i += 2)
	{
		tmp[i + 0] = _mm256_unpacklo_ps(src[i], src[i + 1]);
		tmp[i + 1] = _mm256_unpackhi_ps(src[i], src[i + 1]);
	}
	for (int i = 0; i < 8; i += 4)
	{
		tmpp[i + 0] = _mm256_shuffle_ps(tmp[i + 0], tmp[i + 2], _MM_SHUFFLE(1, 0, 1, 0));
		tmpp[i + 1] = _mm256_shuffle_ps(tmp[i + 0], tmp[i + 2], _MM_SHUFFLE(3, 2, 3, 2));
	}
	for (int i = 0; i < 8; i += 4)
	{
		tmpp[i + 2] = _mm256_shuffle_ps(tmp[i + 1], tmp[i + 3], _MM_SHUFFLE(1, 0, 1, 0));
		tmpp[i + 3] = _mm256_shuffle_ps(tmp[i + 1], tmp[i + 3], _MM_SHUFFLE(3, 2, 3, 2));
	}
	for (int i = 0; i < 4; i++)
	{
		dst[i + 0] = _mm256_permute2f128_ps(tmpp[i], tmpp[i + 4], 0x20);
		dst[i + 4] = _mm256_permute2f128_ps(tmpp[i], tmpp[i + 4], 0x31);
	}
}

int main(const int argc, const char** argv)
{
	//課題1
	//行列積和演算AX+Bを計算するプログラムにおいて，行列積と和それぞれの実行時間をタイマーを挟むことで測定せよ．
	if (false)
	{
		std::cout << "課題1" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F a(row, col);
		mat_rand(a, 0, 100);
		Mat_32F x(row, col);
		mat_rand(x, 0, 100);
		Mat_32F b(row, col);
		mat_rand(b, 0, 100);
		Mat_32F preRet(row, col);
		mat_zero(preRet);
		Mat_32F ret(row, col);
		mat_zero(ret);

		CalcTime t1;
		for (int i = 0; i < loop; i++)
		{
			t1.start();	//時間計測開始
			preRet = mat_mul(a, x);
			t1.end();	//時間計測終了
			std::cout << "time(mul): " << t1.getLastTime() << " ms" << std::endl;
		}
		std::cout << "time (avg,mul): " << t1.getAvgTime() << " ms" << std::endl;

		CalcTime t2;
		for (int i = 0; i < loop; i++)
		{
			t2.start();	//時間計測開始
			ret = mat_add(preRet, b);
			t2.end();	//時間計測終了
			std::cout << "time(add): " << t2.getLastTime() << " ms" << std::endl;
		}
		std::cout << "time (avg,add): " << t2.getAvgTime() << " ms" << std::endl;

		a.show();
		x.show();
		b.show();
		ret.show();

		return 0;
	}

	//課題2
	//行列積を計算するプログラムにおいて，コンパイラオプションを変えて計算速度の計測し，その違いを観測せよ．
	if (false)
	{
		std::cout << "課題2" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F a(row, col);
		mat_rand(a, 0, 100);
		Mat_32F b(row, col);
		mat_rand(b, 0, 100);
		Mat_32F ret(row, col);
		mat_zero(ret);

		CalcTime t;
		for (int i = 0; i < loop; i++)
		{
			t.start();
			ret = mat_mul(a, b);
			t.end();
			std::cout << "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "time (avg): " << t.getAvgTime(true) << " ms" << std::endl;

		a.show();
		b.show();
		ret.show();

		return 0;
	}

	//課題3
	//小さな行列に対して，各要素を
	//3x^4+3x^3+3
	//する計算するプログラムを作成し，乗算回数を削減する前と後で計算速度を比較せよ．
	if (false)
	{
		std::cout << "課題3" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F x(row, col);
		mat_rand(x, 0, 100);
		Mat_32F ret(row, col);
		mat_zero(ret);

		//before
		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			//3x^4+3x^3+3 そのまま
			t.start();
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*ret.cols+i]=3*pow(x.data[j*x.cols+i],4.0)+3*pow(x.data[j*x.cols+i],3.0)+3;
				}
			}
			t.end();
			std::cout << "before: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "before: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		ret.show();

		//after
		for (int k = 0; k < loop; k++)
		{
			//3x^4+3x^3+3 ホーナー法つかった場合
			t.start();
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*ret.cols+i]=3*(pow(x.data[j*x.cols+i],3.0)*(x.data[j*x.cols+i]+1))+3;
				}
			}
			t.end();
			std::cout << "after: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "after: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		ret.show();

		return 0;
	}

	//課題4
	//小さな行列に対して，各要素を下記の定数倍するプログラムを作成し，数式の展開前後で計算速度を比較せよ．
	//(2π+sqrt(5)+0.5^2)x
	if (false)
	{
		std::cout << "課題4" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F x(row, col);
		mat_rand(x, 0, 100);
		Mat_32F ret(row, col);
		mat_zero(ret);

		//before
		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			//毎回計算する場合
			t.start();
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*x.cols+i]=(2*M_PI+sqrt(5)+pow(0.5,0.5))*x.data[j*x.cols+i];
				}
			}
			t.end();
			std::cout << "before: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "before: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		ret.show();

		//after
		const float c = (2 * 3.14 + sqrt(5) + 0.5*0.5);
		for (int k = 0; k < loop; k++)
		{
			//先に計算する場合
			t.start();
			float tmp=2*M_PI+sqrt(5)+pow(0.5,0.5);
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*x.cols+i]=tmp*x.data[j*x.cols+i];
				}
			}
			t.end();
			std::cout << "after: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "after: time (avg): " << t.getAvgTime(true) << " ms" << std::endl;
		ret.show();

		return 0;
	}

	//課題5
	//小さな行列に対して，各要素を3.141592で除算する計算するプログラムを作成し，除算を削減する前と後で計算速度を比較せよ．
	//大きな行列で行うと，効果が少ない可能性があるため注意すること．
	if (false)
	{
		std::cout << "課題5" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F x(row, col);
		mat_rand(x, 0, 100);
		Mat_32F ret(row, col);
		mat_zero(ret);

		CalcTime t;

		float PI = 3.141592; //使用する円周率
		float PIr = 1 / 3.141592; //円周率の逆数

		//before

		for (int k = 0; k < loop; k++)
		{
			//除算の場合
			t.start();
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*x.cols+i]=x.data[j*x.cols+i] / PI;
				}
			}
			t.end();
			std::cout << "div: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "div: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret.show();

		//after
		for (int k = 0; k < loop; k++)
		{
			//乗算にした場合
			t.start();
			for (int j = 0; j < x.rows; j++)
			{
				for (int i = 0; i < x.cols; i++)
				{
					//計算
					ret.data[j*x.cols+i]=x.data[j*x.cols+i] * PIr;
				}
			}
			t.end();
			std::cout << "mul: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "mul: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret.show();
		return 0;
	}

	//課題6
	//小さな４つの行列A,B,C,Dに対して，行列の各要素ごとに`(a/b)*(c/d)`を計算するプログラムを作成し，除算を削減する前と後で計算速度を比較せよ．
	if (false)
	{
		std::cout << "課題6" << std::endl;
		const int loop = 10;
		const int row = 3;
		const int col = 3;
		Mat_32F a(row, col);
		mat_rand(a, 0, 100);
		Mat_32F b(row, col);
		mat_rand(b, 0, 100);
		Mat_32F c(row, col);
		mat_rand(c, 0, 100);
		Mat_32F d(row, col);
		mat_rand(d, 0, 100);
		Mat_32F ret(row, col);
		mat_zero(ret);


		CalcTime t;
		//before
		for (int k = 0; k < loop; k++)
		{
			//普通に計算
			t.start();
			for (int j = 0; j < ret.rows; j++)
			{
				for (int i = 0; i < ret.cols; i++)
				{
					//計算
					ret.data[j*ret.cols+i]=(a.data[j*a.cols+i]/b.data[j*b.cols+i]) * (c.data[j*c.cols+i]/d.data[j*d.cols+i]);
				}
			}
			t.end();
			std::cout << "before: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "before: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret.show();

		//after
		for (int k = 0; k < loop; k++)
		{
			//除算を削減した場合
			t.start();
			for (int j = 0; j < ret.rows; j++)
			{
				for (int i = 0; i < ret.cols; i++)
				{
					//計算
					ret.data[j*ret.cols+i]=(a.data[j*a.cols+i]*c.data[j*c.cols+i]) / (b.data[j*b.cols+i]*d.data[j*d.cols+i]);
				}
			}
			t.end();
			std::cout << "after: time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "after: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret.show();

		return 0;
	}

	//課題7
	//累乗を３乗，4乗．．．ｎ乗としたときに速度がどうなるのか計測せよ．ただし，累乗をすると値が大きくなるため，浮動小数点の最大値を超える可能性がある．その時は入力データを0.1倍`（i*0.1）`などすること．
	if (false)
	{
		std::cout << "課題7" << std::endl;
		const int loop = 1000;
		const int n = 50;
		const float v = 2.5f;
		float ret = 1;

	 
		for (int i = 3; i < n; i++)
		{
			CalcTime t;
			//v^i乗を計算

			for (int j = 0; j < loop; j++)
			{
				ret = 1;
				t.start();
				//pow，計算
				ret = pow(v,i);
				
				/*
				for (int k = 0; k < i; k++)
				{
					ret = ret * v;
				}*/
				t.end();
				//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
			}
			std::cout << i << " : time (avg): " << t.getAvgTime() << " ms" << std::endl;
			std::cout << ret << std::endl;
		}
		return 0;
	}


	//課題8
	//２つの行列の和を`unsigned char, short, int, float, double`で計算しそれぞれ比較せよ．
	//なお，大きい行列サイズでないと，効果がでない場合がある．
	if (false)
	{
		std::cout << "課題8" << std::endl;
		const int loop = 1000;
		const int row = 128;
		const int col = 128;

		//unsigend char
		Mat_8U a_8u(row, col);
		mat_rand(a_8u, 0, 100);
		Mat_8U b_8u(row, col);
		mat_rand(b_8u, 0, 100);
		Mat_8U ret_8u(row, col);
		mat_zero(ret_8u);

		CalcTime t;
		for (int i = 0; i < loop; i++)
		{
			t.start();
			//unsigned char
			ret_8u = mat_add(a_8u,b_8u);
			t.end();
			//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << " 8U : time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//short
		Mat_16S a_16s(row, col);
		mat_rand(a_16s, 0, 100);
		Mat_16S b_16s(row, col);
		mat_rand(b_16s, 0, 100);
		Mat_16S ret_16s(row, col);
		mat_zero(ret_16s);

		for (int i = 0; i < loop; i++)
		{
			t.start();
			//short
			ret_16s = mat_add(a_16s,b_16s);
			t.end();
			//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "16S : time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//int
		Mat_32S a_32s(row, col);
		mat_rand(a_32s, 0, 100);
		Mat_32S b_32s(row, col);
		mat_rand(b_32s, 0, 100);
		Mat_32S ret_32s(row, col);
		mat_zero(ret_32s);

		for (int i = 0; i < loop; i++)
		{
			t.start();
			//int
			ret_32s = mat_add(a_32s,b_32s);
			t.end();
			//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "32S : time (avg): " << t.getAvgTime() << " ms" << std::endl;


		//float
		Mat_32F a_32f(row, col);
		mat_rand(a_32f, 0, 100);
		Mat_32F b_32f(row, col);
		mat_rand(b_32f, 0, 100);
		Mat_32F ret_32f(row, col);
		mat_zero(ret_32f);

		for (int i = 0; i < loop; i++)
		{
			t.start();
			//float
			ret_32f = mat_add(a_32f,b_32f);
			t.end();
			//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "32F : time (avg): " << t.getAvgTime() << " ms" << std::endl;


		//double
		Mat_64F a_64f(row, col);
		mat_rand(a_64f, 0, 100);
		Mat_64F b_64f(row, col);
		mat_rand(b_64f, 0, 100);
		Mat_64F ret_64f(row, col);
		mat_zero(ret_64f);

		for (int i = 0; i < loop; i++)
		{
			t.start();
			//double
			ret_64f = mat_add(a_64f,b_64f);
			t.end();
			//std::cout<< "time: " << t.getLastTime() << " ms" << std::endl;
		}
		std::cout << "64F : time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}


	//課題9
	//intの行列を整数で2倍，浮動小数点で2.f倍,整数を１ビットだけビットシフトすることで2倍する場合の計算速度を比較せよ．
	//また，intの行列を整数で2で除算する場合，浮動小数点で2で除算する場合，浮動小数点の0.5で乗算する場合，１ビットだけビットシフトすることで1/2倍する場合の速度を比較せよ．
	//加えて，floatの行列で，2.0で除算する場合と0.5で乗算する場合を比較せよ．
	//なお，浮動小数点で乗算する場合は整数の場合よりも遅い． 
	//また，大きい行列サイズでないと，効果がでない場合がある．
	if (false)
	{
		std::cout << "課題9" << std::endl;
		const int loop = 1000;
		const int row = 50;
		const int col = 50;
		
		//int
		Mat_32S x_32s(row, col);
		mat_rand(x_32s, 0, 100);
		Mat_32S ret_32s(row, col);
		mat_zero(ret_32s);

		CalcTime t;
		//2x mul
		for (int k = 0; k < loop; k++)
		{
			//2倍 乗算
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*x_32s.cols+i] * 2;
				}
			}
			t.end();
		}
		std::cout << "2x mul: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//2.0x mul
		for (int k = 0; k < loop; k++)
		{
			//2.0倍 乗算(double)
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i]*2.f;
				}
			}
			t.end();
		}
		std::cout << "2x mul (double): time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//2x bit shift
		for (int k = 0; k < loop; k++)
		{
			//2倍 ビットシフト
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i] << 1;
				}
			}
			t.end();
		}
		std::cout << "2x bit shift: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//1/2 div int
		for (int k = 0; k < loop; k++)
		{
			//1/2 除算
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i]  / 2;
				}
			}
			t.end();
		}
		std::cout << "1/2 div: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//1/2 div float
		for (int k = 0; k < loop; k++)
		{
			//1/2 除算
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i] / 2.f;
				}
			}
			t.end();
		}
		std::cout << "1/2 div (float): time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();


		//1/2 -> mul 0.5
		for (int k = 0; k < loop; k++)
		{
			//1/2 0.5乗算で実現
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i] * 0.5;
				}
			}
			t.end();
		}
		std::cout << "1/2 mul: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//1/2->bit shift
		for (int k = 0; k < loop; k++)
		{
			//1/2 ビットシフト
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = x_32s.data[j*ret_32s.cols+i] >> 1;
				}
			}
			t.end();
		}
		std::cout << "1/2 bit shift: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32s.show();

		//float
		Mat_32F x_32f(row, col);
		mat_rand(x_32f, 0, 100);
		Mat_32F ret_32f(row, col);
		mat_zero(ret_32f);
		
		//1/2 div
		for (int k = 0; k < loop; k++)
		{
			//1/2 除算
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = x_32f.data[j*ret_32f.cols+i] / 2.0; 
				}
			}
			t.end();
		}
		std::cout << "float: 1/2 div: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//1/2 -> mul 0.5
		for (int k = 0; k < loop; k++)
		{
			//1/2 0.5乗算
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = x_32f.data[j*ret_32f.cols+i] * 0.5;
				}
			}
			t.end();
		}
		std::cout << "float: 1/2 mul: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();
		return 0;
	}

	//課題10
	//floatの行列をを3.141倍する場合と，intの行列を3.141倍を固定小数点で行う場合で計算し比較せよ．
	if (false)
	{
		std::cout << "課題10" << std::endl;
		const int loop = 1000;
		const int row = 3;
		const int col = 3;
		Mat_32S x_32s(row, col);
		mat_rand(x_32s, 0, 100);
		Mat_32S ret_32s(row, col);
		mat_zero(ret_32s);

		//int
		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			//固定小数点
			t.start();
			for (int j = 0; j < ret_32s.rows; j++)
			{
				for (int i = 0; i < ret_32s.cols; i++)
				{
					ret_32s.data[j*ret_32s.cols+i] = (3216 * x_32s.data[j*ret_32s.cols+i]) >> 10;
				}
			}
			t.end();
		}
		std::cout << "fixed: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret_32s.show();

		Mat_32F x_32f(row, col);
		mat_rand(x_32f, 0, 100);
		Mat_32F ret_32f(row, col);
		mat_zero(ret_32f);

		//float
		for (int k = 0; k < loop; k++)
		{
			//浮動小数点
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = x_32f.data[j*ret_32f.cols+i] * 3.141;
				}
			}
			t.end();
		}
		std::cout << "float: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		ret_32f.show();

		return 0;
	}

	//課題11
	//floatの行列への定数値の四則演算と，`sin, cos, exp, log, sqrt`関数の適用した場合と計算時間を比較せよ．
	//また，`sin, cos, exp, log, sqrt`計算はテーブル参照も作成した場合についても比較せよ．
	//なお，環境によっては，演算したほうが速い演算もある可能性がある．
	if (false)
	{
		std::cout << "課題11" << std::endl;
		const int loop = 100;
		const int row = 50;
		const int col = 50;
		Mat_8U x_8u(row, col);
		mat_rand(x_8u, 0, 255);

		Mat_32F x_32f(x_8u);
		Mat_32F ret_32f(row, col);
		mat_zero(ret_32f);

		//四則演算
		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			//四則演算
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = x_32f.data[j*ret_32f.cols+i] * 3.141;
				}
			}
			t.end();
		}
		std::cout << "arithmetic: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//ret_32f.show();

		//sin
		for (int k = 0; k < loop; k++)
		{
			//sin関数
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = sin(x_32f.data[j*ret_32f.cols+i]);
				}
			}
			t.end();
		}
		std::cout << "sin: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//cos
		for (int k = 0; k < loop; k++)
		{
			//cos関数
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = cos(x_32f.data[j*ret_32f.cols+i]);
				}
			}
			t.end();
		}
		std::cout << "cos: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//exp
		for (int k = 0; k < loop; k++)
		{
			//exp関数
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = exp(x_32f.data[j*ret_32f.cols+i]);
				}
			}
			t.end();
		}
		std::cout << "exp: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//log
		for (int k = 0; k < loop; k++)
		{
			//log関数
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = log(x_32f.data[j*ret_32f.cols+i]);
				}
			}
			t.end();
		}
		std::cout << "log: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//sqrt
		for (int k = 0; k < loop; k++)
		{
			//sqrt関数
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols+i] = sqrt(x_32f.data[j*ret_32f.cols+i]);
				}
			}
			t.end();
		}
		std::cout << "sqrt: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		std::cout << std::endl;
		//sin LUT
		float LUT[256];
		for (int i = 0; i < 256; i++)
		{
			//LUT作成
			LUT[i] = sin(i);
		}
		for (int k = 0; k < loop; k++)
		{
			t.start();
			//sin LUT
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols + i] = LUT[(int)x_32f.data[j*ret_32f.cols + i]];
				}
			}
			t.end();
		}
		std::cout << "sin LUT: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//cos LUT
		for (int i = 0; i < 256; i++)
		{
			//LUT作成
			LUT[i] = cos(i);
		}
		for (int k = 0; k < loop; k++)
		{
			//cos LUT
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols + i] = LUT[(int)x_32f.data[j*ret_32f.cols + i]];
				}
			}
			t.end();
		}
		std::cout << "cos LUT: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//exp LUT
		for (int i = 0; i < 256; i++)
		{
			//LUT作成
			LUT[i] = exp(i);
		}
		for (int k = 0; k < loop; k++)
		{
			//exp LUT
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols + i] = LUT[(int)x_32f.data[j*ret_32f.cols + i]];
				}
			}
			t.end();
		}
		std::cout << "exp LUT: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//log LUT
		for (int i = 0; i < 256; i++)
		{
			//LUT作成
			LUT[i] = log(i);
		}
		for (int k = 0; k < loop; k++)
		{
			//log LUT
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols + i] = LUT[(int)x_32f.data[j*ret_32f.cols + i]];
				}
			}
			t.end();
		}
		std::cout << "log LUT: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		//sqrt LUT
		for (int i = 0; i < 256; i++)
		{
			//LUT作成
			LUT[i] = sqrt(i);
		}
		for (int k = 0; k < loop; k++)
		{
			//sqrt LUT
			t.start();
			for (int j = 0; j < ret_32f.rows; j++)
			{
				for (int i = 0; i < ret_32f.cols; i++)
				{
					ret_32f.data[j*ret_32f.cols + i] = LUT[(int)x_32f.data[j*ret_32f.cols + i]];
				}
			}
			t.end();
		}
		std::cout << "sqrt LUT: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//ret_32f.show();

		return 0;
	}

	//課題12
	//小さな行列A,Bの各要素を任意のradianだけ回転させて，x,yにして格納するプログラムを記述し，inline展開の有無で速度がどのように変わるか計測せよ．
	//また，関数をべた書きした場合とも比較せよ．
	//ただし，-O3のオプションを付けると強制的にinline展開される可能性がある．
//	inline void rot(double a, double b, double &x, double &y, double radian)
//	{
//		x = a * cos(radian);
//		y = b * sin(radian);
//	}
	if (false)
	{
		std::cout << "課題12" << std::endl;
		const int loop = 10000;
		const int row = 3;
		const int col = 3;
		Mat_64F a(row, col);
		mat_rand(a, 0, 100);
		Mat_64F b(row, col);
		mat_rand(b, 0, 100);

		Mat_64F x(row, col);
		mat_zero(x);
		Mat_64F y(row, col);
		mat_zero(y);

		const float radian = 2.2f;
		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			t.start();
			for (int j = 0; j < a.rows; j++)
			{
				for (int i = 0; i < a.cols; i++)
				{
					//rotべた書き
					/*
					x.data[j*x.cols + i] = a.data[j*a.cols + i] * cos(radian);
					y.data[j*y.cols + i] = b.data[j*a.cols + i] * cos(radian);
					*/
					//rotインライン呼び出し
					rot(a.data[j*x.cols + i],b.data[j*x.cols + i],x.data[j*x.cols + i],y.data[j*x.cols + i],radian);
	
				}
			}
			t.end();
		}
		std::cout << "time (avg): " << t.getAvgTime() << " ms" << std::endl;
		return 0;
	}

	//課題13
	//行列A，Bの各要素の乗算を行うときに，結果を行列Cに格納する場合と行列Aに上書きする場合との計算時間をせよ．
	if (false)
	{
		std::cout << "課題13" << std::endl;
		const int loop = 10000;
		const int row = 3;
		const int col = 3;
		//c = a x b
		{
			Mat_64F c(row, col);
			mat_zero(c);

			CalcTime t;
			for (int k = 0; k < loop; k++)
			{
				t.start();
				//C=A*B
				Mat_64F a(row, col);
				mat_rand(a, 0, 100);
				Mat_64F b(row, col);
				mat_rand(b, 0, 100);
				for (int j = 0; j < a.rows; j++)
				{
					for (int i = 0; i < a.cols; i++)
					{
						c.data[j*a.cols + i] = a.data[j*a.cols + i] * b.data[j*a.cols + i]; 
					}
				}
				t.end();
				//c.show();
			}
			std::cout << "c=a*b: time (avg): " << t.getAvgTime() << " ms" << std::endl;
			
		}

		//a = a x b
		{

			CalcTime t;
			for (int k = 0; k < loop; k++)
			{
				t.start();
				//A=AxB
				Mat_64F a(row, col);
				mat_rand(a, 0, 100);
				Mat_64F b(row, col);
				mat_rand(b, 0, 100);
				for (int j = 0; j < a.rows; j++)
				{
					for (int i = 0; i < a.cols; i++)
					{
						a.data[j*a.cols + i] = a.data[j*a.cols + i] * b.data[j*a.cols + i]; 
					}
				}
				t.end();
				//a.show();
			}
			std::cout << "a=a*b: time (avg): " << t.getAvgTime() << " ms" << std::endl;
			
		}

		return 0;
	}

	//課題14
	//上記の0で初期化するコードをループの順序を変えてどちらが速いか計測して検証せよ．
	//また，行列積のコードのループの順序を変えてどれが速いか計測して検証せよ．
	if (false)
	{
		std::cout << "課題14" << std::endl;
		const int loop = 1000;
		const int width = 64;
		const int height = 64;
		float x[width][height];

		CalcTime t;
		//col, row
		for (int k = 0; k < loop; k++)
		{
			t.start();
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					x[i][j] = 0.0f;
				}
			}
			t.end();
		}
		std::cout << "col-row: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//row, col
		for (int k = 0; k < loop; k++)
		{
			t.start();
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					x[i][j] = 0.0f;
				}
			}
			t.end();
		}
		std::cout << "row-col: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		const int size = 64;
		float a[size][size];
		float b[size][size];
		float c[size][size];
		//init
		for (int j = 0; j < size; j++)
		{
			for (int i = 0; i < size; i++)
			{
				a[j][i] = rand_32f(0, 100);
				b[j][i] = rand_32f(0, 100);
				c[j][i] = 0;
			}
		}

		//i, j, k
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int i = 0; i < size; ++i)
			{
				for (int j = 0; j < size; ++j)
				{
					for (int k = 0; k < size; ++k)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "i-j-k: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//i, k, j
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					for (int j = 0; j < size; ++j)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "i-k-j: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//j, i, k
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; ++i)
				{
					for (int k = 0; k < size; ++k)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "j-i-k: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//j, k, i
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int j = 0; j < size; ++j)
			{
				for (int k = 0; k < size; ++k)
				{
					for (int i = 0; i < size; ++i)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "j-k-i: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//k, i, j
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int k = 0; k < size; ++k)
			{
				for (int i = 0; i < size; ++i)
				{
					for (int j = 0; j < size; ++j)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "k-i-j: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//k, j, i
		for (int l = 0; l < loop; l++)
		{
			t.start();
			for (int k = 0; k < size; ++k)
			{
				for (int j = 0; j < size; ++j)
				{
					for (int i = 0; i < size; ++i)
					{
						c[i][j] = c[i][j] + a[i][k] * b[k][j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "k-j-i: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}


	//課題15
	//アンローリングの段数を2,4,8,16,32,...と変更することで，速度がどのように変わるか計測せよ．
	if (false)
	{
		std::cout << "課題15" << std::endl;
		const int loop = 100;
		const int size = 1024;
		float x[size], y[size];
		float a = 2.f;
		float b = 1.f;

		for (int i = 0; i < size; i++)
		{
			x[i] = rand_32f(0, 100);
		}

		CalcTime t;
		//unrolling 1
		for (int j = 0; j < loop; j++)
		{
			//unrolling 1
			t.start();
			for (int i = 0; i < size; i++)
			{
				y[i + 0] = a * x[i + 0] + b;
			}
			t.end();
		}
		std::cout << "no unrolling: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 2
		for (int j = 0; j < loop; j++)
		{
			//unrolling 2
			t.start();
			for (int i = 0; i < size; i += 2)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
			}
			t.end();
		}
		std::cout << "unrolling  2: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 4
		for (int j = 0; j < loop; j++)
		{
			//unrolling 4
			t.start();
			for (int i = 0; i < size; i += 4)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
				y[i + 2] = a * x[i + 2] + b;
				y[i + 3] = a * x[i + 3] + b;
			}
			t.end();
		}
		std::cout << "unrolling  4: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 8
		for (int j = 0; j < loop; j++)
		{
			//unrolling 8
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
				y[i + 2] = a * x[i + 2] + b;
				y[i + 3] = a * x[i + 3] + b;
				y[i + 4] = a * x[i + 4] + b;
				y[i + 5] = a * x[i + 5] + b;
				y[i + 6] = a * x[i + 6] + b;
				y[i + 7] = a * x[i + 7] + b;
			}
			t.end();
		}
		std::cout << "unrolling  8: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 16
		for (int j = 0; j < loop; j++)
		{
			//unrolling 16
			t.start();
			for (int i = 0; i < size; i += 16)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
				y[i + 2] = a * x[i + 2] + b;
				y[i + 3] = a * x[i + 3] + b;
				y[i + 4] = a * x[i + 4] + b;
				y[i + 5] = a * x[i + 5] + b;
				y[i + 6] = a * x[i + 6] + b;
				y[i + 7] = a * x[i + 7] + b;
				y[i + 8] = a * x[i + 8] + b;
				y[i + 9] = a * x[i + 9] + b;
				y[i + 10] = a * x[i + 10] + b;
				y[i + 11] = a * x[i + 11] + b;
				y[i + 12] = a * x[i + 12] + b;
				y[i + 13] = a * x[i + 13] + b;
				y[i + 14] = a * x[i + 14] + b;
				y[i + 15] = a * x[i + 15] + b;
			}
			t.end();
		}
		std::cout << "unrolling 16: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 32
		for (int j = 0; j < loop; j++)
		{
			//unrolling 32
			t.start();
			for (int i = 0; i < size; i += 32)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
				y[i + 2] = a * x[i + 2] + b;
				y[i + 3] = a * x[i + 3] + b;
				y[i + 4] = a * x[i + 4] + b;
				y[i + 5] = a * x[i + 5] + b;
				y[i + 6] = a * x[i + 6] + b;
				y[i + 7] = a * x[i + 7] + b;
				y[i + 8] = a * x[i + 8] + b;
				y[i + 9] = a * x[i + 9] + b;
				y[i + 10] = a * x[i + 10] + b;
				y[i + 11] = a * x[i + 11] + b;
				y[i + 12] = a * x[i + 12] + b;
				y[i + 13] = a * x[i + 13] + b;
				y[i + 14] = a * x[i + 14] + b;
				y[i + 15] = a * x[i + 15] + b;
				y[i + 16] = a * x[i + 16] + b;
				y[i + 17] = a * x[i + 17] + b;
				y[i + 18] = a * x[i + 18] + b;
				y[i + 19] = a * x[i + 19] + b;
				y[i + 20] = a * x[i + 20] + b;
				y[i + 21] = a * x[i + 21] + b;
				y[i + 22] = a * x[i + 22] + b;
				y[i + 23] = a * x[i + 23] + b;
				y[i + 24] = a * x[i + 24] + b;
				y[i + 25] = a * x[i + 25] + b;
				y[i + 26] = a * x[i + 26] + b;
				y[i + 27] = a * x[i + 27] + b;
				y[i + 28] = a * x[i + 28] + b;
				y[i + 29] = a * x[i + 29] + b;
				y[i + 30] = a * x[i + 30] + b;
				y[i + 31] = a * x[i + 31] + b;
			}
			t.end();
		}
		std::cout << "unrolling 32: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//unrolling 64
		for (int j = 0; j < loop; j++)
		{
			//unrolling 64
			t.start();
			for (int i = 0; i < size; i += 64)
			{
				y[i + 0] = a * x[i + 0] + b;
				y[i + 1] = a * x[i + 1] + b;
				y[i + 2] = a * x[i + 2] + b;
				y[i + 3] = a * x[i + 3] + b;
				y[i + 4] = a * x[i + 4] + b;
				y[i + 5] = a * x[i + 5] + b;
				y[i + 6] = a * x[i + 6] + b;
				y[i + 7] = a * x[i + 7] + b;
				y[i + 8] = a * x[i + 8] + b;
				y[i + 9] = a * x[i + 9] + b;
				y[i + 10] = a * x[i + 10] + b;
				y[i + 11] = a * x[i + 11] + b;
				y[i + 12] = a * x[i + 12] + b;
				y[i + 13] = a * x[i + 13] + b;
				y[i + 14] = a * x[i + 14] + b;
				y[i + 15] = a * x[i + 15] + b;
				y[i + 16] = a * x[i + 16] + b;
				y[i + 17] = a * x[i + 17] + b;
				y[i + 18] = a * x[i + 18] + b;
				y[i + 19] = a * x[i + 19] + b;
				y[i + 20] = a * x[i + 20] + b;
				y[i + 21] = a * x[i + 21] + b;
				y[i + 22] = a * x[i + 22] + b;
				y[i + 23] = a * x[i + 23] + b;
				y[i + 24] = a * x[i + 24] + b;
				y[i + 25] = a * x[i + 25] + b;
				y[i + 26] = a * x[i + 26] + b;
				y[i + 27] = a * x[i + 27] + b;
				y[i + 28] = a * x[i + 28] + b;
				y[i + 29] = a * x[i + 29] + b;
				y[i + 30] = a * x[i + 30] + b;
				y[i + 31] = a * x[i + 31] + b;				
				y[i + 32] = a * x[i + 32] + b;
				y[i + 33] = a * x[i + 33] + b;
				y[i + 34] = a * x[i + 34] + b;
				y[i + 35] = a * x[i + 35] + b;
				y[i + 36] = a * x[i + 36] + b;
				y[i + 37] = a * x[i + 37] + b;
				y[i + 38] = a * x[i + 38] + b;
				y[i + 39] = a * x[i + 39] + b;
				y[i + 40] = a * x[i + 40] + b;
				y[i + 41] = a * x[i + 41] + b;
				y[i + 42] = a * x[i + 42] + b;
				y[i + 43] = a * x[i + 43] + b;
				y[i + 44] = a * x[i + 44] + b;
				y[i + 45] = a * x[i + 45] + b;
				y[i + 46] = a * x[i + 46] + b;
				y[i + 47] = a * x[i + 47] + b;
				y[i + 48] = a * x[i + 48] + b;
				y[i + 49] = a * x[i + 49] + b;
				y[i + 50] = a * x[i + 50] + b;
				y[i + 51] = a * x[i + 51] + b;
				y[i + 52] = a * x[i + 52] + b;
				y[i + 53] = a * x[i + 53] + b;
				y[i + 54] = a * x[i + 54] + b;
				y[i + 55] = a * x[i + 55] + b;
				y[i + 56] = a * x[i + 56] + b;
				y[i + 57] = a * x[i + 57] + b;
				y[i + 58] = a * x[i + 58] + b;
				y[i + 59] = a * x[i + 59] + b;
				y[i + 60] = a * x[i + 60] + b;
				y[i + 61] = a * x[i + 61] + b;
				y[i + 62] = a * x[i + 62] + b;
				y[i + 63] = a * x[i + 63] + b;
			}
			t.end();
		}
		std::cout << "unrolling 64: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}

	//課題16
	//上記のプログラムを実装し，ループピーリングの有無で速度がどのように変わるか計測せよ．
	if (false)
	{
		std::cout << "課題16" << std::endl;
		const int loop = 100;
		const int size = 1024;
		int x[size], y[size];

		for (int i = 0; i < size; i++)
		{
			x[i] = rand_32f(0, 100);
			y[i] = rand_32f(0, 100);
		}

		CalcTime t;
		//original
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; ++i)
			{
				if (i == 0)
				{
					y[i] = (x[i] + x[i + 1]) / 2;
				}
				else if (i == size - 1)
				{
					y[i] = (x[i - 1] + x[i]) / 2;
				}
				else
				{
					y[i] = (x[i - 1] + x[i] + x[i + 1]) / 3;
				}
			}
			t.end();
		}
		std::cout << "original: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//Loop peeling
		for (int j = 0; j < loop; j++)
		{
			t.start();
			{
				y[0] = (x[0] + x[1]) / 2;
				for (int i = 1; i < size-1; i++)
				{
					y[i] = (x[i - 1] + x[i] + x[i + 1]) / 3;
				}
				y[size-1] = (x[size-2] + x[size-1]) / 2;
				
			}
			t.end();
		}
		std::cout << "loop peeling: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}

	//課題17
	//上記のコードで，計算時間を比較せよ．
	//なお，必ずしも差がでるとは限らない（配列の大きさを変更すると差が出やすい）．
	if (false)
	{
		std::cout << "課題17" << std::endl;
		const int loop = 100;
		const int width = 768;
		const int height = 512;
		float a[height][width];

		CalcTime t;
		// before
		for (int k = 0; k < loop; k++)
		{
			t.start();
			for (int j = 0; j < height; j++)
			{
				for (int i = 0; i < width; i++)
				{
					a[j][i] = 0.f;
				}
			}
			t.end();
		}
		std::cout << "before: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//after
		const int size = width * height;
		for (int k = 0; k < loop; k++)
		{
			t.start();
			float *p = &a[0][0];
			for (int i = 0; i < size; i++) {
				*p++ = 0.f;
			}
			t.end();
		}
		std::cout << "after: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}

	//課題18
	//上記のコードを実行し，並列に動作していることを確認せよ．
	//また，並列化を有効にする場合としない場合の計算時間を比較せよ．
	if (false)
	{
		std::cout << "課題18" << std::endl;
		CalcTime t;
		#pragma omp parallel for
		for (int i = 0; i < 100; i++)
		{
			t.start();
			std::cout << i << std::endl; //並列化したい処理
			t.end();
		}
		std::cout << "parallel: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//std::cout << "no parallel: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}

	//課題19
	//総和を計算するコードで，reduction指定子を使用する場合としない場合で計算結果がどのようになるか比較せよ．
	if (false)
	{
		std::cout << "課題19" << std::endl;
		//並列化なし
		std::cout << "no parallelization" << std::endl;
		for (int j = 0; j < 10; j++)
		{
			int sum = 0;
			for (int i = 0; i < 100; i++)
			{
				sum += i;
			}
			std::cout << sum << std::endl;
		}

		//omp使用
		std::cout << "parallelization" << std::endl;
		for (int j = 0; j < 10; j++)
		{
			int sum = 0;
			#pragma omp parallel for
			for (int i = 0; i < 100; i++)
			{
				sum += i;
			}
			std::cout << sum << std::endl;
		}

		//omp reduction使用
		std::cout << "parallelization with reduction" << std::endl;
		for (int j = 0; j < 10; j++)
		{
			int sum = 0;
			#pragma omp parallel for reduction(+: sum)
			for (int i = 0; i < 100; i++)
			{
				sum += i;
			}
			std::cout << sum << std::endl;
		}
		return 0;
	}

	//課題20
	//二つの行列の各要素の積を計算するコードで，スレッド数を変更して，計算時間がどのように推移するのかを確認せよ．
	if (false)
	{
		std::cout << "課題20" << std::endl;
		const int loop = 1000;
		const int size = 128;
		Mat_32F a(size, size);
		mat_rand(a, 0, 100);
		Mat_32F b(size, size);
		mat_rand(b, 0, 100);
		Mat_32F c(size, size);

		CalcTime t;
		for (int l = 0; l < loop; l++)
		{
			mat_zero(c);
			t.start();
			//omp num_threads(n)で並列化，nを入れる
			#pragma omp parallel for num_threads(4)
			//#pragma omp parallel for
			for (int i = 0; i < size; ++i)
			{
				for (int k = 0; k < size; ++k)
				{
					for (int j = 0; j < size; ++j)
					{
						c.data[i*c.cols + j] = c.data[i*c.cols + j] + a.data[i*a.cols + k] * b.data[k*b.cols + j];
					}
				}
			}
			t.end();
			//std::cout << "time : " << t.getLastTime() << std::endl;
		}
		std::cout << "time (avg): " << t.getAvgTime() << " ms" << std::endl;
		return 0;
	}

	//課題21
	//四則演算のコードを書いてprintfデバッグで確認せよ．
	if (false)
	{
		std::cout << "課題21" << std::endl;
		const __m256 a = _mm256_set_ps(7, 6, 5, 4, 3, 2, 1, 0);
		const __m256 b = _mm256_set_ps(15, 14, 13, 12, 11, 10, 9, 8);

		__m256 c;
		//加算
		c = _mm256_add_ps(a,b);
		std::cout << "add: ";
		print_m256(c);

		//減算
		c = _mm256_sub_ps(a,b);
		std::cout << "sub: ";
		print_m256(c);

		//乗算
		c = _mm256_mul_ps(a,b);
		std::cout << "mul: ";
		print_m256(c);

		//除算
		c = _mm256_div_ps(a,b);
		std::cout << "div: ";
		print_m256(c);

		return 0;
	}


	//課題22
	//配列a,x,bに対して，`(((a*x+b)*x+b)*x+b)*x+b `の計算を配列ｃに格納するコードをmul/addで記述するものとFMAを使うもので記述し，FMAが速くなることを示せ．
	//なお，上記の関数は以下に等しい．
	//a=_mm256_fmadd_ps(a,b,c);
	//a=_mm256_fmadd_ps(a,b,c);
	//a=_mm256_fmadd_ps(a,b,c);
	//a=_mm256_fmadd_ps(a,b,c);
	//これは，単純にFMAが1度だとメモリで律速するこのコードでは計算速度の差が出にくいためである．差が小さければ，より演算を増やせば良い．
	if (false)
	{
		std::cout << "課題22" << std::endl;
		const int loop = 1000;
		const int size = 1024;
#ifdef __GNUC__
		float __attribute__((aligned(32))) a[size];
		float __attribute__((aligned(32))) x[size];
		float __attribute__((aligned(32))) b[size];
		float __attribute__((aligned(32))) c[size];
#elif _MSC_VER
		float __declspec(align(32)) a[size];
		float __declspec(align(32)) x[size];
		float __declspec(align(32)) b[size];
		float __declspec(align(32)) c[size];
#endif

		//init
		for (int i = 0; i < size; i++)
		{
			a[i] = rand_32f(0, 100);
			x[i] = rand_32f(0, 100);
			b[i] = rand_32f(0, 100);
			c[i] = 0;
		}

		CalcTime t;
		//mul, add
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mx = _mm256_load_ps(x + i);
				const __m256 mb = _mm256_load_ps(b + i);

				//mul,addを使って
				__m256 temp;
				temp = _mm256_mul_ps(ma,mx);
				temp = _mm256_add_ps(temp,mb);
				temp = _mm256_mul_ps(temp,mx);
				temp = _mm256_add_ps(temp,mb);
				temp = _mm256_mul_ps(temp,mx);
				temp = _mm256_add_ps(temp,mb);

				_mm256_store_ps(c + i, temp);
			}
			t.end();
		}
		std::cout << "mul-add: time (avg): " << t.getAvgTime() << " ms" << std::endl;


		//fma
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mx = _mm256_load_ps(x + i);
				const __m256 mb = _mm256_load_ps(b + i);

				//fmaを使って
				__m256 temp;
				temp=_mm256_fmadd_ps(ma,mx,mb);
				temp=_mm256_fmadd_ps(temp,mx,mb);
				temp=_mm256_fmadd_ps(temp,mx,mb);
				temp=_mm256_fmadd_ps(temp,mx,mb);
				_mm256_store_ps(c + i, temp);
			}
			t.end();
		}
		std::cout << "fma: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}


	//課題23
	//divとrcp,sqrtとrsqrtの実行速度を比較せよ．
	if (false)
	{
		std::cout << "課題23" << std::endl;
		const int loop = 10000;
		const int size = 1024;
#ifdef __GNUC__
		float __attribute__((aligned(32))) a[size];
		float __attribute__((aligned(32))) b[size];
#elif _MSC_VER
		__declspec(align(32)) float a[size];
		__declspec(align(32)) float b[size];
#endif

		for (int i = 0; i < size; i++)
		{
			a[i] = rand_32f(0, 100);
			b[i] = rand_32f(0, 100);
		}

		CalcTime t;
		//div
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mb = _mm256_load_ps(b + i);

				__m256 temp;
				//divを使って
				temp = _mm256_div_ps(ma,mb);
				//_mm256_store_ps(c+i, temp);
			}
			t.end();
		}
		std::cout << "div: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//rcp
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mb = _mm256_load_ps(b + i);

				__m256 temp;
				//rcpをつかって
				temp = _mm256_rcp_ps(mb);
				temp = _mm256_mul_ps(ma,temp);
				//_mm256_store_ps(c+i, temp);
			}
			t.end();
		}
		std::cout << "rcp: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//sqrt
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mb = _mm256_load_ps(b + i);

				__m256 temp;
				//sqrtを使って
				temp = _mm256_sqrt_ps(mb);
				temp = _mm256_mul_ps(ma,temp);
				//_mm256_store_ps(c+i, temp);				
			}
			t.end();
		}
		std::cout << "sqrt: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		//rsqrt
		for (int j = 0; j < loop; j++)
		{
			t.start();
			for (int i = 0; i < size; i += 8)
			{
				const __m256 ma = _mm256_load_ps(a + i);
				const __m256 mb = _mm256_load_ps(b + i);

				__m256 temp;
				//rsqrtを使って
				temp = _mm256_rsqrt_ps(ma);
				temp = _mm256_rcp_ps(temp);
				//_mm256_store_ps(c+i, temp);
			}
			t.end();
		}
		std::cout << "rsqrt: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}


	//課題24
	//haddとdpで要素の総和を取るプログラムを作成せよ．
	//また，それぞれの計算時間を比較せよ ．
	//（この課題は，後にリダクションの最適化でもう一度登場します．）
	if (false)
	{
		std::cout << "課題24" << std::endl;
		const int loop = 100000;
#ifdef __GNUC__
		float __attribute__((aligned(32))) a[8];
		float __attribute__((aligned(32))) b[8];
#elif _MSC_VER
		__declspec(align(32)) float a[8];
		__declspec(align(32)) float b[8];
#endif

		float sum = 0.f;
		for (int i = 0; i < 8; i++)
		{
			a[i] = rand_32f(0, 100);
			//b[i] = rand_32f(0, 100);
		}

		CalcTime t;
		//hadd
		for (int i = 0; i < loop; i++)
		{
			t.start();
			__m256 ma = _mm256_load_ps(a);
			//haddを使って
			ma = _mm256_hadd_ps(ma,ma);
			ma = _mm256_hadd_ps(ma,ma);
			sum = ((float*)&ma)[0]+((float*)&ma)[4];
			t.end();
		}
		std::cout << "hadd: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		std::cout <<  "sum: " << sum << std::endl;


		const __m256 one = _mm256_set1_ps(1);
		//dp
		for (int i = 0; i < loop; i++)
		{
			t.start();
			__m256 mb = _mm256_load_ps(a);
			//dpを使って
			mb =_mm256_dp_ps(mb,one,0xff);
			sum = ((float*)&mb)[0]+((float*)&mb)[4];
			t.end();
		}
		std::cout << "dp: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		std::cout <<  "sum: " << sum << std::endl;
		return 0;
	}

	//課題25
	//行列aにおいて要素の値があるしきい値以上の場合だけ3乗し，それ以外は何もしない処理をベクトル化実装せよ．
	//if(a[i]>=threshold) a[i]=a[i]*a[i]*a[i];
	if (false)
	{
		std::cout << "課題25" << std::endl;
		const int size = 8;
		const float th = 50;

#ifdef __GNUC__
		float __attribute__((aligned(32))) a[size];
#elif _MSC_VER
		__declspec(align(32)) float a[size];
#endif

		__m256 md = _mm256_set1_ps(2.f);
		__m256 mh = _mm256_set1_ps(0.5f);
		for (int i = 0; i < size; i++)
		{
			a[i] = rand_32f(0, 100);
		}

		const __m256 mth = _mm256_set1_ps(th);
		for (int i = 0; i < size; i += 8)
		{
			const __m256 ma = _mm256_load_ps(a + i);

			__m256 temp;
			//cmp, mul, blendvを使って
			__m256 ma0 = _mm256_mul_ps(md, ma);
			__m256 ma1 = _mm256_mul_ps(mh, ma);

			temp = _mm256_cmp_ps(ma, mth, _CMP_GT_OQ);
			temp = _mm256_blendv_ps(ma1, ma0, temp);

			_mm256_store_ps(a + i, temp);
		}
		for (int i = 0; i < size; i++)
		{
			std::cout << a[i] << ", ";
			if (i != 0 && i%size == 0)
				std::cout << std::endl;
		}
		std::cout << std::endl;
		return 0;
	}

	//課題26
	//上記のコードのように，SIMD命令を使う場合におけるループアンローリングを8，16，32，64と行い，計算時間を比較せよ．
	if (false)
	{
		std::cout << "課題26" << std::endl;
		const int loop = 1000;
		const int size = 1024 * 3;
#ifdef __GNUC__
		__attribute__((aligned(32))) float a[size];
		__attribute__((aligned(32))) float b[size];
		__attribute__((aligned(32))) float c[size];
#elif _MSC_VER
		__declspec(align(32)) float a[size];
		__declspec(align(32)) float b[size];
		__declspec(align(32)) float c[size];
#endif

		//init
		for (int i = 0; i < size; i++)
		{
			a[i] = rand_32f(0, 100);
			b[i] = rand_32f(0, 100);
			c[i] = 0;
		}

		CalcTime t;
		// unrolling 8
		for (int j = 0; j < loop; j++)
		{
			t.start();
			// unrolling 8
			for (int i = 0; i < size; i += 8)
			{
				__m256 ma = _mm256_load_ps(a + i);
				__m256 mb = _mm256_load_ps(b + i);
				_mm256_store_ps(c + i, _mm256_add_ps(ma, mb));
			}
			t.end();
		}
		std::cout << "  8: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		// unrolling 16
		for (int j = 0; j < loop; j++)
		{
			t.start();
			// unrolling 16
			for (int i = 0; i < size; i += 16)
			{
				__m256 ma = _mm256_load_ps(a + i);
				__m256 mb = _mm256_load_ps(b + i);
				_mm256_store_ps(c + i, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 8);
				mb = _mm256_load_ps(b + i + 8);
				_mm256_store_ps(c + i + 8, _mm256_add_ps(ma, mb));
			}
			t.end();
		}
		std::cout << " 16: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		// unrolling 32
		for (int j = 0; j < loop; j++)
		{
			t.start();
			// unrolling 32
			for (int i = 0; i < size; i += 32)
			{
				__m256 ma = _mm256_load_ps(a + i);
				__m256 mb = _mm256_load_ps(b + i);
				_mm256_store_ps(c + i, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 8);
				mb = _mm256_load_ps(b + i + 8);
				_mm256_store_ps(c + i + 8, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 16);
				mb = _mm256_load_ps(b + i + 16);
				_mm256_store_ps(c + i + 16, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 32);
				mb = _mm256_load_ps(b + i + 32);
				_mm256_store_ps(c + i + 32, _mm256_add_ps(ma, mb));
			}
			t.end();
		}
		std::cout << " 32: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		// unrolling 64
		for (int j = 0; j < loop; j++)
		{
			t.start();
			// unrolling 64
			for (int i = 0; i < size; i += 64)
			{
				__m256 ma = _mm256_load_ps(a + i);
				__m256 mb = _mm256_load_ps(b + i);
				_mm256_store_ps(c + i, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 8);
				mb = _mm256_load_ps(b + i + 8);
				_mm256_store_ps(c + i + 8, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 16);
				mb = _mm256_load_ps(b + i + 16);
				_mm256_store_ps(c + i + 16, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 32);
				mb = _mm256_load_ps(b + i + 32);
				_mm256_store_ps(c + i + 32, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 40);
				mb = _mm256_load_ps(b + i + 40);
				_mm256_store_ps(c + i + 40, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 48);
				mb = _mm256_load_ps(b + i + 48);
				_mm256_store_ps(c + i + 48, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 56);
				mb = _mm256_load_ps(b + i + 56);
				_mm256_store_ps(c + i + 56, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 64);
				mb = _mm256_load_ps(b + i + 64);
				_mm256_store_ps(c + i + 64, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 72);
				mb = _mm256_load_ps(b + i + 72);
				_mm256_store_ps(c + i + 72, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 80);
				mb = _mm256_load_ps(b + i + 80);
				_mm256_store_ps(c + i + 80, _mm256_add_ps(ma, mb));

				ma = _mm256_load_ps(a + i + 88);
				mb = _mm256_load_ps(b + i + 88);
				_mm256_store_ps(c + i + 88, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 96);
				mb = _mm256_load_ps(b + i + 96);
				_mm256_store_ps(c + i + 96, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 104);
				mb = _mm256_load_ps(b + i + 104);
				_mm256_store_ps(c + i + 104, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 112);
				mb = _mm256_load_ps(b + i + 112);
				_mm256_store_ps(c + i + 112, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 120);
				mb = _mm256_load_ps(b + i + 120);
				_mm256_store_ps(c + i + 120, _mm256_add_ps(ma, mb));				
				
				ma = _mm256_load_ps(a + i + 128);
				mb = _mm256_load_ps(b + i + 128);
				_mm256_store_ps(c + i + 128, _mm256_add_ps(ma, mb));
			}
			t.end();
		}
		std::cout << "128: time (avg): " << t.getAvgTime() << " ms" << std::endl;

		return 0;
	}

	//課題27
	//上の関数を用いて，データ構造の相互変換を確認せよ． ４ｘ４のdouble型データの転置を手書きで考えてみよ．
	//この問題は，自力で答えを埋めると時間がかかり過ぎるためプログラムの答えはすでに埋めてある．
	//そのため，この動作を追って転置ができていることを手書きで確認するだけで良い．
	if (false)
	{
		std::cout << "課題27" << std::endl;
		const int size = 64;
#ifdef __GNUC__
		__attribute__((aligned(32))) float a[size];
		__attribute__((aligned(32))) float b[size];
#elif _MSC_VER
		__declspec(align(32)) float a[size];
		__declspec(align(32)) float b[size];
#endif
		for (int i = 0; i < size; i++)
		{
			a[i] = i;
			b[i] = 0;
		}
		__m256 ma[8], mb[8];
		for (int i = 0; i < 8; i++)
		{
			ma[i] = _mm256_load_ps((float*)(&a[i * 8]));
			mb[i] = _mm256_setzero_ps();
		}

		for (int i = 0; i < 8; i++)
		{
			print_m256(ma[i]);
		}

		//転置
		_mm256_transpose_8x8_ps(mb,ma);

		for (int i = 0; i < 8; i++)
		{
			print_m256(mb[i]);
		}
		return 0;
	}

	//課題28
	//__m256i（int）型を_m256（float）型に変換せよ．
	if (false)
	{
		std::cout << "課題28" << std::endl;
		__m256i m32i = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
		__m256 m32f = _mm256_setzero_ps();

		print_m256(m32f);
		//cvtを使って
		m32f = _mm256_cvtepi32_ps(m32i);
		print_m256(m32f);
	}


	//課題29
	//上記のコードを実行し，計算時間を計測せよ．
	//また，スカラ実装，スカラ実装＋並列化，SIMD実装のみを作成し，計算時間を比較せよ．
	//if (false)
	{
		std::cout << "課題29" << std::endl;
		const int loop = 10;
		const int size = 128;
		Mat_32F a(size, size);
		Mat_32F b(size, size);
		Mat_32F c(size, size);

		//init
		mat_rand(a, 0, 100);
		mat_rand(b, 0, 100);
		mat_zero(c);

		CalcTime t;
		for (int k = 0; k < loop; k++)
		{
			//スカラー実装
			t.start();
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; i++)
				{
					c.data[j*c.cols + i] = a.data[j*a.cols + i] * b.data[j*b.cols + i]; 
				}
			}
			t.end();
		}
		std::cout << "scalar    : time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//c.show();


		for (int k = 0; k < loop; k++)
		{
			//スカラー，並列化実装
			t.start();
			#pragma omp parallel for
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; i++)
				{
					c.data[j*c.cols + i] = a.data[j*a.cols + i] * b.data[j*b.cols + i]; 
				}
			}
			t.end();
		}
		std::cout << "scalar+omp: time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//c.show();

		for (int k = 0; k < loop; k++)
		{
			//SIMD実装
			t.start();
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; i += 8)
				{
					__m256 ma = _mm256_load_ps(a.data+j*size+i);
					__m256 mb = _mm256_load_ps(b.data+j*size+i);
					__m256 temp = _mm256_mul_ps(ma, mb);
					_mm256_store_ps(c.data + j*size+i, temp);
				}
			}
			t.end();
		}
		std::cout << "SIMD      : time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//c.show();

		for (int k = 0; k < loop; k++)
		{
			//SIMD，並列化実装
			t.start();
			#pragma omp parallel for
			for (int j = 0; j < size; ++j)
			{
				for (int i = 0; i < size; i += 8)
				{
					__m256 ma = _mm256_load_ps(a.data+j*size+i);
					__m256 mb = _mm256_load_ps(b.data+j*size+i);
					__m256 temp = _mm256_mul_ps(ma, mb);
					_mm256_store_ps(c.data + j*size+i, temp);
				}
			}
			t.end();
		}
		std::cout << "SIMD+omp  : time (avg): " << t.getAvgTime() << " ms" << std::endl;
		//c.show();

		return 0;
	}

	std::cout << "no select" << std::endl;
	return 0;
}
