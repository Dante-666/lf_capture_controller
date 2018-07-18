#!/usr/bin/env python
import numpy as np
import math

f = np.linspace(1000, 20000, 256)

ex = math.pow(2, 28)
f_clk = 25e6 

p = f * ex / f_clk

p = np.around(p)

"""
Print for the Atmega code
"""
j = 256
for i in reversed(p):
    print("uint32_t EEMEM F" + str(j) + " = " + str(int(i)) + ";")
    j = j-1

f_n = p * f_clk / ex

"""
Print for the C++ code
"""
for i in (f_n):
    print("\tthis->frequencyLookup["+ str(j) +"] = "+ str(i) +";")
    j = j+1
