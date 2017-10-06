#ifndef PLANET_H
#define PLANET_H
#include <iostream>
//#include "non_interact.h"
#include <armadillo>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>

class Planet
{
public:
    Planet();
    void relativeDistance(double x, double y, double &r);
    void acceleration(double x, double y, double r, double &ax, double &ay);

};

#endif // PLANET_H
