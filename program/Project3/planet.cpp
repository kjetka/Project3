#include "planet.h"
#include "solver.h"
#include <cmath>

Planet::Planet(double mass_, double x, double y, double vx, double vy){

    position = vec({x,y});
    velocity = vec({vx,vy});
    aks = vec({0,0});
    mass = mass_;
    //dimension = position.size();

    pi = M_PI;
    fourpi2 = 4*pi*pi;

}

void Planet::relativeDistance(mat &position, int dimension, double &distance){
    double sum = 0;
    for(int i=0;i<dimension;i++){
        sum += position[i]*position[i];
    }
    distance = sqrt(sum);
}




void Planet::acceleration(mat& position, mat& aks, int dimension, double absDistance){
    for(int i=0;i<dimension; i++){
    aks(i) = (-fourpi2/pow(absDistance,3))*position(i);}
}


//Question: Make a force function - use to get acceleration.
