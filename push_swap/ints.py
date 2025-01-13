#!/bin/python3
import sys, random

if len(sys.argv) != 2:
    exit(1)
ints = random.sample(range(0, int(sys.argv[1])), int(sys.argv[1]))
print(" ".join([str(i) for i in ints]))

