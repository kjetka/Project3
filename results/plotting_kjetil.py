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


"""

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







figure 

figure()
plot(time , totangu*1e6, label = 'Total angular momentum')
ylabel(r'Angular momentum, $\mu kgAu^2/year')
xlabel('time, years')
ticklabel_format(style='plain', axis='x', scilimits=(0,0))
legend()
title('Angular momentum for the three-body system')
show()
"""

"""

filer, planets = findFiles("earth-euler")
time,x,y,vx,vy,KineticEnergy,PotentialEnergy, Angular = loadtxt(filer[0],unpack=True, skiprows=1)
toten_eu = KineticEnergy + PotentialEnergy
filer1, planets1 = findFiles("sun-euler")
time1,x1,y1,vx1,vy1,KineticEnergy1,PotentialEnergy1, Angular1 = loadtxt(filer1[0],unpack=True, skiprows=1)
toten_eu = toten_eu+ KineticEnergy1 + PotentialEnergy1


filer, planets = findFiles("earth-verlet")
time,x,y,vx,vy,KineticEnergy,PotentialEnergy, Angular = loadtxt(filer[0],unpack=True, skiprows=1)
toten_ver = KineticEnergy + PotentialEnergy
filer1, planets1 = findFiles("sun-verlet")
time1,x1,y1,vx1,vy1,KineticEnergy1,PotentialEnergy1, Angular1 = loadtxt(filer1[0],unpack=True, skiprows=1)
toten_ver =toten_ver + KineticEnergy1 + PotentialEnergy1

dE_ver = []
dE_eu = []
dt = []
for i in range(1,len(toten_ver)):
    de_v = toten_ver[i]-toten_ver[i-1]
    dE_ver.append(de_v)
    de_e = toten_eu[i]-toten_eu[i-1]
    dE_eu.append(de_e)

    dt.append(time[i])

figure()
plot(dt, dE_ver)
plot(dt, dE_eu)


figure()

plot(time, toten_eu, label =r'$E_{tot}$ Euler')
plot(time, toten_ver, label =r'$E_{tot}$ vVerlet')
legend()
xlabel('time, years')
ylabel(r'Energy, $J_{ast}$')
title('Total energy, Euler and vVerlet method')
savefig('plots/toten_compar.pdf')
show()

"""


stikkord = "3bodynoBary"
# -euler,-verlet,-allplanets

filer, planets = findFiles(stikkord)
for i in range(len(planets)):
    planet = planets[i]
    planets[i] =planet[0:-1]


toten = []
totan = []
figure()

for i in range(len(filer)):
    fil = filer[i]
    time,x,y,vx,vy,KineticEnergy,PotentialEnergy, Angular = loadtxt(fil,unpack=True, skiprows=1)
    tote = KineticEnergy + PotentialEnergy
    tota = Angular
    if i==0:
        toten = tote
        totan = tota
    else:
        toten += tote
        totan += tota
    plot(x,y, label = planets[i])
legend()
xlabel ('x-direction, Au')
ylabel ('y-direction, Au')
title('Movement of 3-body, sun as origin')
savefig('plots/3body_nobary.pdf')

"""figure()
plot(time, toten)
ylim([-0.014,-0.012])
"""
#figure()
#plot(time, totan*1e6)
#ylim([-0.014,-0.012])



stikkord = "3bodyCentric"
# -euler,-verlet,-allplanets

filer, planets = findFiles(stikkord)
for i in range(len(planets)):
    planet = planets[i]
    planets[i] =planet[0:-1]


fil = filer[0]
toten = []
totan = []
figure()
for i in range(len(filer)):
    fil = filer[i]
    time,x,y,vx,vy,KineticEnergy,PotentialEnergy, Angular = loadtxt(fil,unpack=True, skiprows=1)
    tote = KineticEnergy + PotentialEnergy
    tota = Angular
    if i==0:
        toten = tote
        totan = tota
    else:
        toten += tote
        totan += tota
    plot(x,y, label = planets[i])
legend()
xlabel ('x-direction, Au')
ylabel ('y-direction, Au')
title('Movement of 3-body, barycentre as origin')
savefig('plots/3body_bary.pdf')

print time[-1]

"""
figure()
plot(time, toten)
ylim([-0.014,-0.012])

figure()
title('bc')
plot(time, totan*1e6)
print totan[0]
print totan[1]
show()



"""