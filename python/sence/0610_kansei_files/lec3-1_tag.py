# -*- coding: utf-8 -*-
"""
Created on Mon May 20 17:10:50 2019

@author: taguchi
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram, linkage, fcluster, set_link_color_palette

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
def drawScatter(x,y,xlabel,ylabel):     
    plt.clf();

    # グラフの軸ラベル等の設定
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)

    # 散布図を描画
    for (i,j,k) in zip(x,y,range(1,x.shape[0]+1)):
        plt.plot(i,j,'o')
        plt.annotate(k, xy=(i, j))
    #plt.scatter(x, y)
    plt.show()


####################################
# ユークリッド距離の行列を計算する関数
# data: データ行列
####################################
def calcEuclideanDistanceMatrix(data):
    n_sample = data.shape[0]
    dist_mat = np.zeros((n_sample,n_sample))
    
    for i in range(n_sample):
        for j in range(n_sample):
            d = np.sum(((data[i,:] - data[j,:])**2))
            d = d**0.5
            dist_mat[i,j] = d
    
    return dist_mat

####################################
# ユークリッド距離の行列を計算する関数
# data: データ行列
####################################
def minDistance(mat):
    n_sample = mat.shape[0]
    min_val = -1
    min_index = [0,0]
    for i in range(n_sample):
        for j in range(i+1,n_sample):
            if min_val < 0 or min_val > mat[i,j]:
                min_val = mat[i,j]
                min_index = [i,j]
    return min_val, min_index
    
####################################
# ユークリッド距離の行列を計算する関数
# data: データ行列
####################################
def calcSingleLinkageMethod(data):

    n_sample = data.shape[0]
    dist_mat = calcEuclideanDistanceMatrix(data)
    index_name = np.array(range(n_sample))
    
    result = []
    
    print(dist_mat)
    
    for i in range(n_sample-1):
        min_val, min_index = minDistance(dist_mat)
        
        print(min_val, index_name[min_index])
        
        #target_data = np.zeros(2,dist_mat.shape[1])
        #target_data[0,:]  = dist_mat[min_index[0],:]
        #target_data[1,:]  = dist_mat[min_index[1],:]
        
        target_data  = dist_mat[min_index,:]
        target_data = np.min(target_data,axis=0)
        target_data = np.insert(target_data, target_data.shape[0], 0)
        
        new_dist_mat = np.insert(dist_mat, dist_mat.shape[0], target_data[:-1], axis=0)
        new_dist_mat = np.insert(new_dist_mat, new_dist_mat.shape[1], target_data.T, axis=1)
        
        

        new_dist_mat = np.delete(new_dist_mat, min_index, 0)
        new_dist_mat = np.delete(new_dist_mat, min_index, 1)
        
        index_name = np.delete(index_name, min_index)
        index_name = np.insert(index_name,  index_name.shape[0], i + n_sample)

        #print(new_dist_mat)
        
        dist_mat = new_dist_mat

####################################
# ウォード法の距離を計算する関数
# data: データ
####################################
def calcWardsMethodDistance(data):
    m = np.average(data,axis=1)
    s = (data - m)**2

    print(s)


    r = data
    return r
    
    
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("lecture 3-1")

    #data = loadCSV("data3-1_p176.csv",True,True)
    data = loadCSV("data3-2_p132.csv",True,True)
    
    print("data")
    print(data)
    
    #calcEuclideanDistance(data)
    
    calcSingleLinkageMethod(data)
    
    #l = linkage(data, method='ward')
    l = linkage(data, method='single')
    print(l)
    dn = dendrogram(l)
    plt.show()




    