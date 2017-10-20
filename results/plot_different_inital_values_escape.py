import numpy as np
import matplotlib.pyplot as plt
import glob, os

filelist = []

for filename in glob.glob("*.txt"):
    a = filename.find("sun-")
    if a<0:
        filelist.append(filename)

print filelist
plt.figure()
for filename in filelist:  
    time,x,y,vx,vy = np.loadtxt(filename,unpack=True, skiprows=2)
    
    plt.plot(x,y, label = "$v_{ini}$ = %.2f" %vy[0])
    plt.hold('on')

x_circ = np.linspace(-1,1,100)

#plt.axis([-90,23,-5,50])
plt.title('Finding the escape velocity')
plt.xlabel('Posistion, x-direction')
plt.ylabel('Posistion, y-direction')
plt.plot(0,0,'o', label = "The sun")
plt.legend()
plt.savefig('escape_velocity_closeto_exact.pdf')