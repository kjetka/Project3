#include "planet.h"
#include "solver.h"

Planet::Planet(double mass, double &x, double &y, double &vx, double &vy){

    position = vec({x,y});
    velocity = vec({vx,vy});
    acceleration = vec({0,0});
    dimension = position.size();

    m_pi = acos(-1.0);
    m_fourpi2 = 4*m_pi*m_pi;

}

void Planet::relativeDistance(int dimension, double &position, double &distance){
    double sum = 0;

    for(int i=0;i<dimension;i++){
        sum += position[i]*position[i];
    }
    distance = sqrt(sum);
}

void Planet::acceleration(double &ax, double &ay){
    ax = (-m_fourpi2/pow(r,3))*x;
    ay = (-m_fourpi2/pow(r,3))*y;
}
