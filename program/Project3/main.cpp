#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
using namespace arma;

void finding_initial_velocity_escape();
void finding_initial_velocity_cirkular();

int main(){
    float speed_years = 1./(365);
    int years = 100;

/*
    Planet earth(0.000030, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");
    Solver testing("sun_earth");
*/
//    finding_initial_velocity_escape(years);
//    finding_intial_velocity_circular(years);


    double m_sun = 2.0*1e30;

    Planet earth(6*1e24/m_sun,   1.364125053119183       ,  1.661119876735337e-1   ,  3.841445104127103e-03*speed_years ,   4.372876237736002e-02*speed_years  , "earth"); // (mass,x,y,vx,vy)

    Planet sun(1.0,     0,    0 ,0,0   , "sun");

    //Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");

    //Planet jupiter(1./1000,-4.25662680436108, -2.868197076870578,   1.118281447057823e-2*speed_years,  2.080737970677697e-02*speed_years ,  "jupiter"); // (mass,x,y,vx,vy)



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

void finding_initial_velocity_cirkular(int years){
   double start_v = 1.9*M_PI;
   double end_v = 2.1*M_PI;

   double v = start_v;

   double dv = (end_v - start_v)/7.0;

   while (v <= end_v){
       Planet earth(0.000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
       Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
       string type = "sun_earth_initial_velocity_" + to_string(v);
       Solver test_initial("verlet", true, years);

       test_initial.add(earth);
       test_initial.add(sun);
       test_initial.algorithm();
       v += dv;
   }
}

void finding_initial_velocity_escape(int years ){
    double start_v = 0.97*2*sqrt(2)*M_PI;
    double end_v = 2*M_PI*sqrt(2);

    double v = start_v;

    double dv = (end_v - start_v)/5.0;

    while (v <= end_v){
        Planet earth(0.0000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "sun_earth_initial_velocity_" + to_string(v);
        Solver test_initial("v_test", true, years);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm();

        v += dv;
    }
}
