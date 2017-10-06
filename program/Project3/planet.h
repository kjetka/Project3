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

using namespace arma;

class Planet{
    //friend class Solver;

    private:
        double m_pi;
        double m_fourpi2;



        int dimension = 2;


    public:
        mat position;
        mat velocity;
        mat aks;
        Planet();
        Planet(double mass, double x, double y, double vx, double vy);
        //~Planet () {}                        // destructor

        void relativeDistance(mat &position, int dimension, double &distance);
        void acceleration(mat& aks, double absDistance, int dimension, mat& position);



};

#endif // PLANET_H
