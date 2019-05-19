# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 00:35:43 2018

@author: taguchi
"""

import numpy as np
import matplotlib.pyplot as plt

####################################
# 散布図を描画する関数
# x,y: データ
# xlabel : x軸のラベル
# ylabel : y軸のラベル
####################################
def drawScatter(x,y,xlabel,ylabel):     

    # グラフの軸ラベル等の設定
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)

    # 散布図を描画
    plt.scatter(x, y)


####################################
# テスト用関数
####################################    
def test():
    # 乱数で仮想データを生成
    x = np.random.rand(100)
    y = np.random.rand(100)

    # グラフの描画
    drawScatter(x,y,"x axis","y axis")

    
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("test")
    test()
    

