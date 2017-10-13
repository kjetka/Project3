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
using namespace std;

class Planet{
    friend class Solver;

    private:
        double pi;
        double fourpi2;
        mat position;
        mat velocity;
        mat acceleration;
        mat a_other;
        double mass;
        string name;
        double kinEnergy;
        double potEnergy;
        double distance;
        int dimension = 2;


    public:
        Planet(double mass_, double x, double y, double vx, double vy, std::string name_);
        //~Planet () {}                        // destructor

        double relativeDistance(Planet otherPlanet);
        mat accelerationFromOther(Planet otherPlanet, double &distance);

        void energyUpdate();
        double FromOtherPotEnergy(Planet & other,double& distance);

};

#endif // PLANET_H
