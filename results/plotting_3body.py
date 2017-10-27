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
    masses = []
    for file in glob.glob(mappe + "*.txt"):
        if stikkord in file:
            filer.append(file)
            planet = file[len(mappe):-len(stikkord)-10]
            mass = file[len(mappe)+len(planet):-len(stikkord)-4]
            planets.append(planet)
            masses.append(mass)

    return filer, planets, masses

stikkord = "-massJupiter"
# -euler,-verlet,-allplanets

filer, planets, masses = findFiles(stikkord)

print filer,planets,masses

totkin =[]
totpot = []
totangu = []

figure(1)
title("Three body system. Jupiter's mass is %s"%masses[0])

figure(2)
title("Three body system. Jupiter's mass is %s"%masses[1])

figure(3)
title("Three body system. Jupiter's mass is %s"%masses[2])

figure(4)
title("Three body system. Jupiter's mass is %s"%masses[0])

figure(5)
title("Three body system. Jupiter's mass is %s"%masses[1])

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
    if masses[i] == "1.0000":
        figure(1)
        plot(x,y, label= planets[i])
        plot(x[-1],y[-1],'o',markersize=1.5)
        if planets[i] != "jupiter":
            figure(4)
            plot(x,y, label= planets[i])
            plot(x[-1],y[-1],'o',markersize=1.5)
    elif masses[i] == "10.000":
        figure(2)
        plot(x,y, label=planets[i])
        plot(x[-1],y[-1],'o',markersize=1.5)
        if planets[i] != "jupiter":
            figure(5)
            plot(x,y, label= planets[i])
            plot(x[-1],y[-1],'o',markersize=1.5)
    elif masses[i] == "1000.0":
        figure(3)
        plot(x,y, label = planets[i])
        plot(x[-1],y[-1],'o',markersize=1.5)

for i in range(1,6):
    if i<=4:
        figure(i)
        legend()
        savefig("plots/Jupitermass_is_%s_earth.pdf"%masses[i-5])
    else:
        figure(i)
        legend()
        savefig("plots/Jupitermass_is_%s.pdf"%masses[i-1])
        
    
"""    
legend(loc=1)
title("Orbits of Earth and Jupiter")
xlabel("Position, x-direction [AU]")
ylabel("Position, y-direction [AU]")
savefig("plots/plotof%s.pdf"%(stikkord))
tight_layout()

figure()
plot(time, totangu,linewidth=1.0) 
title("Angular momentum %s" %stikkord)
xlabel("Time [Years]")
ylabel("Angular momentum [AU/year]")
ymax = max(totangu)
ymin = min(totangu)
ylim([ymin*0.999,ymax*1.001])
savefig("plots/angularmomentum%s.pdf"%stikkord)
legend()
tight_layout()


figure(figsize=(7,8))
subplot(3,1, 1)
title("Total kinetic energy")
plot(time, totkin)
xlabel("Time [Years]")
ylabel("$E_k$ [$J_{ast}$]")
ymax = max(totkin)
ymin = min(totkin)
ylim([ymin*0.9998,ymax*1.0002])
legend()
tight_layout()

subplot(3,1, 2)
title("Total potential energy")
plot(time, totpot)
xlabel("Time [Years]")
ylabel("$E_p$ [$J_{ast}$]")
ymax = max(totpot)
ymin = min(totpot)
ylim([ymin*0.9998,ymax*1.0002])
legend()
tight_layout()

subplot(3,1, 3)
title("Total energy %s" %stikkord)
plot(time, totkin+totpot)
xlabel("Time [Years]")
ylabel("$E_p+E_k$ [$J_{ast}$]")
ymax = max(totkin+totpot)
ymin = min(totkin+totpot)
ylim([ymin*0.9998,ymax*1.0002])
ticklabel_format(style = 'sci', axis = 'y')
savefig("plots/totalenergy%s.pdf"%stikkord)
legend()
tight_layout()
"""
show()