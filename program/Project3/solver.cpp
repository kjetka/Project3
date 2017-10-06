#include "solver.h"

Solver::Solver()
{
    m_pi = acos(-1.0);
}


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

void Solver::writePosition(ofstream &output, mat r, mat v, int dimension, double time){
    for(int i=0;i<dimension; i++){output << "\t" << r[i];}
    for(int i=0;i<dimension; i++){output << "\t" << v[i];}
    output << endl;

}
