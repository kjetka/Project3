#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
//using namespace arma;

int main(){
    //Planet planet;
    Planet earth(0.0000030, 1.0, 0.000, 0.0, M_PI*2, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");
    Solver testing("sun_earth");

    testing.add(earth);
    testing.add(sun);
    testing.pretests();
    testing.algorithm();

    return 0;
}
