# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 00:35:43 2018

@author: taguchi
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
    
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("sample loadCSV")
    
    data = loadCSV("data01_p031.csv",True,True)
    
    print(data)
    

