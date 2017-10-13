import numpy as np
import matplotlib.pyplot as plt
import glob,os

filelist = []

for filename in glob.glob("*.txt"):
    a = filename.find("sun-")
    if a<0:
        filelist.append(filename)

print filelist
plt.figure()
for filename in filelist:  
    time,x,y,vx,vy = np.loadtxt(filename,unpack=True, skiprows=2)
    
    plt.plot(x,y, label = "v_{ini} = %g" %vy[0])
    plt.hold('on')

plt.legend()
#plt.axis([-30,3,-13,10])
plt.plot(0,0,'o')
plt.savefig('test2.pdf')