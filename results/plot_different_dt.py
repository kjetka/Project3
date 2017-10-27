from __future__ import division
from numpy import * 
from numpy.linalg import *
from matplotlib.pyplot import*
import matplotlib.ticker
from scipy.optimize import curve_fit

import glob, os
mappe = "text/"
def findFiles(stikkord):
    filer = []
    timesteps = []
    for file in glob.glob(mappe + "*.txt"):
        if stikkord in file:
            filer.append(file)
            dt = file[len(mappe):-len(stikkord)-4]
            timesteps.append(dt)

    return filer, timesteps

filer, timesteps = findFiles("-timesteps-eu")#"-timesteps-ve"

plt.figure()
for file in filer:  
    time,x,y,vx,vy,kin,pot,ang = loadtxt(file,unpack=True, skiprows=1)
        
    plt.plot(x,y)
    title("Earth's orbit for 100 years with dt=%s" %dt)
    plt.hold('on')

#plt.axis([-1.2,2.0,-1.2,1.2])
plt.title('The earth orbit for beta = %.2f' %beta)
plt.xlabel('Posistion, x-direction')
plt.ylabel('Posistion, y-direction')
#plt.plot(0,0,'o', label = "The sun")
plt.legend()
plt.savefig('orbit_beta_is_%.2f.pdf'%beta)