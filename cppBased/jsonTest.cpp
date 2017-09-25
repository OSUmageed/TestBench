#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <typeinfo>
#include "json/json.h"
#include <unordered_map>

typedef Json::Value jsons;

using namespace std;

// Test json
int main(int argc, char *argv[])
{
    ifstream imzep("test.json", ifstream::in);
    jsons myJ;
    imzep >> myJ;
    cout << myJ << endl;

    int dt = myJ["dt"].asInt(); 
    cout << typeid(myJ["ImFalse"]).name() << endl;
    imzep.close();

    // vector<int> ivec = myJ["arr"].asArray();
    // vector<int> sm(ivec.size());

    // partial_sum(ivec.begin(), ivec.end(), sm.begin());

    cout << "New Json" << endl;
    myJ["Bean"] = 40;
    myJ["B"]["CD"] = 90;
    myJ["FF"]["CD"]["yu"] = 850.0;
    myJ["B"]["DF"] = 100050.9;

    cout << myJ << endl;
    
    bool wha = myJ["mg"].asString() == "level";
    if (&myJ["Imfalse"]) cout << "Yeah it's a nullptr " << bool(&myJ["Bean"]) << endl;

    cout << dt*5 << endl;
    // cout << sm[0] << " " << sm.back() << endl;
    cout << wha << endl;

    // TestMap
    unordered_map<int, double> whoamap;

    cout << whoamap.size() << " " << whoamap.max_size() << endl;
    double k2;

    // cout << double
    for (int k=2; k<10; k++)
    {
        k2 = k*0.02635;
        cout << k2 << endl;
        whoamap.insert(make_pair(k, k2));
    }

    cout << whoamap.size() << " " << whoamap.max_size() << endl;

    string ext = ".json";
    string myrank = to_string(k2);
    string sout = argv[2];
    sout.append(myrank);
    sout.append(ext); 

    cout << k2 << endl;

    string boom = "Boom";

    bool mal = boom.compare(argv[1]);

    bool m2 = -1;

    cout << m2 << " " << mal << endl;

    cout << sout << endl;

    cout << "What is: nonsense" << endl;
    int bl = myJ["nonsense"] == NULL;

    cout << bl << endl;

    cout << myJ["nonsense"] << endl;

    // jsons j_umap(whoamap);

    // cout << typeid(jm).name() << endl; 

    return 0;
}