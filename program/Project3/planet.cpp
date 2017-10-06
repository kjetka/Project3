#include "planet.h"

Planet::Planet(){
    pi = acos(-1.0);
    fourpi2 = 4*pi*pi;
}

void Planet::relativeDistance(double x, double y, double &r){
    r = sqrt(pow(x,2)+pow(y,2));
}

void Planet::acceleration(double x, double y, double r, double &ax, double &ay){
    ax = (-fourpi2/pow(r,3))*x;
    ay = (-fourpi2/pow(r,3))*y;
}
