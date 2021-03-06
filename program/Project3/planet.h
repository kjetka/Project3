#ifndef PLANET_H
#define PLANET_H
#include <iostream>

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
        double angularMomentum;
        double absposition_start;
        double min_x_Perihelion;
        double min_y_Perihelion;
        double minPerihelion;
        double sunDistance;



    public:

        Planet(double mass_, double x, double y, double vx, double vy, std::string name_);

        double relativeDistance(Planet& otherPlanet);
        mat accelerationFromOther(Planet& otherPlanet, double &distance, double beta);

        void kineticEnergyUpdate();
        double fromOtherPotentialEnergy(Planet & other,double& distance);
       void angularMomentumUpdate();

};

#endif // PLANET_H
