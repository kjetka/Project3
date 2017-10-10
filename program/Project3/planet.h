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
//#include "solver.h"
#include <new>
#include <armadillo>

using namespace arma;

class Planet{
    friend class Solver;

    private:
        double pi;
        double fourpi2;
        mat position;
        mat velocity;
        mat aks;
        double mass;


        int dimension = 2;


    public:

        Planet();
        Planet(double mass, double x, double y, double vx, double vy);
        //~Planet () {}                        // destructor

        void relativeDistance(mat &position, int dimension, double &distance);
        void acceleration(mat& position, mat& aks, int dimension, double absDistance );



};

#endif // PLANET_H
