#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 17:31:25 2019

@author: akitakazuki
"""

import numpy as np

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

def cal_R_ab(data):
    #a,bの偏差積和 S_ab
    a = data[:,0]
    print(a)
    b = data[:,1]
    a = a - a.mean()   #aの偏差
    b = b - b.mean() #bの偏差
    length = len(a)   #a,bの個数

    S_ab = 0

    for i in range(0,length):
        S_ab += a[i] * b[i]        
     
    #print("\n",S_ab)

    #a,bの共分散
    S_aa = np.dot(a,a)
    S_bb = np.dot(b,b)

    R_ab = S_ab / ((S_aa * S_bb)** 0.5)
    return R_ab



####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("sample loadCSV")
    
    data = loadCSV("data01_p031.csv",True,True)
    
    R = cal_R_ab(data)
    
    print("演習１.data01の相関係数 \n ",R)
    
    
    