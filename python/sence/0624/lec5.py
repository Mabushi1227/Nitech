# -*- coding: utf-8 -*-
"""


@author: taguchi, akitakazuki


t分布による解析

"""
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats

###################################

#CSVの読み込み

###################################
def loadCSV(filename,f_skip_first_row = False,f_skip_first_col=False):
    _skiprows = 0

    if f_skip_first_row==True:
        _skiprows = 1
        
    d = np.loadtxt(filename,delimiter=',',skiprows=_skiprows)
    

    if f_skip_first_col==True:
        d = d[:,1:]

    return d
####################################
# t分布を描画する関数
# df_list: 自由度のリスト
####################################
def drawTDistribution(df_list):
    plt.clf();

    plt.xlabel("t")
    plt.ylabel("prob")
    plt.grid(True)
    
    plt.xlim([-5,5])
    plt.ylim([0,0.45])
    
    t = np.linspace(-5,5,100)
         
    for df in df_list:
        # t分布から確率を取得
        p = stats.t.pdf(t,df)
        label = "df = " + str(df)
        plt.plot(t, p,label=label)

    # 標準正規分布の確率を描画
    p = stats.norm.pdf(t, loc=0, scale=1)
    #label = "normal"
    #plt.plot(t, p,label=label,color='black',  linestyle='dashed')
    
    #追加プログラム
    t0,t1 = stats.t.interval(0.95,50)
    plt.plot([t0, t0], [0, 0.45], 'r-')
    plt.plot([t1, t1], [0, 0.45], 'r-')
    #
    
    plt.legend()        
    
    plt.savefig("TDistribution5.png")
    plt.show()
        
####################################
# メイン関数
####################################    
if __name__ == "__main__":
    print("lecture 5")
        
    #drawTDistribution([2,10,50])
    
    drawTDistribution([50])
    t0,t1 = stats.t.interval(0.95,9)
    print("t(9,0.05) = ",t1)
    
    #教科書p30.2.2
    data = np.array([3.,4,2,9,6,7,5,6,5,4])
    m = np.mean(data)
    t = (np.mean(data) - 3.0) / pow(np.var(data,ddof=1) / len(data),0.5)
    
    print("t = ",t)
    
    p = stats.t.pdf (t,9)
    print("p:" ,p)
    print("範囲外の範囲",1-p)
    
    u0 = m + t0 * (pow(np.var(data,ddof = 1)/data.shape[0],0.5))
    u1 = m + t1 * (pow(np.var(data,ddof = 1)/data.shape[0],0.5))
    
    ##p51例題２
    data = loadCSV("../0617/data4-1_p043.csv", True, True)
    
    avr = np.mean(data, axis = 0)  
    
    Sxx = np.dot(data[:,0]-avr[0],data[:,0]-avr[0])
    Sxy = np.dot(data[:,0]-avr[0],data[:,1]-avr[1])
    
    B1 = Sxy/Sxx
    B0 = avr[1] - B1 * avr[0]
    Se = 17.5
    Ve = Se / (data.shape[0]-2)
    t = B1/()
    
    
    
    

