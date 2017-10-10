#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
//using namespace arma;

int main(){
    //Planet planet;
    Planet earth(0.00010, 1.0, 0.000, 0.0, 1.0); // Earth: (mass,x,y,vx,vy)
    Planet sun(1, 0,0,0,0);
    Solver testing;

<<<<<<< Updated upstream
    testing.add(earth);
    testing.add(sun);
    testing.alt();
=======
    Solver* solv;

    double x, y, vx, vy;

    solv = new Solver();
    solv->velocityVerlet(x, y, vx, vy);


  //  solv->
/*
    double timeLimit = 1.0;
    int numberofsteps = 10000;
    double time = 0;
    double dt = timeLimit/numberofsteps;

    double pi = acos(-1.0);

    double x = 1.0;
    double y = 0.0;
    double vx = 0;
    double vy = 2*pi;
    double ax, ay, r;


    double fourpi2 = 4*pi*pi;

    // Euler-Cromer method:
    while(time<=timeLimit){
        r = sqrt(pow(x,2) + pow(y,2));

        ax = (-fourpi2/pow(r,3))*x;
        ay = (-fourpi2/pow(r,3))*y;

        vx = vx + dt*ax;
        vy = vy + dt*ay;

        x = x + dt*vx;
        y = y + dt*vy;

        time = time + dt;
    }

    cout << "Euler:" << endl;
    cout << "Position: " << "(" << x << " , " << y << " ) " << endl;
    cout << "Velocity: " << "(" << vx << " , " << vy << " ) " << endl;

    x = 1.0;
    y = 0.0;
    vx = 0;
    vy = 2*pi;

    // Velocity Verlet:

    double dtdiv2 = dt/2;

    double ax_new, ay_new, vx_half, vy_half;

    r = sqrt(pow(x,2) + pow(y,2));
    ax = (-fourpi2/pow(r,3))*x;
    ay = (-fourpi2/pow(r,3))*y;

    while(time<=timeLimit){
        vx_half = vx + dtdiv2*ax;
        vy_half = vy + dtdiv2*ay;

        x = x + dt*vx_half;
        y = y + dt*vy_half;

        r = sqrt(pow(x,2) + pow(y,2));

        ax = (-fourpi2/pow(r,3))*x;
        ay = (-fourpi2/pow(r,3))*y;

        vx = vx_half + dtdiv2*ax;
        vy = vy_half + dtdiv2*ay;

        time = time + dt;
    }
*/
std::cout << "Velocity Verlet:"<<std::endl;
std::cout << "Position: " << "(" << x << " , " << y << " ) " << std::endl;
std::cout << "Velocity: " << "(" << vx << " , " << vy << " ) " << std::endl;
>>>>>>> Stashed changes

    return 0;
}
