#include <iostream>
//#include "non_interact.h"
#include <armadillo>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
using namespace arma;

int main(){




//    class planet;

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
    ax, ay, r;

    // Velocity Verlet:

    double dt2 = pow(dt,2)/2;
    double dtdiv2 = dt/2;

    double ax_new, ay_new;

    while(time<=timeLimit){
        r = sqrt(pow(x,2) + pow(y,2));

        ax_new = (-fourpi2/pow(r,3))*x;
        ay_new = (-fourpi2/pow(r,3))*y;

        x = x + dt*vx + dt2*ax;
        y = y + dt*vy + dt2*ay;

        vx = vx + dtdiv2*(ax_new + ax);
        vy = vy + dtdiv2*(ay_new + ay);

        ax = ax_new;
        ay = ay_new;

        time = time + dt;
    }
cout << "Velocity Verlet:"<<endl;
cout << "Position: " << "(" << x << " , " << y << " ) " << endl;
cout << "Velocity: " << "(" << vx << " , " << vy << " ) " << endl;

}

