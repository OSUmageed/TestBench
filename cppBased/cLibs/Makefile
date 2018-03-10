
vs = vlib.so
ts = tlib.so
mains = mApp

all: vs ts mains

vs: rlib.cpp vlib.h
	g++ -shared -fPIC rlib.cpp -o vlib.so -DVLNOW

ts: rlib.cpp tlib.h
	g++ -shared -fPIC rlib.cpp -o tlib.so -DTLNOW

mains: maintest.cpp
	g++  maintest.cpp -o mApp -ldl
