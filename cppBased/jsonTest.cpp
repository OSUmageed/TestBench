#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include "../json.h"
#include <unordered_map>

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

    bool wha = myJ["mg"] == "level";

    std::cout << dt*5 << std::endl;
    std::cout << sm[0] << " " << sm.back() << std::endl;
    std::cout << wha << std::endl;

    // TestMap
    std::unordered_map<int, double> whoamap;

    std::cout << whoamap.size() << " " << whoamap.max_size() << std::endl;
    double k2;

    // std::cout << double
    for (int k=2; k<100; k++)
    {
        k2 = k*0.02635;
        std::cout << k2 << std::endl;
        whoamap.insert(std::make_pair(k, k2));
    }

    std::cout << whoamap.size() << " " << whoamap.max_size() << std::endl;

    std::string ext = ".json";
    std::string myrank = std::to_string(k2);
    std::string sout = argv[2];
    sout.append(myrank);
    sout.append(ext); 

    std::cout << k2 << std::endl;

    std::string boom = "Boom";

    bool mal = boom.compare(argv[1]);

    bool m2 = -1;

    std::cout << m2 << " " << mal << std::endl;

    std::cout << sout << std::endl;

    std::cout << "What is: nonsense" << std::endl;

    std::cout << myJ["nonsense"] == NULL << std::endl;

    std::cout << myJ["nonsense"] << std::endl;



    // jsons j_umap(whoamap);

    // std::cout << typeid(jm).name() << std::endl; 

    return 0;
}