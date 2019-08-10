#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 22 16:32:07 2019

@author: akitakazuki
"""

import numpy as np
import numpy.linalg as LA
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

if __name__ == "__main__":
    
    #単回帰分析
    #fn = "data6-1_p061(UTF8)"
    #fn = "../0701_kansei_files/data6-2_p086(UTF8)"
    fn = "data1" 
    
    data = loadCSV(fn + ".csv",True,True)

    print("data\n",data)
    
    x = data[:,:1]
    x1 = data[:,0]
    #x2 = data[:,1]
    y = data[:,1]
    
    print("x\n",x)
    print("y\n",y)
    
    n = data.shape[0] 
    
    x_avr = np.mean(x, axis = 0)  
    y_avr = np.mean(y, axis = 0)
    
    Sxx = np.zeros(x.shape[1])
    Sxy = np.zeros(x.shape[1])
    

    
    for i in range(x.shape[1]):
        Sxx[i] = np.dot(x[:,i]-x_avr[i], x[:,i]-x_avr[i])
        Sxy[i] = np.dot(x[:,i]-x_avr[i], y[:] - y_avr)
    Syy = np.dot(y[:] - y_avr, y[:] - y_avr)
    
    B1 = Sxy/Sxx
    B0 = y_avr - B1[:] * x_avr[:]
    
    #相関係数
    r = np.corrcoef(data, rowvar = False)
    for i in range(data.shape[1]):
        for j in range(data.shape[1]):
            if i <= j:
                print("r",i,j, " = ", r[i,j])
    
    
    Se = np.zeros(x.shape[1]) # 残差平方和
    Sr = np.zeros(x.shape[1]) # 回帰による平方和
    
    Sr = B1 * Sxy #残差平方和
    Se = Syy - Sr #回帰による平方和
    R2 =  Sr / Syy #寄与率
    R_2 =  1 - (( Se[:] / (n-2))/( Syy / (n-1))) #自由度調整済寄与率
    
    F0 = (Syy - Se[:]) / (n-1-n+2) / (Se[:]/(n-2)) ##単回帰の分散比
    
    
    plot_x = np.arange(2,14,0.1)
    for i in range(x.shape[1]):
        print("\n")
        print("x",i,"による単回帰分析\nB0 = ", B0[i],"\nB1 = ", B1[i],"\nSxx,Sxy = " ,Sxx[i],",",Sxy[i])
        print("Sr = ",Sr[i],"\nSe = ",Se[i],"\nR2 = ",R2[i],"\nR_2 = ",R_2[i],"\nF0 = " , F0[i])
        plt.scatter(plot_x, B1[i]*plot_x+B0[i], label="y="+str(B1[i])+"x"+"+"+ str(B0[i]), s = 5, c = "blue")
        plt.scatter(x[:,0],y[:], label="data", c = "orange")
        plt.xlabel("x")
        plt.ylabel("y")
        #plt.legend()
        #plt.show()
        
        
        
        
        
    print("probrem 2")
    
    #fn = "data6-1_p061(UTF8)"
    #fn = "data6-2_p086(UTF8)"
    
    #data = loadCSV(fn + ".csv",True,True)

    print("data\n",data)
    
    #x = data[:,:2]
    #y = data[:,2]
    y = np.array([22.,21,19,24])
    #print("x\n",x)
    print("y\n",y)
    
    n = y.shape[0] 
    
    #X = np.ones([x.shape[0],x.shape[1]+1])
    
    x_mean = np.array([11.25,3.75])
    
    #for i in range(x.shape[0]):
    #    for j in range (x.shape[1]):
    #        X[i,j+1] = x[i,j] - x_mean[j]
    
    X = np.array(([1,0.75,0.25],[1,-0.25,-0.75],[1,-3.25,-0.75],[1,2.75,1.25]))
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
    """
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
    """
    
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
    
