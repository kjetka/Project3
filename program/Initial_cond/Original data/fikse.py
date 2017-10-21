from __future__ import division
from matplotlib.pyplot import *
from numpy import * 
import glob, os


filer = []
filnavn = []
for file in glob.glob('*.txt'):			# edit: tok bort maaletype
	filer.append(file)

file =  filer[0]

with open(file,'r') as infile:
		go_on = False
		firstline = infile.readline()
		thisline = firstline.split()
		print "-------------"

		for i in range(len(thisline)):
			her = thisline[i]
			if her == '$$SOE':
				print'x =? ', thisline[i+9]
				print'y =? ', thisline[i+12]
				print'z =? ', thisline[i+14]


		

