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

stikkord = "-euler"
# -euler,-verlet,-allplanets

filer, planets = findFiles(stikkord)

print filer,planets

totkin =[]
totpot = []
totangu = []

figure(figsize=(5,5))

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
        
    plot(x,y, 'o' if planets[i] == "sun" else '-', linewidth=1.0,label= planets[i])
    plot(x[-1],y[-1],'ko',markersize=1.5)
    
legend(loc=1)
title("Orbit %s" %stikkord)
xlabel("Position, x-direction [AU]")
ylabel("Position, y-direction [AU]")
savefig("plots/plotof-%s%s%s.pdf"%(planets[0],planets[1],stikkord))
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
ylim([ymin*0.9999,ymax*1.0001])
legend()
tight_layout()

subplot(3,1, 2)
title("Total potential energy")
plot(time, totpot)
xlabel("Time [Years]")
ylabel("$E_p$ [$J_{ast}$]")
ymax = max(totpot)
ymin = min(totpot)
ylim([ymin*0.9999,ymax*1.0001])
legend()
tight_layout()

subplot(3,1, 3)
title("Total energy %s" %stikkord)
plot(time, totkin+totpot)
xlabel("Time [Years]")
ylabel("$E_p+E_k$ [$J_{ast}$]")
ymax = max(totkin+totpot)
ymin = min(totkin+totpot)
ylim([ymin*0.9999,ymax*1.0001])
ticklabel_format(style = 'sci', axis = 'y')
savefig("plots/totalenergy%s.pdf"%stikkord)
legend()
tight_layout()

show()