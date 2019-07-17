#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 17 16:57:51 2019

@author: akitakazuki
"""

import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt

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
    fn = "../0701_kansei_files/data6-2_p086(UTF8)"
    
    data = loadCSV(fn + ".csv",True,True)

    print("data\n",data)
    
    x = data[:,:2]
    x1 = data[:,0]
    x2 = data[:,1]
    y = data[:,2]
    
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
    
    F0 = (Syy - Se[:]) / (n-1-n+2) / (Se[:]/(n-2))
    
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
    
    
    
    
    