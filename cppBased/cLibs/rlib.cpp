#include <iostream>
#include "rlib.h"
#include "vlib.h"
 
using namespace std;
void rlib::init()
{
   cout << "rlib::init: Hello World!! " << endl ;
}

void rlib::synaptic(int multi)
{
   cout << "Now adding " << multi*b << endl ;
}
 
extern "C" void reinterpret(void *r)
{
    rlib *rr = reinterpret_cast<rlib *> r
    *r = *rr

}


//Define functions with C symbols (create/destroy TestLib instance).
extern "C" rlib* create()
{
    return new rlib;
}
extern "C" void destroy(rlib* Tl)
{
   delete Tl ;
}

//Change it