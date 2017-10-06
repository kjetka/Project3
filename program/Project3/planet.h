#ifndef PLANET_H
#define PLANET_H
#include <iostream>
#include <armadillo>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "solver.h"

class Planet{
    private:
        double pi;
        double fourpi2;
    public:
        Planet();
        void relativeDistance(double x, double y, double &r);
        void acceleration(double x, double y, double r, double &ax, double &ay);

};

#endif // PLANET_H
