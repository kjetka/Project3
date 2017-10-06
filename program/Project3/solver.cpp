#include "solver.h"
#include "planet.h"


Solver::Solver(){

    m_pi = acos(-1.0);
    fourpi2 = 4*m_pi*m_pi;

    timeLimit = 1.0;
    numberofsteps = 10000;
    time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    m_planets.reserve(20);

void Solver::euler(double x, double y, double vx, double vy, double timeLimit, double integrationPoints){
    // Euler-Cromer method:
    double r, ax,ay;

    double fourpi2 = 4*m_pi*m_pi;

    double time = 0;
    double dt = timeLimit/integrationPoints;
    ofstream outfile("../test.txt");

    while(time<=timeLimit){
        r = sqrt(pow(x,2) + pow(y,2));
        ax = (-fourpi2/pow(r,3))*x;
        ay = (-fourpi2/pow(r,3))*y;
        vx = vx + dt*ax;
        vy = vy + dt*ay;
        x = x + dt*vx;
        y = y + dt*vy;
        writePosition(outfile, vec({x,y}), vec({vx,vy}), 3, time);

        time = time + dt;
    }

    cout << "Euler:" << endl;
    cout << "Position: " << "(" << x << " , " << y << " ) " << endl;
    cout << "Velocity: " << "(" << vx << " , " << vy << " ) " << endl;


}

void Solver::velocity(double &vx, double &vy, double ax, double ay){
    vx = vx + dt_half*ax;
    vy = vy + dt_half*ay;
}

void Solver::velocityVerlet(double &x, double &y, double &vx, double &vy){
    x = 1.0;
    y = 0.0;
    vx = 0;
    vy = 2*m_pi;

    double ax, ay, r;

    for (unsigned int i=0; i < m_planets.size(); i++) {
        Planet* planet_i = m_planets.at(i); // m_planets[i];
        double ax,ay;
        planet_i->acceleration(ax,ay);
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
void Solver::addPlanet(Planet *p) {
    m_planets.push_back(p);
}

void Solver::writePosition(ofstream &output, mat r, mat v, int dimension, double time){
    for(int i=0;i<dimension; i++){output << "\t" << r[i];}
    for(int i=0;i<dimension; i++){output << "\t" << v[i];}
    output << endl;

}
