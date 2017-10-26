#include "planet.h"
#include "solver.h"
#include <cmath>

Planet::Planet(double mass_, double x, double y, double vx, double vy, std::string name_){

    position = vec({x,y});
    velocity = vec({vx,vy});
    //a_other = vec({0, 0});
    acceleration = vec({0,0});
    mass = mass_;
    name = name_;
    dimension = position.size();
    pi = M_PI;
    fourpi2 = 4*pi*pi;
    kinEnergy = 0.5*mass*dot(velocity, velocity);
    potEnergy = -fourpi2*3e-6;
    distance = 0;
    absposition_start = dot(position,position);
    angularMomentum = mass*absposition_start* pow(dot(velocity,velocity), 0.5);
    min_x_after = 1.0;
    min_y_after = 1.0;
    minimum = 1.0;
}

double Planet::relativeDistance(Planet otherPlanet){
    // Calculates the distance between this planet and "otherPlanet"
    double sum = 0;
    for(int i=0;i<dimension;i++){
        sum += (position[i]-otherPlanet.position[i])*(position[i]-otherPlanet.position[i]);
    }
    return distance = sqrt(sum);
}


mat Planet::accelerationFromOther(Planet otherPlanet, double &distance, double beta){

    // Defining the relativistic part:
    double l = abs(position[0]*velocity[1]-velocity[0]*position[1]);
    double c = 63239.7263; // AU per year
    double relativistic = (1+(3*l*l/(distance*distance*c*c)));
    //double relativistic = 1.0;
    // Calculating the acceleration contribution from "otherPlanet"
    return ((-fourpi2*otherPlanet.mass)/pow(distance,beta+1))*(position-otherPlanet.position)*relativistic;

}

void Planet::kinEnergyUpdate(){
    // Calculating the kinetic energy for updated velocity
    kinEnergy = 0.5*mass*dot(velocity, velocity);
}

double Planet::FromOtherPotEnergy(Planet& other, double &distance){
    // Calculating the potential energy contribution from "otherPlanet"
    return -fourpi2*mass*other.mass / distance;
    //unit: Joule/mass_sun

}
