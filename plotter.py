from array import *

frequencies = array('d', [0] * 100);

with open("output.txt") as f:
	for line in f:
		if line[0] == '#':
			continue

		word = line.split()[1]

		index = int(word)

		frequencies[index] += 1

sum = 0.0
latestValueIndex = 0
for i in xrange(100):
	frequencies[i] = frequencies[i] / 1000
	sum += frequencies[i]

	if frequencies[i] != 0:
		latestValueIndex = i;

print 'Summan blev ' + str(sum)

with open("freq.txt", 'w')as f:
	for i in xrange(latestValueIndex + 1):
		f.write(str(i + 1) + ' ' + str(frequencies[i]) + '\n')