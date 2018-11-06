### A Python Code with simple modules that are then disassembled for 
### assembly code practice.

import dis
def addten(x):
    # this function assigns to new variable z
    z = x + 10
    return z

def summ(x, y):
    return x + y

def divide(x, y):
    return x/y

def ifs(x):
    if x == 0:
        return 0
    elif x == 1:
        return 1
    else:
        return -1

def fibonacci(num):
    if 0:
        return 0
    elif 1:
        return 1
    else:
        return fibonacci(num-2) + fibonacci(num-1)

def loop(x):
    # this loop goes from 0 to 4
    for i in range(5):
        x = x - 1    
    return x

dis.dis(addten)