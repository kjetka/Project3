from numpy import *
from matplotlib.pyplot import *
import glob, os
mappe = "text/"
filer = []
def findFiles(stikkord):    
    for file in glob.glob(mappe + "*.txt"):
        if stikkord in file:
            filer.append(file)
    return filer
"""
findFiles("earth-v_ini")

print filer

figure()
for file in filer:  
    time,x,y,vx,vy,kin, pot = loadtxt(file,unpack=True, skiprows=1)
    plot(x,y, label = "$v_{ini}$ = %.2f" %vy[0])

x_circ = np.linspace(-1,1,100)

axis([-1.2,2.0,-1.2,1.2])
title('Finding the circular orbit')
xlabel('Posistion, x-direction')
ylabel('Posistion, y-direction')
plot(0,0,'o', label = "The sun")
plot(x_circ, np.sqrt(1-x_circ**2),'y--', label='Circuar orbit')
plot(x_circ, -np.sqrt(1-x_circ**2),'y--')
legend()
savefig('plots/circular_orbit.pdf')

"""

findFiles("convergence")

figure()
for file in filer:  
    dt, energy, delta_energy = loadtxt(file,unpack=True, skiprows=3)
    
#plot(dt, energy, label='Total energy')
plot(log10(dt)[1:], log10(delta_energy)[1:], label = 'Change in energy')
legend()
title('Energy convergence - circular orbit')
xlabel('log(Timestep [year])')
ylabel('$\log(\Delta E_{tot}) $')
savefig('plots/convergence.pdf')

# I think we have reach the occillation
    
    
    
    
    
    
    