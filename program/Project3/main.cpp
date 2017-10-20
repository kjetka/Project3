#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
//using namespace arma;

void finding_initial_velocity_escape();
void finding_initial_velocity_cirkular();

int main(){
//    Planet planet;
/*
    Planet earth(0.000030, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");
    Solver testing("sun_earth");

    testing.add(earth);
    testing.add(sun);
    testing.pretests();
    testing.algorithm();
*/
    finding_initial_velocity_escape();
//    finding_intial_velocity_circular();

    return 0;
}

void finding_initial_velocity_cirkular(){
   double start_v = 1.9*M_PI;
   double end_v = 2.1*M_PI;

   double v = start_v;

   double dv = (end_v - start_v)/7.0;

   while (v <= end_v){
       Planet earth(0.000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
       Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
       string type = "sun_earth_initial_velocity_" + to_string(v);
       Solver test_initial(type);

       test_initial.add(earth);
       test_initial.add(sun);
       test_initial.algorithm();
       v += dv;
   }
}

void finding_initial_velocity_escape(){
    double start_v = 0.97*2*sqrt(2)*M_PI;
    double end_v = 2*M_PI*sqrt(2);

    double v = start_v;

    double dv = (end_v - start_v)/5.0;

    while (v <= end_v){
        Planet earth(0.0000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "sun_earth_initial_velocity_" + to_string(v);
        Solver test_initial(type);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm();

        v += dv;
    }
}
