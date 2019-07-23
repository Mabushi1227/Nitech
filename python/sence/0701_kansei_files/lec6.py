# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 17:47:04 2019

@author: taguchi akitakazuki

重回帰分析を行うプログラム
"""
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats
from mpl_toolkits.mplot3d import Axes3D

####################################
# CSVを読み込む関数
# filename : ファイル名
# f_skip_first_row : １行目を読み飛ばすならTrue
# f_skip_first_col : １列目を読み飛ばすならTrue
####################################    
def loadCSV(filename,f_skip_first_row = False,f_skip_first_col=False):
    _skiprows = 0

    if f_skip_first_row==True:
        _skiprows = 1
        
    d = np.loadtxt(filename,delimiter=',',skiprows=_skiprows)
    

    if f_skip_first_col==True:
        d = d[:,1:]

    return d

####################################
# 散布図を描画する関数
# x,y: データ
# xlabel : x軸のラベル
# ylabel : y軸のラベル
####################################
def drawScatter1(x,y,xlabel,ylabel):     
    plt.clf();

    # グラフの軸ラベル等の設定
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)

    # 散布図を描画
    for (i,j,k) in zip(x,y,range(1,x.shape[0]+1)):
        plt.plot(i,j,'ro')
        plt.annotate(k, xy=(i, j))
    plt.show()

####################################
# 散布図と直線を描画する関数
# x,y: プロットするデータ
# xlabel : x軸のラベル
# ylabel : y軸のラベル
# lx,ly: 直線のデータ    
####################################
def drawScatter2(x,y,xlabel,ylabel,lx,ly):     
    plt.clf();

    # グラフの軸ラベル等の設定
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)

    # 散布図を描画
    for (i,j,k) in zip(x,y,range(1,x.shape[0]+1)):
        plt.plot(i,j,'ro')
        plt.annotate(k, xy=(i, j))
    plt.plot(lx, ly,color='red')
    plt.show()


####################################
# 散布図と回帰平面を3Dで描画する関数
# x,y,z: プロットするデータ
# xlabel : x軸のラベル
# ylabel : y軸のラベル
# zlabel : z軸のラベル
# lx,ly,lz: 平面のデータ    
####################################
def drawScatter3D(x,y,z,xlabel,ylabel,zlabel,lx,ly,lz):     
    plt.clf();
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(x, y, z,color = (1,0,0))
    ax.plot_surface(lx, ly, lz, alpha = 0.5, color = (0,1,0),shade=False)
    ax.set_xlabel(xlabel)
    ax.set_ylabel(ylabel)
    ax.set_zlabel(zlabel)
    plt.savefig("lecture6.png")
    plt.show()
    
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("lecture 6")
    
    #fn = "data6-1_p061(UTF8)"
    fn = "data6-2_p086(UTF8)"
    
    data = loadCSV(fn + ".csv",True,True)

    print("data\n",data)
    
    x = data[:,:2]
    y = data[:,2]
    
    print("x\n",x)
    print("y\n",y)
    
    n = data.shape[0] 
    p = 2
    X = np.ones([x.shape[0],x.shape[1]+1])
    
    x_mean = np.mean(x,axis = 0)
    
    for i in range(x.shape[0]):
        for j in range (x.shape[1]):
            X[i,j+1] = x[i,j] - x_mean[j]
    
    print("X\n", X)
    
    X_t = X.T
    
    XtX = X_t @ X
    XtX_1 = np.linalg.inv(X_t @ X)  
    
    Beta = XtX_1 @ X_t @ y
    
    Beta[0] = Beta[0] - Beta[1] * x_mean[0] - Beta[2] * x_mean[1]
    
    print("Beta\n" , Beta)
    
    #サンプルとしてyの平均を通るx1-x2平面と平行な平面を作成
    y_m = np.average(y,axis=0)
    B = np.array([y_m,0,0])    
    print("B\n",B)

    # 格子状のデータを作成
    #lx1, lx2 = np.meshgrid(np.arange(20, 90, 10), np.arange(0, 40, 10))
    lx1, lx2 = np.meshgrid(np.arange(0, 20, 2), np.arange(0, 10, 2))
    print("lx1\n",lx1)
    print("lx2\n",lx2)
    
    ly =  Beta[0] + Beta[1]*lx1 + Beta[2]*lx2
    
    #ly = B[0] + B[1]*lx1 + B[2]*lx2 
    #print("ly\n",ly)
        
    #dataのプロットと，平面を描画
    #drawScatter3D(x[:,0],x[:,1],y[:],"x1","x2","y",lx1,lx2,ly)
    
    ##寄与率の計算
    y_predict = Beta[0] + Beta[1]*x[:,0] + Beta[2]*x[:,1]
    
    #残差
    e_i = y - y_predict
    #残差平方和
    Se = sum(e_i ** 2)
    Sr = np.dot(x[:,0]-x_mean[0], e_i)*Beta[0] + np.dot(x[:,1]-x_mean[1], e_i)*Beta[1]
    
    ##Sr = sum(Sr)
    Syy = sum( (y - y_m) **2 )
    
    R2 = 1 - Se / Syy
    Se_2 = Syy - Sr 
     
    print("Se\n",Se,"\nSr(回帰による平方和)\n",Sr,
                      "\nSyy\n",Syy,"\nR2（寄与率）\n",R2)