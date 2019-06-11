# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import numpy as np

#2
array_2 = np.array([[48.,46,2,7,14],[50,52,3,8,15],[42,58,9,11,17],[34,30,14,18,20],[25,31,39,30,24]]) 
##2.(a)
y_2a = np.zeros([3,3])

for i in range(0,3):
    for j in range(0,3):
        for k in range(0,3):
            for l in range(0,3):
                y_2a[i][j] += array_2[i+k][j+l]
print("2(a)*9",y_2a)
y_2a = y_2a / 9.0
print("2(a)\n",y_2a)

#4
###4.(a),(b) 5*5はarray_2と同じ
t = np.array([[3.,11,15],[8,10,16],[7,18,17]])

SAD = np.zeros([3,3])


for i in range(0,3):
    for j in range(0,3):
        for k in range(0,3):
            for l in range(0,3):
                SAD[i][j] += np.abs(array_2[i+k][j+l] - t[k][l ])
print("SAD\n",SAD)
