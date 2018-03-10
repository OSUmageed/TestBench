#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

// UTILITIES PATH

#include "json/json.h"


struct boy
{
    int age, ht;
    std::string name;
    void init(int a, int b, std::string c)
    {
        age = a;
        ht = b;
        name = c;
    };
    void printme()
    {
        std::cout << name << " " << ht << " " << age << std::endl;
    };
};


class Equation
{

private:

    int boi;
	boy *chosenEquation = new boy;


public:
    Equation(int a, int b, std::string c)
    {
        boi = a;
        chosenEquation->init(a, b, c);
    };
    void printit()
    {
        chosenEquation->printme();
    };
};

int main()
{
    Equation eq(5, 81, "Matt");
    eq.printit();


    return 0;
}