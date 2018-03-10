#include <iostream>
#include <dlfcn.h>
#include "rlib.h"

using namespace std;

int main(int argc, char *argv[])
{
    void *handle;
    handle = dlopen(argv[1], RTLD_NOW);
    if (!handle)
    {
           printf("The error is %s", dlerror());
    }

    rlib benji;
	benji.init();
    benji.printme();
    return 0 ;
}
