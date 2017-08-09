#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
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

    std::vector<int> ivec = myJ["arr"];
    std::vector<int> sm(ivec.size());

    std::partial_sum(ivec.begin(), ivec.end(), sm.begin());

    std::cout << dt*5 << std::endl;
    std::cout << sm[0] << " " << sm.back() << std::endl;
    return 0;
}