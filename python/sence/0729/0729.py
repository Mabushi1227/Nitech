#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 29 15:38:18 2019

@author: akitakazuki

感性情報処理　判別分析

"""

import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


####################################
# 散布図と回帰平面を3Dで描画する関数
# x,y,z: プロットするデータ
# xlabel : x軸のラベル
# ylabel : y軸のラベル
# zlabel : z軸のラベル
# lx,ly,lz: 平面のデータ    
####################################
def drawScatter2(x1,x2,y1,y2,xlabel,ylabel,lx,ly):     
    plt.clf();

    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
    
    plt.scatter(x1,x2, color = (1,0,0))
    plt.scatter(y1,y2, color = (0,0,1))
    
    plt.plot(lx, ly, color = (0,1,0))
    #plt.savefig("lecture6.png")
    plt.show()
    
#####################################

"""
data = np.array([["健常者",50,15.5,-0.516,"患者"],
                ["健常者",69,18.4,2.809,"健常者"],
                ["健常者",93,26.4,5.561,"健常者"],
                ["健常者",76,22.9,2.888,"健常者"],
                ["健常者",88,18.6,7.037,"健常者"],
                ["患者",43,16.9,-2.566,"患者"],
                ["患者",56,21.6,-1.197,"患者"],
                ["患者",38,12.2,-2.126,"患者"],
                ["患者",21,16.0,-7.237,"患者"],
                ["患者",25,10.5,-4.496,"患者"]])
"""

"""
data = np.array([[50,15.5,-0.516],
                [69,18.4,2.809],
                [93,26.4,5.561],
                [76,22.9,2.888,],
                [88,18.6,7.037],
                [43,16.9,-2.566],
                [56,21.6,-1.197],
                [38,12.2,-2.126],
                [21,16.0,-7.237],
                [25,10.5,-4.496]])
    """

data = np.array([[4,0],
                [6,2],
                [5,1],
                [4,1],
                [4,-1],
                [7,1],
                [8,2],
                [7,2]])
    
data1 = data[0:4,:2]
data2 = data[4:,:2]

n1 = data1.shape[0]
n2 = data2.shape[0] 

m1 = np.mean(data1, axis = 0)
m2 = np.mean(data2, axis = 0)

v1 = np.cov(data1,rowvar=False) * (n1-1)
v2 = np.cov(data2,rowvar=False) * (n2-1)

v = (v1+v2)/(n1+n2-2)

print("v\n",v)

v_1 = np.linalg.inv(v)

k = m1-m2
a = np.dot(k,v_1)
ma = (m1+m2)/2
b = np.dot(a,-ma)
lx = np.linspace(0,10,10)
ly = (-a[0] * lx - b) / a[1]
print("a = ",a)
drawScatter2(data1[:,0],data1[:,1],data2[:,0],data2[:,1],"x","y",lx,ly)

DE = np.dot(a,ma)

"""
data = np.array([[50,15.5],
                 [69,18.4],
                 [93,26.4],
                 [76,22.9],
                 [88,18.6],
                 [43,16.9],
                 [56,21.6],
                 [38,12.2],
                 [21,16.0],
                 [25,10.5]])
data1 = data[0:5,:]
data2 = data[5:,:]    
print("data1:\n",data1)
print("data2:\n",data2)
print("\n")

data1_mean = data1.mean(axis=0)
data2_mean = data2.mean(axis=0)
print("data1の平均:",data1_mean)
print("data2の平均:",data2_mean)
print("\n")

#data1について
S1_11 = 0
S1_22 = 0
S1_12 = 0
for i in range(0,data1.shape[0]):
    S1_11 += (data1[i][0]-data1_mean[0])**2
    S1_22 += (data1[i][1]-data1_mean[1])**2
    S1_12 += (data1[i][0]-data1_mean[0])*(data1[i][1]-data1_mean[1])
print("S1_11:",S1_11)
print("S1_22:",S1_22)
print("S1_12:",S1_12)
print("\n")

#data2について
S2_11 = 0
S2_22 = 0
S2_12 = 0
for i in range(0,data2.shape[0]):
    S2_11 += (data2[i][0]-data2_mean[0])**2
    S2_22 += (data2[i][1]-data2_mean[1])**2
    S2_12 += (data2[i][0]-data2_mean[0])*(data2[i][1]-data2_mean[1])
print("S2_11:",S2_11)
print("S2_22:",S2_22)
print("S2_12:",S2_12)
print("\n")

#dataの平均の平均
μ1 = (data1_mean[0]+data2_mean[0])/2
μ2 = (data1_mean[1]+data2_mean[1])/2
print("μ1:",μ1)
print("μ2:",μ2)
print("\n")

