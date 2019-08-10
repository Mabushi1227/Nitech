#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 17 16:57:51 2019

@author: akitakazuki

感性情報処理レポート３　名古屋市のデータを重回帰分析を用いて分析
"""

import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
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
    #d = d.astype(np.float)

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
    #plt.savefig("lecture6.png")
    plt.show()

###################################
    
if __name__ == "__main__":
    
    #単回帰分析
    fn = "nagoya_data"
    
    data = loadCSV(fn + ".csv",True,False)

    print("data\n",data)
    
    #x = data[:,:2]
    #y = data[:,2]
    
   ##　p は xの説明変数(x)数, データによって変更
    p = 2
    #x = data[:,:p]
    x = np.zeros([data.shape[0],2])
    x[:,0] = data[:,2] / data[:,0]
    x[:,1] = data[:,4] / (data[:,3] + data[:,4])
    
    #y = data[:,p:data.shape[1]-1]
    #y = np.sum(y, axis = 1)
    y = data[:,5]
    
    
    """
    ####一つだけ大きく外れた点を除外すると、寄与率が大きく上昇する
    #x = np.delete(x,8,0)
    #y = np.delete(y,8,0)
    """
    n = x.shape[0] 
    
    x_avr = np.mean(x, axis = 0)  
    y_avr = np.mean(y, axis = 0)
    
    x_z = (x[:,:2] - x_avr) / pow(np.var(x, axis = 0),0.5)  
    y_z = (y - y_avr) / pow(np.var(y), 0.5)
    
    print("x_z(標準化したx)\n",x_z)
    print("y_z(標準化したy)\n",y_z)
    
    x_avr = np.mean(x_z, axis=0)
    
    
    """
    #寄与率の導出
    x_zt = x_z.T  
    R = np.cov(x_zt)
    w,v = LA.eig(R)
    
    #固有値でソート
    sort_index = np.argsort(w)[::-1]
    sort_w = w[sort_index]
    sort_v = v[:,sort_index]
    
    print("w=\n",w,"\nv=\n",v)
    
    
    ##主成分得点zを説明変数として解析する
    #主成分得点zの導出
    z = np.zeros([x.shape[0],x.shape[1]])
    for i in range(0,x.shape[0]):
        for j in range(0,x.shape[1]):
            for k in range(0,x.shape[1]):
                z[i,j] += v[k,j] * x_z[i,k]
                
    print("z\n = ",z)
    """  
    
    Sxx = np.zeros(x.shape[1])
    Sxy = np.zeros(x.shape[1])
    
    #Szz = np.zeros(z.shape[1])
    #Szy = np.zeros(z.shape[1])
    
    #z_avr = np.mean(z, axis = 0) 
    
    for i in range(x.shape[1]):
        Sxx[i] = np.dot(x_z[:,i]-x_avr[i], x_z[:,i]-x_avr[i])
        Sxy[i] = np.dot(x_z[:,i]-x_avr[i], y[:] - y_avr)
    Syy = np.dot(y[:] - y_avr, y[:] - y_avr)
    
    B1 = Sxy/Sxx
    B0 = y_avr - B1[:] * x_avr[:]
    
    
    """
    #相関係数
    r = np.corrcoef(data, rowvar = False)
    for i in range(data.shape[1]):
        for j in range(data.shape[1]):
            if i <= j:
                print("r",i,j, " = ", r[i,j])
                
    """
    
    
    Sr = B1 * Sxy #残差平方和
    Se = Syy - Sr #回帰による平方和
    R2 =  Sr / Syy #寄与率
    R_2 =  1 - (( Se[:] / (n-2))/( Syy / (n-1))) #自由度調整済寄与率
    
    F0 = (Syy - Se[:]) / (n-1-n+2) / (Se[:]/(n-2)) ##単回帰の分散比
    
    
    plot_z = np.arange(0,2,0.05)
    
    print("\n")
    print("xによる単回帰分析\nB0 = ", B0,"\nB1 = ", B1,"\nSxx,Sxy = " ,Sxx,",",Sxy)
    #print("zによる単回帰分析\nB0 = ", B0,"\nB1 = ", B1,"\nSzz,Szy = " ,Szz,",",Szy)
    print("Sr = ",Sr,"\nSe = ",Se,"\nR2 = ",R2,"\nR_2 = ",R_2,"\nF0 = " , F0)
        
    """
    for i in range(x.shape[1]):
        print("\n")
        print("x",i+1,"による単回帰分析\nB0 = ", B0[i],"\nB1 = ", B1[i],"\nSxx,Sxy = " ,Szz[i],",",Szy[i])
        print("Sr = ",Sr[i],"\nSe = ",Se[i],"\nR2 = ",R2[i],"\nR_2 = ",R_2[i],"\nF0 = " , F0[i])
        plt.scatter(plot_z, B1[i]*plot_z+B0[i], label="y="+str(B1[i])+"x"+"+"+ str(B0[i]), s = 5, c = "blue")
        plt.scatter(x[:,0],y[:], label="data", c = "orange")
        plt.xlabel("x")
        plt.ylabel("y")
        #plt.legend()
        plt.show()
        
    """
    
    print("\n重回帰分析")
    Se_M1 = Se
    p = 2
    
    
    n = data.shape[0] 
    X = np.ones([x.shape[0],x.shape[1]+1])
    
    for i in range(x.shape[0]):
        for j in range (x.shape[1]):
            X[i,j+1] = x_z[i,j] - x_avr[j]
    
    print("X\n", X)
    
    X_t = X.T
    
    XtX = X_t @ X
    XtX_1 = np.linalg.inv(X_t @ X)  
    
    Beta = XtX_1 @ X_t @ y
    
    for i in range(1,x.shape[1]+1):
        Beta[0] -= Beta[i] * x_avr[i-1]
    
    print("Beta\n" , Beta)
    
    #サンプルとしてyの平均を通るx1-x2平面と平行な平面を作成
    y_m = np.average(y,axis=0)
    a = np.array([y_m,0,0])    
    print("a\n",a)
    
    # 格子状のデータを作成
    lx1, lx2 = np.meshgrid(np.arange(-3, 3, 0.03), np.arange(-3, 3, 0.03))
    #print("lx1\n",lx1)
    #print("lx2\n",lx2)
    
    
    #ly =  Beta[0] + Beta[1]*lx1 + Beta[2]*lx2 + Beta[3]*lx3
    ly =  Beta[0] + Beta[1]*lx1 + Beta[2]*lx2 
     
    #print("ly\n",ly)
        
    #dataのプロットと，平面を描画
    drawScatter3D(x_z[:,0],x_z[:,1],y[:],"x1","x2","y",lx1,lx2,ly)
    
    ##寄与率の計算
    y_predict = Beta[0] + Beta[1]*x_z[:,0] + Beta[2]*x_z[:,1] #変数2
    #y_predict = Beta[0] + Beta[1]*x[:,0] + Beta[2]*x[:,1] + Beta[3]*x[:,2] #変数３
    
    
    #残差
    e_i = y - y_predict
    #残差平方和
    Se = sum(e_i ** 2)
    Sr = np.dot(x[:,0]-x_avr[0], e_i)*Beta[0] + np.dot(x[:,1]-x_avr[1], e_i)*Beta[1]
    
    ##Sr = sum(Sr)
    Syy = sum( (y - y_m) **2 )
    
    R2 = 1 - Se / Syy
     
    print("Se\n",Se,"\nSr(回帰による平方和)\n",Sr,
                      "\nSyy\n",Syy,"\nR2（寄与率）\n",R2)
    
    R_2 = 1- (Se/(n-p-1)) / (Syy/(n-1))
    
    print("R_2(自由度調整済寄与率)", R_2)
    
    F0 = (Se_M1[0] - Se) / (n-2 - (n-p-1)) / (Se / (n-p-1))
    
    print("重回帰の分散比",F0)
    
    