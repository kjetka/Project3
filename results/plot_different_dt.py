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
            a = file.find("sun")
            if a<0:
                filer.append(file)
                steps = file[len(mappe)+6:-len(stikkord)-4]
                dt = 100./float(steps)
                timesteps.append(dt)

    return filer, timesteps

filer, timesteps = findFiles("timestep_ve")#"-timesteps_ve"

stikkord="Velocity Verlet method"
#stikkord = "Eulers method"
print filer, timesteps

figure(figsize=(5.5,9))
i = 1
for file in filer:
    subplot(3,1,i)
    time,x,y,vx,vy,kin,pot,ang = loadtxt(file,unpack=True, skiprows=1) 
    plot(x,y, label = "earth")
    plot(x[-1],y[-1],'o')
    plot(0,0, 'o', label="sun")
    title("Earth's orbit for 100 years with dt=%s %s" %(timesteps[i-1],stikkord))
    xlabel("Position, x-direction [AU]")
    ylabel("Position, y-direction [AU]")
    legend(loc=2)
    tight_layout()
    i += 1
    
savefig("plots/different_timesteps_%s.pdf"%stikkord) 
show()