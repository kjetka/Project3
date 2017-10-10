#include "planet.h"
#include "solver.h"
#include <cmath>

Planet::Planet(double mass_, double x, double y, double vx, double vy, std::string name_){

    position = vec({x,y});
    velocity = vec({vx,vy});
    a = vec({0, 0});
    aks = vec({0,0});
    mass = mass_;
    name = name_;

    //dimension = position.size();

    pi = M_PI;
    fourpi2 = 4*pi*pi;

}

void Planet::relativeDistance(Planet otherPlanet, double &distance){
    double sum = 0;
    for(unsigned int i=0;i<position.size() ;i++){
        sum += position[i]*otherPlanet.position[i];
    }
    distance = sqrt(sum);
}


mat Planet::acceleration(Planet otherPlanet){
    double absDistance;
    relativeDistance(otherPlanet, absDistance);

    for(unsigned int i=0;i<position.size(); i++){
        a(i) = (-fourpi2*otherPlanet.mass/pow(absDistance,3))*(position(i)-otherPlanet.position[i]);}
        return a;
}


//Question: Make a force function - use to get acceleration.
