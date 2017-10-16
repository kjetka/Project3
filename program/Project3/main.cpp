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

    clock_t start_, finish_;
    start_ = clock();
    //test.pretests();

    Solver euler("sun_earth", true, 1.0);

    euler.add(earth);
    euler.add(sun);
    euler.algorithm();
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

    /*

    clock_t start_2, finish_2;
    start_2 = clock();

    Solver verlet("sun_earth", true, 1);

    verlet.add(earth);
    verlet.add(sun);
    verlet.pretests();
    verlet.algorithm();
    finish_2 = clock();
    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));


    cout<< time_euler<<endl;
    cout << time_verlet<<endl;

    */
    return 0;
}
