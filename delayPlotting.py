from subprocess import call
from math import exp

def runSimulator(arrivalRate):
	call(["/home/emil/Hack/TSIN01/simulator", str(arrivalRate), "-1"])

def parseResult():
	result = -1.0
	with open("output.txt") as f:
		for line in f:
			words = line.split()
			if words[0] == "999":
				result = float(words[5])

	return result;

def averageResult(arrivalRate, iterations):
	result = 0.0
	for i in range(iterations):
		runSimulator(arrivalRate)
		result += parseResult()

	return result / iterations


def theoreticalDelay(arrivalRate):
	a = (exp(1) - 1/2) / (1 - arrivalRate * exp(1))
	b1 = (exp(1) - 1) * (exp(arrivalRate) - 1)
	b2 = arrivalRate * (1 - b1)
	b = b1 / b2

	return a - b

with open("simulatedDelayOutput.txt", 'w') as f:
	arrivalRate = 0.05;
	f.write(str(arrivalRate) + ' ' + str(averageResult(arrivalRate, 10)) + '\n')

	arrivalRate = 0.20;
	f.write(str(arrivalRate) + ' ' + str(averageResult(arrivalRate, 10)) + '\n')

	arrivalRate = 0.35;
	f.write(str(arrivalRate) + ' ' + str(averageResult(arrivalRate, 10)) + '\n')
	
with open("theoreticalDelayOutput.txt", 'w') as f:
	arrivalIncrement = 0.005

	for i in range(1, 73):
		arrivalRate = arrivalIncrement * i;
		f.write(str(arrivalRate) + ' ' + str(theoreticalDelay(arrivalRate)) + '\n')