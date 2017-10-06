#include "solver.h"
#include "planet.h"

Solver::Solver(){

    pi = acos(-1.0);
    fourpi2 = 4*pi*pi;

    timeLimit = 1.0;
    numberofsteps = 10000;
    time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;
}

void Solver::velocity(double &vx, double &vy, double ax, double ay){
    vx = vx + dtdiv2*ax;
    vy = vy + dtdiv2*ay;
}

void Solver::velocityVerlet(double &x, double &y, double &vx, double &vy){

    double x = 1.0;
    double y = 0.0;
    double vx = 0;
    double vy = 2*pi;
    double ax, ay, r;

    double ax_new, ay_new, vx_half, vy_half;

    relativeDistance(x,y,r);
    accelaration(x,y,r,ax,ay);

    while(time<=timeLimit){
        velocity(vx, vy, ax, ay);

        x = x + dt*vx;
        y = y + dt*vy;

        relativeDistance(x,y,r);

        acceleration(x, y, r, ax, ay);

        velocity(vx, vy, ax, ay;)

        time = time + dt;
}
