import re
import string


producePurchased = {}
sortedProducePurchased = {}
f = open("Purchases.txt", "r")
for x in f:
    x=x.rstrip('\n')
    if x in producePurchased.keys():
        producePurchased[x] = producePurchased[x]+1;
    else:
        producePurchased[x] = 1
sorted(producePurchased)
for i in sorted(producePurchased):
    sortedProducePurchased[i] = producePurchased[i]
f.close()




def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print(v)
    return 100;

def PrintProduceItems():
    print(sortedProducePurchased)

def SquareValue(v):
    return v * v

def MultiplicationTable(a):
    for x in range(1, 11):
        print(str(a) + " x " + str(x) + " = " + str(a*x)) 
    return 0

def DoubleValue(a):
    print(str(a*2))
    return a * 2

def PrintAllItems():
    for key in sortedProducePurchased.keys():
        print(key, end = ": ", flush = True)
        print(sortedProducePurchased[key])

def FindItem(key):
    for x in sortedProducePurchased.keys():
        if key == x:
            return sortedProducePurchased[key]
    return 0;

def Histogram():
    fl= open("frequency.dat", "w")
    for x in sortedProducePurchased.keys():
        fl.write(x)
        fl.write(' ')
        fl.write(str(sortedProducePurchased[x]))
        fl.write("\n")
    fl.close()
