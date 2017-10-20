from numpy import *
from matplotlib.pyplot import *
import glob, os

filelist = []

for filename in glob.glob("*.txt"):
    a = filename.find("sun-")
    if a<0:
        filelist.append(filename)

print filelist
plt.figure()
for filename in filelist:  
    name = filename[:-4]
    for i in name.split('-'):
        try:
            #trying to convert i to float
            beta = float(i)
            #break the loop if i is the first string that's successfully converted
            break
        except:
            continue
    time,x,y,vx,vy,kin,pot = np.loadtxt(filename,unpack=True, skiprows=1)
    plt.plot(x,y, label = "$\beta = $ %.2f"%beta)
    print "Plotted for beta = %.2" %beta
    plt.hold('on')

#plt.axis([-1.2,2.0,-1.2,1.2])
plt.title('The earth orbit for different gravitation forces')
plt.xlabel('Position, x-direction')
plt.ylabel('Position, y-direction')
#plt.plot(0,0,'o', label = "The sun")
plt.legend()
plt.savefig('orbits_For different_beta.pdf')