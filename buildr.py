#!/usr/env/python

import os
import os.path as op
import sys
import subprocess as sp
import shlex

projpath = op.abspath(op.dirname(__file__))
os.chdir(projpath)
outpath = op.join(projpath, 'bin')

wlk = os.listdir(projpath)
walker = [k for k in wlk if k.endswith(".cpp")]

outf = []
for k in walker:
    outf.append(op.join(outpath, k.split(".")[0]))

mayb = " -gencode arch=compute_35,code=sm_35 -std=c++11"

libs = " -fopenmp -O3 -lm -lcudart"

for o, w in zip(outf, walker):
    cmpstr = "mpic++ -o " + o + " " + w + libs
    cmpreal = shlex.split(cmpstr)
    proc = sp.Popen(cmpreal)
    sp.Popen.wait(proc)


