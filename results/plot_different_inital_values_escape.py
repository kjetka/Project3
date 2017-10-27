import numpy as np
import matplotlib.pyplot as plt
import glob, os


time,x,y,vx,vy, kin, pot, ang = np.loadtxt("text/earth-v_ini_is8.885766.txt",unpack=True, skiprows=1)
plt.figure()
plt.plot(x,y, label = "$v_{ini}$ = %.5f" %vy[0])
    

#plt.axis([-90,23,-5,50])
plt.title('Finding the escape velocity')
plt.xlabel('Posistion, x-direction')
plt.ylabel('Posistion, y-direction')
plt.plot(0,0,'o', label = "The sun")
plt.legend()
plt.savefig('escape_velocity_closeto_exact.pdf')