/**
    Base class for equations
*/

#ifndef EQ_H
#define EQ_H


// #ifndef SPECIFIC
// 	#define WHERE WHEREISIT
// 	#define SPECIFIC Wave
// #endif

#include "equations/eqHead.h"

//str defaultOut = "/something/From/Makefile";

class Equation
{
private:
	jsons inJ, solution;
	SPECIFIC *chosenEquation = new SPECIFIC;

	void parseArgs(int argc, char *argv[])
	{
		if (argc>4)
		{
			str inarg;
			for (int k=4; k<argc; k+=2)
			{
				inarg = argv[k];
				inJ[inarg] = atof(argv[k+1]);
			}
		}
	};

public:
	str tpath, spath;
	double dt, lx, tf, freq;
	int tpb, gridSize, stateSize, bitSize, nWrite, height;
	double dx;
	int bks;

	Equation(inputf inFile, str outpath, int argc, char *argv[]);

	~Equation();

	void makeInitialCondition(states *nState);

	void solutionOutput(states *outState, double tstamp);
};

Equation::Equation(inputf inFile, str outpath, int argc, char *argv[])
{
    inFile >> inJ;
    inFile.close();
    parseArgs(argc, argv);
    stateSize = sizeof(states);
    gridSize = inJ["nX"].asInt();
    lx = inJ["lx"].asDouble();
    bitSize = stateSize*gridSize;
    freq = inJ["freq"].asDouble();
    tpb = inJ["tpb"].asInt();
    tf = inJ["tf"].asDouble();
    dx = lx/(double)gridSize; // Spatial step
    bks = gridSize/tpb;
    height = tpb/2;

    if (!freq) freq = tf*2.0;

    tpath = outpath + "/t" + fspec;
    spath = outpath + "/s" + fspec;

    nWrite = tf/freq + 2; //Future, use to preallocate solution array. (OR USE vector)

}

Equation::~Equation()
{
	outputf solutionOut(spath.c_str(), std::ofstream::trunc);
	solution["meta"] = inJ;
	solutionOut << solution;
	solutionOut.close();
	delete[] chosenEquation;	
};

void Equation::makeInitialCondition(states *nState)
{
    inJ["dx"] = dx;
    chosenEquation->initEq(inJ);
    for (int i=0; i<gridSize; i++)
    {
        chosenEquation->initState(nState, i);
    }
    solutionOutput(nState, 0.0);
}

void Equation::solutionOutput(states *outState, double tstamp)
{
    str tsts = std::to_string(tstamp);
    for (int k=0; k<NVARS; k++)
    {
        for (int i=0; i<gridSize; i++)
        {
            str xpts = std::to_string((double)i*dx);
            solution[outVars[k]][tsts][xpts] = chosenEquation->printout(outState + i, k);
        }
    }
}



#endif