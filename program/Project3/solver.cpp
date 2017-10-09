#include "solver.h"
#include "planet.h"


Solver::Solver(){

    fourpi2 = 4*M_PI*M_PI;

    timeLimit = 1.0;
    numberofsteps = 10000;
    time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    m_planets.reserve(20);

}
void Solver::velocity_funk(mat v, mat a){
    // problem with mat and vec? Make this inliner?
   v = v + dt_half*a;
    //vx = vx + dt_half*ax;
    //vy = vy + dt_half*ay;
}

void Solver::velocityVerlet(double &x, double &y, double &vx, double &vy){
    x = 1.0;
    y = 0.0;
    vx = 0;
    vy = 2*M_PI;

    double ax, ay, r;

    for (unsigned int i=0; i < m_planets.size(); i++) {
        Planet* planet_i = m_planets.at(i); // m_planets[i];
        double ax,ay;
        planet_i->acceleration(mat a);
    }

    p.relativeDistance(x,y,r);
    p.accelaration(x,y,r,ax,ay);

    while(time<=timeLimit){
        velocity(vx, vy, ax, ay);

        x = x + dt*vx;
        y = y + dt*vy;

        p.relativeDistance(x,y,r);

        p.acceleration(x, y, r, ax, ay);

        velocity(vx, vy, ax, ay);

        time = time + dt;

    }
}
void Solver::addPlanet(Planet *p) { //Inliner?
    m_planets.push_back(p);
}

void Solver::writePosition(ofstream &output, mat r, mat v, int dimension, double time){
    for(int i=0;i<dimension; i++){output << "\t" << r[i];}
    for(int i=0;i<dimension; i++){output << "\t" << v[i];}
    output << endl;

}
