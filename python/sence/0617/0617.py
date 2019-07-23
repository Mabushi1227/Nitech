#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 17 16:57:51 2019

@author: akitakazuki

単回帰分析を行うプログラム

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
    
    data = loadCSV("data4-1_p043.csv", True, True)
    
    avr = np.mean(data, axis = 0)  
    
    Sxx = np.dot(data[:,0]-avr[0],data[:,0]-avr[0])
    Sxy = np.dot(data[:,0]-avr[0],data[:,1]-avr[1])
    
    B1 = Sxy/Sxx
    B0 = avr[1] - B1 * avr[0]
    
    x = np.arange(2,6,0.01)
    
    plt.scatter(x, B1*x+B0, label="y="+str(B1)+"x"+"+"+ str(B0), s = 5, c = "blue")
    plt.scatter(data[:,0],data[:,1], label="data", c = "orange")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend()
    plt.show()
    
    
    
    
    