ρ11 = (S1_11+S2_11)/((data1.shape[0]-1)+(data2.shape[0]-1))
ρ22 = (S1_22+S2_22)/((data1.shape[0]-1)+(data2.shape[0]-1))
ρ12 = (S1_12+S2_12)/((data1.shape[0]-1)+(data2.shape[0]-1))
print("ρ11:",ρ11)
print("ρ22:",ρ22)
print("ρ12:",ρ12)
print("\n")

Σ = np.array([[ρ11,ρ12],
              [ρ12,ρ22]])
print("Σ",Σ)
print("\n")
Σ1 = np.linalg.inv(Σ)
print("Σinv",Σ1)
print("\n")

z = np.dot((data1_mean-data2_mean),Σ1)
print("z",z)

A = np.dot((data1_mean-data2_mean),Σ1)
A = np.dot(A,[[-55.9],[-17.90]])
print("A(定数部分)",A)

D = np.dot((data1_mean-data2_mean),Σ1)
D = np.dot(D,(data1_mean-data2_mean))
print("D",D)

D1 = ((data1_mean[0]-data2_mean[0])**2)/ρ11
D2 = ((data1_mean[1]-data2_mean[1])**2)/ρ22
print("D1:",D1)
print("D2:",D2)

F0_1 = (data1.shape[0]+data2.shape[0]-1-1-1)*data1.shape[0]*data2.shape[0]*(D-D1)
F0_2 = 1*((data1.shape[0]+data2.shape[0]-2)*(data1.shape[0]+data2.shape[0])+data1.shape[0]*data2.shape[0]*D1)
F0 = F0_1/F0_2
print("F0:",F0)

"""
data = np.array([[4,0],
                [6,2],
                [5,1],
                [4,1],
                [4,-1],
                [7,1],
                [8,2],
                [7,2]])
    
    
data1 = data[0:4,:]
data2 = data[4:,:]    
print("data1:\n",data1)
print("data2:\n",data2)
print("\n")

data1_mean = data1.mean(axis=0)
data2_mean = data2.mean(axis=0)
print("data1の平均:",data1_mean)
print("data2の平均:",data2_mean)
print("\n")

#data1について
S1_11 = 0
S1_22 = 0
S1_12 = 0
for i in range(0,data1.shape[0]):
    S1_11 += (data1[i][0]-data1_mean[0])**2
    S1_22 += (data1[i][1]-data1_mean[1])**2
    S1_12 += (data1[i][0]-data1_mean[0])*(data1[i][1]-data1_mean[1])
print("S1_11:",S1_11)
print("S1_22:",S1_22)
print("S1_12:",S1_12)
print("\n")

#data2について
S2_11 = 0
S2_22 = 0
S2_12 = 0
for i in range(0,data2.shape[0]):
    S2_11 += (data2[i][0]-data2_mean[0])**2
    S2_22 += (data2[i][1]-data2_mean[1])**2
    S2_12 += (data2[i][0]-data2_mean[0])*(data2[i][1]-data2_mean[1])
print("S2_11:",S2_11)
print("S2_22:",S2_22)
print("S2_12:",S2_12)
print("\n")

#dataの平均の平均
μ1 = (data1_mean[0]+data2_mean[0])/2
μ2 = (data1_mean[1]+data2_mean[1])/2
print("μ1:",μ1)
print("μ2:",μ2)
print("\n")

ρ11 = (S1_11+S2_11)/((data1.shape[0]-1)+(data2.shape[0]-1))
ρ22 = (S1_22+S2_22)/((data1.shape[0]-1)+(data2.shape[0]-1))
ρ12 = (S1_12+S2_12)/((data1.shape[0]-1)+(data2.shape[0]-1))
print("ρ11:",ρ11)
print("ρ22:",ρ22)
print("ρ12:",ρ12)
print("\n")

Σ = np.array([[ρ11,ρ12],
              [ρ12,ρ22]])
print("Σ",Σ)
print("\n")
Σ1 = np.linalg.inv(Σ)
print("Σinv",Σ1)
print("\n")

z = np.dot((data1_mean-data2_mean),Σ1)
print("z",z)

A = np.dot((data1_mean-data2_mean),Σ1)
A = np.dot(A,[[-55.9],[-17.90]])
print("A(定数部分)",A)

D = np.dot((data1_mean-data2_mean),Σ1)
D = np.dot(D,(data1_mean-data2_mean))
print("D",D)

D1 = ((data1_mean[0]-data2_mean[0])**2)/ρ11
D2 = ((data1_mean[1]-data2_mean[1])**2)/ρ22
print("D1:",D1)
print("D2:",D2)

F0_1 = (data1.shape[0]+data2.shape[0]-1-1-1)*data1.shape[0]*data2.shape[0]*(D-D1)
F0_2 = 1*((data1.shape[0]+data2.shape[0]-2)*(data1.shape[0]+data2.shape[0])+data1.shape[0]*data2.shape[0]*D1)
F0 = F0_1/F0_2
print("F0:",F0)