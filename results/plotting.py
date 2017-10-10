from __future__ import division
from numpy import * 
from numpy.linalg import *
from matplotlib.pyplot import*
import matplotlib.ticker
from scipy.optimize import curve_fit

import glob, os

time,x,y,vx,vy = loadtxt('test1.txt',unpack=True, skiprows=1)

plot(x,y)
show()