#ifndef TLIB_H
#define TLIB_H

#include "rlib.h"

class tlib
{
	friend rlib;

private:
	int b,c,d;
	double bb;

public:
	tlib(int *g)
	{
		b = g[0];
		c = g[1];
		d = g[2];
		bb = 500.15;
	};
};

typedef tlib eqdome;

#endif
