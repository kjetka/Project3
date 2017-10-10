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

    testing.add(earth);
    testing.add(sun);
    testing.alt();

    return 0;
}
