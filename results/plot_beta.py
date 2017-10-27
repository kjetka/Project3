from __future__ import division
import numpy as np
#from numpy.linalg import *
import matplotlib.pyplot as plt
#import matplotlib.ticker

import glob#, os
mappe = "text/"
filer = []
def findFiles(stikkord):
    for file in glob.glob(mappe + "*.txt"):
        a = file.find(stikkord)
        print a
        if a<0:
            print "no match"
        else:
            filer.append(file)
    return filer

stikkord = "earth-beta-is"
filer = findFiles(stikkord)
figure(figsize=(5,5))
print "filer er" 
print filer
beta = 2.2

for i in range(len(filer)):
    time,x ,y ,vx ,vy ,KineticEnergy ,PotentialEnergy , Angular = np.loadtxt(filer[i],unpack=True, skiprows=1)
    plt.plot(x,y, '--' if abs(beta -3.1)<=0.1 else '-',linewidth=1.0,label = "$\\beta$ = %.1f"%beta)
    beta = beta + 0.3
plt.title("Changing the gravitational force (time = %.1f years)"%time[-1])
plt.xlabel("Position, x-direction")
plt.ylabel("Position, y-direction")
plt.legend()
plt.savefig("plots/diffenrent_gravitation.pdf")
plt.show()