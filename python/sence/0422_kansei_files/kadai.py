#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 17:31:25 2019

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
        
    #envording='shift_jis'を付けないと読み込み時にエラーがでた    
    d = np.loadtxt(filename,delimiter=',',skiprows=_skiprows,encoding='shift_jis')

    if f_skip_first_col==True:
        d = d[:,1:]

    return d

def loadCSV_txt(filename,f_skip_first_row = False,f_skip_first_col=False):
    _skiprows = 0

    if f_skip_first_row==True:
        _skiprows = 1
        
    #envording='shift_jis'を付けないと読み込み時にエラーがでた    
    d = np.loadtxt(filename,delimiter=',',skiprows=_skiprows,encoding='shift_jis',dtype = "str")

    if f_skip_first_col==True:
        d = d[:,1:]

    return d

def cal_R_ab(data):
    #a,bの偏差積和 S_ab
    a = data[:,0]
    print("元データa\n",a)
    b = data[:,1]
    print("元データb\n",b)
    
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
    
#課題2(data01の相関係数)
print("kadai2\n")
if __name__ == "__main__":
    
    data = loadCSV("data01_p031.csv",True,True)
    
    R = cal_R_ab(data)
    
    print("演習１.data01の相関係数 \n ",R)

#課題3(data02の固有値と固有ベクトルの算出)
print("\nkadai3")

if __name__ == "__main__":
    
    data = loadCSV("data02_p042.csv",False,False)
    
    w,v = LA.eig(data)
    
    print("固有値\n",w)
    print("固有ベクトル\n",v)

#課題4(data03の主成分分析)
print("\nkadai4")
if __name__ == "__main__":
    
    #データのカテゴリー(教科)
    categoly = ["Japanese", "English", "Math", "Science"]
    
    #データの取得
    data = loadCSV("data03_p132.csv",True,True)
    
    data_len = len(data)
    #扱いやすいように行列を転置
    SD = data.T
    cat_len = len(SD)
    
    cat_mean = np.zeros(cat_len)
    cat_std = np.zeros(cat_len)
    
    #データ偏差
    data_dev = np.zeros((cat_len,data_len))
    
    print("元のデータ\n",data)
    
    #SDを標準化させる
    for i in range(0,cat_len):
        
        cat_mean[i] = SD[i].mean() 
        
        for j in range(0,data_len):
            data_dev[i,j] = SD[i,j] - cat_mean[i] 
            cat_std[i] += pow(data_dev[i,j], 2.0)
        
        cat_std[i] = pow(cat_std[i] / (data_len-1) , 0.5)
        
        for j in range(0,data_len):
            SD[i,j] = data_dev[i,j] / cat_std[i]
    
    R = np.cov(SD)
    w,v = LA.eig(R)
    
    print("標準化したデータ[categoly,number]\n",SD)
    

    print("固有値\n",w)
    print("固有ベクトル\n",v)
    
    #累積寄与率
    c_sum = 0.0;
    
    #固有値でソート
    sort_index = np.argsort(w)[::-1]
    sort_w = w[sort_index]
    sort_v = v[:,sort_index]
    
    
    for i in range(0,cat_len):
        print("第"+ str(i+1) + "主成分\n %.6f" % (sort_w[i]/cat_len))
        c_sum += sort_w[i]/cat_len
        print("累積寄与率: %.6f" % (c_sum))
    
    #主成分得点を散布図プロット(x = 第一主成分,y＝第二主成分)
    x = np.zeros(data_len)
    y = np.zeros(data_len)
    
    for i in range(0,data_len):
        for j in range(0,cat_len):
            x[i] += SD[j,i] * v[j,0]
            y[i] += SD[j,i] * v[j,1]
    
    for i in range(0,data_len):
        plt.scatter(x[i],y[i], label = i)
    
    plt.legend()
    plt.xlabel("first")
    plt.ylabel("second")
    plt.title("data03_PCA")
    plt.show()
    
    #因子負荷量
    r = np.zeros((cat_len,cat_len))
    
    for i in range(0,cat_len):
        for j in range(0,cat_len):
            r[i,j] = pow(w[i],0.5) * v[j,i]

    print("因子負荷量\n",r)
    for i in range(0,cat_len):
        plt.scatter(r[0,i], r[1,i], s= 50, label = categoly[i])
    
    plt.xlim(-1.0,1.0)
    plt.ylim(-1.0,1.0)
    plt.legend()
    plt.xlabel("first")
    plt.ylabel("second")
    plt.title("data03_r")
    plt.show()

