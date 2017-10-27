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
    for file in glob.glob(mappe + "*.txt")
        if stikkord in file:
            print "Yes"
            filer.append(file)
            dt = file[len(mappe):-len(stikkord)-4]
            timesteps.append(dt)

    return filer, timesteps

filer, timesteps = findFiles("-timestep_eu")#"-timesteps_ve"

print filer, timesteps

figure(figsize=(7,8))

for file in filer:
    subplot()
    time,x,y,vx,vy,kin,pot,ang = loadtxt(file,unpack=True, skiprows=1) 
    plot(x,y)
    plot(x[-1],y[-1],'o')
    title("Earth's orbit for 100 years with dt=%s %s" %(timesteps[i][:-5],stikkord))
    xlabel("Position, x-direction [AU]")
    ylabel("Position, y-direction [AU]")
    
    
show()