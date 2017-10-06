#include "planet.h"
#include "solver.h"

Planet::Planet(){

}

void Planet::relativeDistance(double x, double y, double &r){
    r = sqrt(pow(x,2)+pow(y,2));
}

void Planet::acceleration(double x, double y, double r, double &ax, double &ay){
    ax = (-fourpi2/pow(r,3))*x;
    ay = (-fourpi2/pow(r,3))*y;
}
