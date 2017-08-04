#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <mpi.h>
#include "../json.hpp"

using jsons =  nlohmann::json;

// Test json
int main(int argc, char *argv[])
{
    std::ifstream imzep("test.json", std::ifstream::in);
    jsons myJ;
    imzep >> myJ;
    std::cout << myJ.dump(4) << std::endl;

    int dt = myJ["dt"]; 
    std::cout << typeid(myJ["dm"]).name() << std::endl;
    imzep.close();

    std::cout << dt*5 << std::endl;
    return 0;
}