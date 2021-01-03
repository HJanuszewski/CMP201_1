import numpy as np
import matplotlib.pyplot as plt


data1 = np.loadtxt(fname='times1.txt',dtype='int',delimiter='\t')
data2 = np.loadtxt(fname='times2.txt',dtype='int',delimiter='\t')
data = [data1,data2]
fig1, ax1 = plt.subplots()
ax1.set_title("Bayer-Moore-Horsepool vs Rabin-Karp")
ax1.boxplot(data)
fig1.savefig('3.png')
#ax1.set_title("Rabin-Karp")
#ax1.boxplot(data2)
#fig1.savefig('2.png')
