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
        if stikkord in file:
            filer.append(file)
            planet = file[len(mappe):-len(stikkord)-4]
            planets.append(planet)

    return filer, planets

stikkord = "3bodyCentric"
# -euler,-verlet,-allplanets

filer, planets = findFiles(stikkord)




totkin =[]
totpot = []
totangu = []

for i in range(len(filer)):

    time,x,y,vx,vy,KineticEnergy,PotentialEnergy, Angular = loadtxt(filer[i],unpack=True, skiprows=1)
    
    if i==0:
        totkin = KineticEnergy
        totpot = PotentialEnergy
        totangu = Angular
    else:
        totkin += KineticEnergy
        totpot += PotentialEnergy
        totangu += Angular
    figure(1)
    plot(x,y, label = planets[i])

figure(1)
legend()
xlabel('x, Au')
xlabel('y, Au')
title('Position of 3-body system around barrycentre')
savefig('plots/position_3bodyCentric.pdf')

figure()
plot(time , totangu, label = 'Total angular momentum')
ylabel(r'Angular momentum, $kgAu^2/year$')
xlabel('time, years')
#ylim([-0.016,-0.01])
legend()
title('Angular momentum for the three-body system')
savefig('plots/angular_3bodyCentric.pdf')


#ylim([0.01365,0.01368])

figure()
plot(time, totpot+ totkin, label = 'Total Energy')
ylabel(r'Energy, $J_{ast}$')
xlabel('time, years')
ylim([-0.016,-0.01])
legend()
title('Energy for the three-body system')
savefig('plots/energy_3bodyCentric.pdf')

show()





