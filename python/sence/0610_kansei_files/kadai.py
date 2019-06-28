#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 10 17:27:53 2019

@author: akitakazuki
"""

import numpy as np
from scipy.cluster.hierarchy import dendrogram, linkage, set_link_color_palette
import numpy.linalg as LA
import matplotlib.pyplot as plt

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

f = open('data3-3_utf8.txt')
lines = f.readlines()
f.close()

labname = np.array(["伊藤孝行研究室",
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
         "山本研究室"])

#元のデータリスト(0 or 1)
datalist = np.zeros((len(lines),len(labname)))
    

for j in range(len(lines)):
    for i in range(len(labname)):
        if labname[i] in lines[j]:
            datalist[j,i] = 1 
        else: 
            datalist[j,i] = 0

print("元データ\n",datalist)

##数量化３類の計算
bnumber = np.sum(datalist, axis= 0)
b = np.zeros((len(labname),len(labname)))
for i in range(len(labname)):
    b[i,i] = bnumber[i]


cnumber = np.sum(datalist, axis=1)
c = np.zeros((len(lines),len(lines)))
for i in range(len(lines)):
    c[i,i] = cnumber[i]

datalist_t = datalist.T

for i in range(0,len(labname)):
    if b[i,i] != 0:
        b[i,i] = pow(b[i,i],-0.5)

for i in range(0,len(lines)):
    c[i,i] = pow(c[i,i],-1)

h = b @ datalist_t @ c @ datalist @ b

w,v = LA.eig(h)

sort_index = np.argsort(w)[::-1]
sort_w = w[sort_index]
sort_v = v[:,sort_index]

#固有値が１でなく、最も大きいものを使って解析（w[1]）
r = pow(w[1],0.5)

x = b @ v[:,1]
y = c @ datalist @ x / r


##０票ならソートした時最右に持っていく
for i in range(len(labname)):
    if bnumber[i] == 0:
        x[i] = 1

sortx_index = np.argsort(x,axis = 0)
sort_data = datalist[:,sortx_index]
sorty_index = np.argsort(y,axis = 0)
sort_data = sort_data[sorty_index,:]

print("数量化３類結果")
print(" ",sortx_index)
for i in range(len(lines)):
    if sorty_index[i] < 10:
        st = " " + str(sorty_index[i]) +  ":" 
    else:
        st = str(sorty_index[i]) +  ":"
    for j in range(len(labname)):
        if sort_data[i,j] == 1:
            plt.scatter(j,i)
            st = st + " 1 "
        else:
            st = st + " 0 "
    print(st)

plt.title("Three quantifications")
plt.xlabel("lab")
plt.ylabel("student")
plt.grid()
plt.show()

##0票を除外してプロット
#y軸は固有値が１のものを除いた中で２番目に大きいもので解析
x2 = b @ v[:,2]
x3 = np.zeros((len(labname),2))
for i in range(len(labname)):
    x3[i,0] = x[i]
    x3[i,1] = x2[i]
    if x[i] != 1: 
        if i < 10:
            plt.scatter(x[i],x2[i],label = str(i))
        else:
            plt.scatter(x[i], x2[i], label = str(i), marker = ",")

plt.title("x score")
plt.xlabel("x2")
plt.ylabel("x3")
plt.legend(loc='upper right',
           bbox_to_anchor=(0.7,0.7, 0.5, .5), 
           borderaxespad=0.,)
plt.show()


y2 = c @ datalist @ x2 / r
y3 = np.zeros((len(lines),2))
for i in range(len(lines)):
    y3[i,0] = y[i]
    y3[i,1] = y2[i]
    if y[i] != 1: 
        if i < 10:
            plt.scatter(y[i],y2[i],label = str(i))
        elif i < 20:
            plt.scatter(y[i], y2[i], label = str(i), marker = ",")
        else:
            plt.scatter(y[i], y2[i], label = str(i), marker = "*")
            
plt.title("y score")
plt.xlabel("y2")
plt.ylabel("y3")
plt.legend(loc='upper right',
           bbox_to_anchor=(0.7,0.7, 0.5, .5), 
           borderaxespad=0.,)
plt.show()


##数量化３類の結果を用いてクラスター分析
l = linkage(x3, method='ward', metric='euclidean')

set_link_color_palette(['red','orange','blue','green' ])
dn = dendrogram(l,color_threshold=0.4,above_threshold_color='black')
plt.title("x cluster")
plt.show()



l = linkage(y3, method='ward', metric='euclidean')

set_link_color_palette(['red','orange','blue','green'])
dn = dendrogram(l,color_threshold=0.2,above_threshold_color='black')
plt.title("y cluster")
plt.show()

