#!/usr/bin/python

import sys

f = open(sys.argv[1])
k = int(sys.argv[2])

lines = f.readlines()
f.close()

if k > 0 :
  for s in lines[(- k):] :
    print s.strip()

