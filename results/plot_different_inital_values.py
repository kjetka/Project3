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

findFiles("earth-v_ini")


print filer
color = ['g','r', 'c','m', 'y', 'k', 'brown', 'hotpink', 'orange', 'purple']
i=0
figure()
for file in filer:  
    time,x,y,vx,vy,kin, pot, angmom = loadtxt(file,unpack=True, skiprows=1)
    plot(x,y, color[i], label = "$v_{init}$ = %.2f" %vy[0])
    i+=1

x_circ = np.linspace(-1,1,100)

axis([-1.2,2.0,-1.2,1.2])
title('Finding the circular orbit')
xlabel('Posistion, x-direction')
ylabel('Posistion, y-direction')
sun_pl = color[i]+'o'
plot(0,0,sun_pl, label = "Sun")
plot(x_circ, np.sqrt(1-x_circ**2),'b--', label='Circuar orbit')
plot(x_circ, -np.sqrt(1-x_circ**2),'b--')
legend()

savefig('plots/circular_orbit.pdf')

"""

findFiles("convergence_euler")

figure()
for file in filer:  
    dt, energy, delta_energy = loadtxt(file,unpack=True, skiprows=3)
    
#plot(dt, energy, label='Total energy')
plot(log10(dt)[1:], log10(delta_energy)[1:], label = 'Change in energy')
legend()
title('Energy convergence - circular orbit')
xlabel('log(Timestep [year])')
ylabel('$\log(\Delta E_{tot}) $')
#savefig('plots/convergence_euler.pdf')
show()
# I think we have reach the occillation
    
    
    
    
    
    
"""