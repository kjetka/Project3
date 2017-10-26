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
	planets = []
	for file in glob.glob(mappe + "*.txt"):
		a = file.find("_")
		if stikkord in file:
			filer.append(file)
			planet = file.find("-")
			planet = file[len(mappe):planet] #+ " "+ file[planet +1:a]
			planets.append(planet)

	return filer, planets

files, planets = findFiles("")
totkin =[]
totpot = []
for i in range(len(files)):

	time, x,y,vx,vy,KineticEnergy,PotentialEnergy = loadtxt(files[i],unpack=True, skiprows=1)
	if i==0:
		totkin = KineticEnergy
		totpot = PotentialEnergy
	else:
		totkin += KineticEnergy
		totpot += PotentialEnergy

	plot(x,y, label = planets[i])
legend()
show()

