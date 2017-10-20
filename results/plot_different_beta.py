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
    time,x,y,vx,vy,kin,pot = np.loadtxt(filename,unpack=True, skiprows=1)
    name = filename[:-4]
    for i in name.split('-'):
        try:
            #trying to convert i to float
            beta = float(i)
            #break the loop if i is the first string that's successfully converted
            break
        except:
            continue
    plt.plot(x,y, label = "$\beta = $ %.2f"%beta)
    plt.hold('on')

#plt.axis([-1.2,2.0,-1.2,1.2])
plt.title('The earth orbit for beta = %.2f' %beta)
plt.xlabel('Position, x-direction')
plt.ylabel('Position, y-direction')
#plt.plot(0,0,'o', label = "The sun")
plt.legend()
plt.savefig('orbit_beta_is_%.2f.pdf'%beta)