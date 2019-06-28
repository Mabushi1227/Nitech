# -*- coding: utf-8 -*-
"""
Created on Mon May 20 17:10:50 2019

@author: taguchi
"""

import numpy as np
from scipy.cluster.hierarchy import dendrogram, linkage

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
# indexで指定した行の平方和の計算
####################################        
def SS(data,index):
    d = data[index,:]
    m = np.average(d,axis=0)
    x = np.sum((d - m)**2)
    return x
    
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("lecture 3-1")

    d = loadCSV("data3-1_p176.csv",True,True)
    #d = loadCSV("data3-2_p132.csv",True,True)

    print("data")
    print(d)
    
    '''
    s = SS(d,[0,3,4])
    print(s)

    #l = linkage(d, method='ward', metric='euclidean')
    l = linkage(d, method='single', metric='euclidean')

    print("result")
    print(l)

    dn = dendrogram(l)
    '''

    #練習２
    S = np.zeros((5,5))
    dim = 5
    for i in range(dim):
        for j in range(i):    
            S[i,j] = SS(d, [i,j])
    print(S)
    
    S_min = 0.;
    
    np.amin(S, out =S_min)




    