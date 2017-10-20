from __future__ import division
from numpy import * 
from numpy.linalg import *
from matplotlib.pyplot import*
import matplotlib.ticker
from scipy.optimize import curve_fit

import glob, os

def findFiles(stikkord):
	filer = []
	planets = []
	for file in glob.glob("*.txt"):
		a = file.find("_")
		if stikkord in file:
			filer.append(file)
			planet = file.find("-")
			planet = file[0:planet] #+ " "+ file[planet +1:a]
			planets.append(planet)
	return filer, planets



"""
algoritmer = ["euler", "verlet"]
for algoritme in algoritmer:
	files, planets = findFiles(algoritme)
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
	#plot(time, totkin+totpot)
	figure()
	plot (time, totkin +totpot, label = algoritme)
	#ylim([0.000059, 0.0000595])
	title("Totkin ")

	legend()
show()
"""

algoritmer = ["euler", "verlet"]
for algoritme in algoritmer:
	figure()
	#ylim([0.8,1.05])
	files, planets = findFiles(algoritme)
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

		plot(x,y, label = planets[i] + ' '+ algoritme)
	legend()
show()
"""



time,x,y,vx,vy = loadtxt('mars-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, label = 'mars')
time,x,y,vx,vy = loadtxt('earth-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, label = 'earth')
time,x,y,vx,vy = loadtxt('sun-sun_earth_mars.txt',unpack=True, skiprows=1)
plot(x,y, '*', label = 'earth')
legend()
show()
"""