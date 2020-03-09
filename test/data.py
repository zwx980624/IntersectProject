import random
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--n", type=int)
parser.add_argument("--i", type=int)
args = parser.parse_args()
dataid = 0 
num = random.randint(1,500000)
if (args.n):
    num = args.n
if (args.i):
	dataid = args.i
data = str(num) + "\n"
test = open('test'+str(dataid)+".txt","w")
for i in range(num):
	t = random.randint(1,500000)
	if (t%2 == 0):
	    data += "C " + str(random.randint(-100000,100000)) + " " + str(random.randint(-100000,100000)) + " " + str(random.randint(1,100000)) + "\n"
	else:
	    data += "L " + str(random.randint(-100000,100000)) + " " + str(random.randint(-100000,100000)) + " " + str(random.randint(-100000,100000)) + " " + str(random.randint(-100000,100000))+ "\n"
test.write(data)
test.close