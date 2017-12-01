#!~/anaconda/bin/python

import os
import os.path as op
import sys
import subprocess as sp
import shlex

## Change these on linux
outpath = "bin"

projpath = op.abspath(op.dirname(__file__))
os.chdir(projpath)
fulloutpath = op.join(projpath, outpath)

print os.getcwd()

wlk = os.listdir(projpath)
walker = [k for k in wlk if k.endswith(".cpp")]

outf = []
for k in walker:
    outf.append(op.join(outpath, k.split(".")[0]))

mayb = " -gencode arch=compute_35,code=sm_35 -std=c++11"

libs = " -fopenmp -std=c++11 -lm" # + " -lcudart"

for o, w in zip(outf, walker):
    try:
        cmpstr = "mpic++ -o " + o + win + " " + w + libs
        print(cmpstr)
        cmpreal = shlex.split(cmpstr)
        proc = sp.Popen(cmpreal)
        sp.Popen.wait(proc)
    except:
        continue
