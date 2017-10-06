#include "planet.h"
#include "solver.h"

Planet::Planet(double mass, double x, double y, double vx, double vy){

    position = vec({x,y});
    velocity = vec({vx,vy});
    aks = vec({0,0});
    //dimension = position.size();

    m_pi = acos(-1.0);
    m_fourpi2 = 4*m_pi*m_pi;

}

void Planet::relativeDistance(mat &position, int dimension, double &distance){
    double sum = 0;
    for(int i=0;i<dimension;i++){
        sum += position[i]*position[i];
    }
    distance = sqrt(sum);
}




void Planet::acceleration(mat& aks, double absDistance, int dimension, mat& position){
    for(int i=0;i<dimension; i++){
    aks(i) = (-m_fourpi2/pow(absDistance,3))*position(i);}
}

