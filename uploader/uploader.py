#!/usr/bin/env python

# simple program to compile and upload Arduino code using the Arduino command line

import subprocess
import sys
import os.path

libsFile = "libs.txt"

arduinoProg = "./bin/Arduino.app/Contents/MacOS/Arduino"

projectFile = sys.argv[1]

codeFile = open(projectFile, 'r')
startLine = codeFile.readline()[3:].strip()
prereqLine = codeFile.readline()[3:].strip()
actionLine = codeFile.readline()[3:].strip()
boardLine = codeFile.readline()[3:].strip()
portLine = codeFile.readline()[3:].strip()
endLine = codeFile.readline()[3:].strip()
codeFile.close()

installLibs = True

if os.path.isfile(libsFile):
	with open(libsFile) as libs:
		for line in libs:
			if prereqLine in line:
				installLibs = False
else:
	installLibs = True
	
if installLibs:
	prereqCall = arduinoProg + " --" + prereqLine
	
	print "\n-- Installing prereqs --"
	
	lresult = subprocess.call(prereqCall, shell=True)
	
	if lresult != 0:
		print "\n Prereqs failed - result code = %s --" %(lresult)
	else:
		print "\n-- Prereqs successful --"
		
		with open(libsFile, "a") as libs:
			libs.write(prereqLine + "\n")
else:
	print "\n-- Prereqs satisfied --"

if (startLine != "python-build-start" or endLine != "python-build-end"):
	print "Sorry, can't process file"
	sys.exit()

arduinoCommand = arduinoProg + " --" + actionLine + " --board " + boardLine + " --port " + portLine + " " + projectFile

print "\n\n -- Arduino Command --"
print arduinoCommand

print "-- Starting %s --\n" %(actionLine)

presult = subprocess.call(arduinoCommand, shell=True)

if presult != 0:
	print "\n Failed - result code = %s --" %(presult)
else:
	print "\n-- Success --"