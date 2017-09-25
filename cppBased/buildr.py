#!~/anaconda/bin/python

import os
import os.path as op
import sys
import subprocess as sp
import shlex

projpath = op.abspath(op.dirname(__file__))
os.chdir(projpath)
outpath = op.join(projpath, 'bin')

wlk = os.listdir(projpath)
walker = [k for k in wlk if k.endswith(".cpp") and "jsoncpp" not in k]

outf = []
for k in walker:
    outf.append(op.join("bin", k.split(".")[0]))

libs = " -fopenmp -O3 -std=c++11 -lm -w"

for o, w in zip(outf, walker):
    cmpstr = "mpic++ " + w + " jsoncpp.cpp -o " + o + libs
    print(cmpstr)
    cmpreal = shlex.split(cmpstr)
    proc = sp.Popen(cmpreal)
    sp.Popen.wait(proc)


