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
    dimension = position.size();
    pi = M_PI;
    fourpi2 = 4*pi*pi;

}

void Planet::relativeDistance(Planet otherPlanet, double &distance){
    double sum = 0;
    for(int i=0;i<dimension;i++){
        sum += (position[i]-otherPlanet.position[i])*(position[i]-otherPlanet.position[i]);
    }
    distance = sqrt(sum);
}


mat Planet::acceleration(Planet otherPlanet){
    double absDistance=0; //Question: fjerne? add in function header?
    // calculates the distance from this planet to the other planet
    relativeDistance(otherPlanet, absDistance);
    // Calculates the acceleration form the gravitational force between the planets

    a =((-fourpi2*otherPlanet.mass)/pow(absDistance,3))*(position-otherPlanet.position);
   /* for(unsigned int i=0;i<position.size(); i++){
        a(i) = ((-fourpi2*otherPlanet.mass)/pow(absDistance,3))*(position(i)-otherPlanet.position[i]);
    }*/
    return a;
}