#課題5(data04の主成分分析)
print("\nkadai5")

if __name__ == "__main__":

    #数値の取得
    data = loadCSV("data04_nagoya1_new.csv",True,True)
    
    #データのインデックス(区名)を取得
    #index = loadCSV_txt("data04_nagoya1_index.csv",True,True)
    #文字化けしたため手打ち
    index = ["Chikusa", "Higashi", "Kita", "Nishi", "Nakamura", "Naka", "Showa", "Mizuho", "Atsuta", "Nakagawa", "Minato", "Minami", "Moriyama", "Midori","Meito", "Tenpaku" ]
    
    #データのカテゴリー
    categoly = ["All", "~15", "16~64", "65~", "Foreiner", "in Daytime" ]
    
    data_len = len(data)
    #扱いやすいように行列を転置
    SD = data.T
    cat_len = len(SD)
    
    cat_mean = np.zeros(cat_len)
    cat_std = np.zeros(cat_len)
    
    #データ偏差
    data_dev = np.zeros((cat_len,data_len))
    
    #SDを標準化させる
    for i in range(0,cat_len):
        
        #category別の平均
        cat_mean[i] = SD[i].mean() 
        
        #cat_stdに偏差の２乗を足していく
        for j in range(0,data_len):
            data_dev[i,j] = SD[i,j] - cat_mean[i] 
            cat_std[i] += pow(data_dev[i,j], 2.0)
        
        #((偏差^2の和) / (n-1))^0.5で標準偏差
        cat_std[i] = pow(cat_std[i] / (data_len-1) , 0.5)
        
        #標準化
        for j in range(0,data_len):
            SD[i,j] = data_dev[i,j] / cat_std[i]
    
    
    R = np.cov(SD)
    w,v = LA.eig(R)
    
    print("(標準化したデータ[categoly,number])\n",SD)
    

    print("固有値\n",w)
    print("固有ベクトル\n",v)
    
    #累積寄与率
    c_sum = 0;

    #固有値でソート
    sort_index = np.argsort(w)[::-1]
    sort_w = w[sort_index]
    sort_v = v[:,sort_index]
    
    
    for i in range(0,cat_len):
        print("第"+ str(i+1) + "主成分\n %.6f" % (sort_w[i]/cat_len))
        c_sum += sort_w[i]/cat_len
        print("累積寄与率: %.6f" % (c_sum))
    
    x = np.zeros(data_len)
    y = np.zeros(data_len)
    
    #主成分得点
    for i in range(0,data_len):
        for j in range(0,cat_len):
            x[i] += SD[j,i] * v[j,0]
            y[i] += SD[j,i] * v[j,1]
            
    for i in range(0,data_len):
        plt.scatter(x[i],y[i], s = (i+1)*20, label = index[i] )
    
    plt.grid()
    plt.xlim(-5,8)
    plt.legend()
    plt.xlabel("first")
    plt.ylabel("second")
    plt.title("data04_PCA")
    plt.show()
    
    #因子負荷量
    r = np.zeros((cat_len,cat_len))
    
    for i in range(0,cat_len):
        for j in range(0,cat_len):
            r[i,j] = pow(w[i],0.5) * v[j,i]
            
    #plt.scatter(r[0,:],r[1,:])
    for i in range(0,cat_len):
        plt.scatter(r[0,i],r[1,i], label = categoly[i])
    
    plt.grid()
    plt.xlim(-1.2,1.2)
    plt.ylim(-1.0,1.0)
    plt.legend()
    plt.xlabel("first")
    plt.ylabel("second")
    plt.title("data04_r")
    plt.show()

    
