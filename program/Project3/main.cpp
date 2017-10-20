#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
//using namespace arma;

int main(){
    float speed_years = 1./(365);

    double m_sun = 2.0*1e30;

    Planet earth(6*1e24/m_sun,   1.364125053119183       ,  1.661119876735337e-1   ,  3.841445104127103e-03*speed_years ,   4.372876237736002e-02*speed_years  , "earth"); // (mass,x,y,vx,vy)

    Planet sun(1.0,     0,    0 ,0,0   , "sun");

    //Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");

    //Planet jupiter(1./1000,-4.25662680436108, -2.868197076870578,   1.118281447057823e-2*speed_years,  2.080737970677697e-02*speed_years ,  "jupiter"); // (mass,x,y,vx,vy)
    int years = 100;

    vec pos_e = {(1.364125053119183       ,  1.661119876735337e-1)};
    cout << dot(pos_e,pos_e)<<endl;
cout << sqrt(3.841445104127103e-03*speed_years*3.841445104127103e-03*speed_years +   4.372876237736002e-02*speed_years* 4.372876237736002e-02*speed_years)<<"   " << 2*M_PI<<endl;
    clock_t start_2, finish_2;
    start_2 = clock();

    Solver verlet("verlet", true, years);

    verlet.add(earth);
    verlet.add(sun);
    verlet.pretests();
    verlet.algorithm();
    finish_2 = clock();
    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));


    cout << time_verlet<<endl;




    clock_t start_, finish_;
    start_ = clock();
    //test.pretests();

    Solver euler("euler", false, years);


    //Looks like euler method conserves energy. KinEn varies a lot, potential not.!!! How test for energy?
    // Should the kinetic and pot energy be conserved independently? (3c)
    euler.add(earth);
    euler.add(sun);
    euler.algorithm();
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

    cout<< time_euler<<endl;

/*

    Solver threebody("3body", true, years);

    threebody.add(earth);
    threebody.add(sun);
    threebody.add(jupiter);

    threebody.pretests();
    threebody.algorithm();

*/
    return 0;
}
