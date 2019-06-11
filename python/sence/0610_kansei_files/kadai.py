#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 10 17:27:53 2019

@author: akitakazuki
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
        
    d = np.loadtxt(filename, dtype = 'str', delimiter=',', skiprows=_skiprows)
    

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
print("課題")

d = loadCSV("data3-3_utf8.txt",False,False)

print(d)

f = open('data3-3_utf8.txt')
lines = f.readlines()
f.close()

labname = ["伊藤孝行研究室",
         "犬塚・武藤・森山研究室",
         "新谷・大園研究室",
         "加藤研究室",
         "世木研究室",
         "竹内・烏山研究室",
         "大塚研究室",
         "白松研究室",
         "中村研究室",
         "船瀬研究室",
         "松井研究室",
         "小田研究室",
         "佐藤・坂上研究室",
         "徳田・南角・橋本研究室",
         "本谷研究室",
         "李・酒向研究室",
         "黒柳研究室",
         "田口研究室",
         "平野・後藤研究室",
         "舟橋研究室",
         "山本研究室"]
for j in range(len(lines)):
    st = "" + str(j) + ":"
    for i in range(labname.shape):
        if labname[i] in lines[j]:
            st = st + "1"
        else:
            st = st + "0" 
    print(st + lines[j])

