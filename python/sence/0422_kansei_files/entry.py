#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 22 17:01:03 2019

@author: akitakazuki
"""

import numpy as np

a = 10/3

print("10/3 = ",a)

a = 10 // 3

print ("10//3 = ", a)

a = [10,20,30,40]

print("\n",a)

a = list(range(10))

print("\n",a)

a = list(range(10,0,-1))

print("\n",a)

b = a[1]

a.append(50)

print("\n",a)
print("\n",b)

b = a[1:3]
print("\n",b)

c = a[-2:]
print("\n",c)

print(pow(5,0.5) / 5 * 2)