#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
using namespace arma;

void finding_initial_velocity_escape();
void finding_initial_velocity_circular();
void checking_gravitation(int years, Planet earth, Planet sun);

int main(){
    float speed_years = (365.);
    int years = 3;


    Planet earth(0.000030, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
//    Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");
//    Solver testing("sun_earth");

    //    finding_initial_velocity_escape(years);
    //    finding_intial_velocity_circular(years);


    double m_sun = 2.0*1e30;
    //Planet sun(1.0,     2.208054875983525E-03, 5.746280454272564E-03, -5.245593715780954E-06*speed_years ,  5.482120330588081E-06*speed_years   , "sun");
//    Planet sun(1.0,     2.208054875983525E-03, 5.746280454272564E-03, 0 , 0   , "sun");

//    Planet earth(6*1e24/m_sun,    8.930309961463524E-01, 4.508411860073833E-01   ,-7.978069853256020E-03*speed_years, 1.533806773162681E-02 *speed_years   , "earth"); // (mass,x,y,vx,vy)

//    checking_gravitation(years, earth, sun);

    /*

    //Planet mars(0.000002, 0.0, 0.1, 0.0, M_PI, "mars");

    Planet jupiter(1./1000, -4.572777635194016E+00, -2.939093897020645E+00,  3.991864886961527E-03*speed_years, -5.989606308601243E-03*speed_years   ,  "jupiter"); // (mass,x,y,vx,vy)


    clock_t start_2, finish_2;
    start_2 = clock();
*/
    Solver verlet("verlet", true, years);

    verlet.add(earth);
    verlet.add(sun);
    verlet.pretests();
//    verlet.algorithm(2);
//    finish_2 = clock();
    verlet.check_convergence();
    /*
    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));



    cout << time_verlet<<endl;
*/
    /*
    clock_t start_, finish_;
    start_ = clock();
    //test.pretests();

    Solver euler("euler", false, years);


    //Looks like euler method conserves energy. KinEn varies a lot, potential not.!!! How test for energy?
    // Should the kinetic and pot energy be conserved independently? (3c)
    euler.add(earth);
    euler.add(sun);
    euler.algorithm(2);
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

//    euler.check_convergence(earth);

    cout<< time_euler<<endl;



    Solver threebody("3body", true, years);

    threebody.add(earth);
    threebody.add(sun);
    threebody.add(jupiter);

    threebody.pretests();
    threebody.algorithm();
*/

    return 0;
}

void finding_initial_velocity_circular(int years){
    double start_v = 1.9*M_PI;
    double end_v = 2.1*M_PI;

    double v = start_v;

    double dv = (end_v - start_v)/7.0;

    while (v <= end_v){
        Planet earth(0.000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, years);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(2);
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
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, years);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(2);

        v += dv;
    }
}

void checking_gravitation(int years, Planet earth, Planet sun){
    double beta = 2;
    while (beta <= 3){
        string type = "beta-is-" + to_string(beta);
        Solver gravitation(type, true, years);

        gravitation.add(earth);
        gravitation.add(sun);
        gravitation.algorithm(beta);

        beta += 0.1;
    }
}
