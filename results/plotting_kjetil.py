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
xlabel('x-direction, Au')
ylabel('y-direction, Au')
title('Position of 3-body system around barrycentre')
savefig('plots/3bodyCentric_position.pdf')

figure()
plot(time , totangu*1e6, label = 'Total angular momentum')
ylabel(r'Angular momentum, $\mu kgAu^2/year')
xlabel('time, years')
legend()
title('Angular momentum for the three-body system')
savefig('plots/3bodyCentric_angular.pdf')


#ylim([0.01365,0.01368])

figure()
plot(time, totpot+ totkin, label = 'Total Energy')
ylabel(r'Energy, $J_{ast}$')
xlabel('time, years')
ylim([-0.016,-0.01])
legend()
title('Energy for the three-body system')
savefig('plots/3bodyCentric_energy.pdf')

show()






figure 

figure()
plot(time , totangu*1e6, label = 'Total angular momentum')
ylabel(r'Angular momentum, $\mu kgAu^2/year')
xlabel('time, years')
ticklabel_format(style='plain', axis='x', scilimits=(0,0))
legend()
title('Angular momentum for the three-body system')
show()
