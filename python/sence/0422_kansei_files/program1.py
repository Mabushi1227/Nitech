#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 17:09:29 2019

@author: akitakazuki
"""

import numpy as np

a = np.arange(0,10)

b = np.arange(10,0,-1)

a_sum = a.sum() #aの合計
a_mean = a.mean() #aの平均
a_var = a.var() #aの分散

print("\n sum  = \n ",a_sum)
print("\n mean = \n ",a_mean)
print("\n var = \n ",a_var)

c = a @ b
print("\n",c)

#a,bの偏差積和 S_ab

a = a - a.mean()   #aの偏差
b = b - b.mean() #bの偏差
length = len(a)   #a,bの個数

S_ab = 0

for i in range(0,length):
     S_ab += a[i] * b[i]        
     
print("\n",S_ab)

#a,bの共分散
S_aa = np.dot(a,a)
S_bb = np.dot(b,b)

R_ab = S_ab / ((S_aa * S_bb)** 0.5)
print(R_ab)