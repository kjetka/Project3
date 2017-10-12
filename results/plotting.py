from __future__ import division
from numpy import * 
from numpy.linalg import *
from matplotlib.pyplot import*
import matplotlib.ticker
from scipy.optimize import curve_fit

import glob, os

time,x,y,vx,vy = loadtxt('mars-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, label = 'mars')
time,x,y,vx,vy = loadtxt('earth-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, label = 'earth')
time,x,y,vx,vy = loadtxt('sun-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, '*', label = 'earth')
legend()
show()