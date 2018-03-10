#ifndef VLIB_H
#define VLIB_H
#include "rlib.h"

class vlib
{
	friend rlib;

private:
	int c, b, d;
	double bb;
public:
	vlib(int *g)
	{
		c = g[0];
		b = g[1];
		d = g[2];
		b = 3.14;
	};
};

typedef vlib eqdome;

#endif
