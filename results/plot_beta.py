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

print "filer er" 
print filer
beta = 2.3

for i in range(len(filer)):
    time, x,y,vx,vy,KineticEnergy,PotentialEnergy = np.loadtxt(filer[i],unpack=True, skiprows=1)
    plt.plot(x,y, label = "beta = %.1f"%beta)
    beta = beta + 0.3
plt.title("Changing the gravitational force")
plt.xlabel("Position, x-direction")
plt.ylabel("Position, y-direction")
plt.legend()
plt.savefig("diffenrent_gravitation.pdf")
plt.show()