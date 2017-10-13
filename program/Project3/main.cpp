#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
//using namespace arma;

void finding_initial_velocity();

int main(){
    //Planet planet;

    //Planet earth(0.000010, 1.0, 0.000, 0.0, M_PI*2, "earth"); // (mass,x,y,vx,vy)
    //Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");
    Solver testing("sun_earth");

//    testing.add(earth);
//    testing.add(sun);
//    testing.pretests();
//    testing.algorithm();

    finding_initial_velocity();

    return 0;
}

 void finding_initial_velocity(){
    double start_v = 2*M_PI;
    double end_v = 2*M_PI*sqrt(2)+0.01;

    double v = start_v;

    double dv = (end_v - start_v)/15.0;

    while (v < end_v){
        Planet earth(0.000010, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "sun_earth_initial_velocity_" + to_string(v);
        Solver test_initial(type);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm();

        v += dv;
    }
}
