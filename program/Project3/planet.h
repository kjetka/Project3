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
    friend class Solver;

    private:
        double m_pi;
        double m_fourpi2;

        mat position;
        mat velocity ;
        mat acceleration;

        int dimension;


    public:
        Planet(double mass, double &x, double &y, double &vx, double &vy);
        void relativeDistance(double *r, int dimension);
        void acceleration(double &ax, double &ay);

};

#endif // PLANET_H
