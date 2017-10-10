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
        mat a;
        double mass;
        std::string name;


        int dimension = 2;


    public:
        Planet(double mass_, double x, double y, double vx, double vy, std::string name_);
        //~Planet () {}                        // destructor

        void relativeDistance(Planet otherPlanet, double &distance);
        mat acceleration(Planet otherPlanet);



};

#endif // PLANET_H
