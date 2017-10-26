#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
using namespace arma;

void finding_initial_velocity_escape();
void finding_initial_velocity_circular();
void checking_gravitation(int years, Planet earth, Planet sun);
void reading_init_values(string filename, double& x, double& y, double& z, double& vx, double& vy, double& vz);
int main(){
    string planetname;
    //cout << "check if the initial potential energy is correct for many bodies!!!"<<endl;
    int years = 100;
    double m_sun = 2.0*1e30;

// Original initial values ---------------------------------------------------
//    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mercury(3.3e23/m_sun,0.3075, 0, 0, 12.44,"mercury");

// Different functions -------------------------------------------------------

//    checking_gravitation(years, earth, sun);
//    finding_initial_velocity_escape(years);
//    finding_intial_velocity_circular(years);

// ---------------------------------------------------------------------------
/*
    double x,y,z,vx,vy,vz;

    planetname ="earth";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet earth(3e-6, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="sun";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet sun(1.0, x,y,vx,vy, planetname);

    checking_gravitation(years, earth, sun);

    planetname ="mars";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet mars(6.6e23/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)


    planetname ="uranus";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet uranus(8.8e25/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="jupiter";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet jupiter(1.9e27/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)


    planetname ="mercury";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet mercury(3.3e23/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="neptun";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet neptun(1.03e26/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="pluto";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet pluto(1.31e22/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="saturn";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet saturn(5.5e26/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="venus";
    reading_init_values(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet venus(4.9e24/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)


*/

// ----------------------------------------------------------------------------


// Check energy convergence ---------------------------------------------------
    /*
    Solver convergence("converg", true, 10);
    convergence.add(earth);
    convergence.add(sun);
    double convergence_crit = 3e-6;
    double dt = 1;
    convergence.check_convergence(convergence_crit, dt);
    cout <<dt;
*/

// Velocity Verlet-------------------------------------------------------------
    clock_t start_2, finish_2;
    start_2 = clock();

    Solver verlet("verlet", true, years);

    //verlet.add(earth);
    verlet.add(sun);
    verlet.add(mercury);
    verlet.pretests();
    verlet.algorithm(true, 2);
    finish_2 = clock();
//    verlet.check_convergence();

    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));
    cout << "CPU time: " << time_verlet<<endl;

// ----------------------------------------------------------------------------

// Euler's method -------------------------------------------------------------
    /*
    clock_t start_, finish_;
    start_ = clock();
    //test.pretests();

    Solver euler("euler", false, years);

    //Looks like euler method conserves energy. KinEn varies a lot, potential not.!!! How test for energy?
    // Should the kinetic and pot energy be conserved independently? (3c)
    euler.add(earth);
    euler.add(sun);
    euler.algorithm(true, 2);
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

//    euler.check_convergence(earth);

    cout<< time_euler<<endl;
*/
// -------------------------------------------------------------------------------


// Three-body --------------------------------------------------------------------
/*
    Solver threebody("3body", true, years);

    mat massJupiter = vec({1./1e3, 10./1e3, 1.});
    string filename[] = {"3body_m1e0", "3body_m1e1", "3body_m1e3"};
    for (int i =0; i<3; i++){
        Solver threebody(filename[i], true, years);

    threebody.pretests();
    threebody.algorithm(true, 2);
*/
// --------------------------------------------------------------------------------


    return 0;
}

void reading_init_values(string filename, double &x, double &y , double &z, double &vx, double &vy, double &vz){
    double speed_years = (365.);

    string fileloc = "../Initial_cond/"+filename + "_.txt";
    ifstream inf(fileloc);
    string line;

    vector<std::string> myLines;
    if (!inf){
        // Print an error and exit
        cout << "Uh oh, could not open that file for reading!" << endl;
        exit(1);
    }
    while (std::getline(inf, line))
    {
       myLines.push_back(line);
    }

    x = stod(myLines[0]);
    y = stod(myLines[1]);
    z = stod(myLines[2]);
    vx = stod(myLines[3])*speed_years;
    vy = stod(myLines[4])*speed_years;
    vz = stod(myLines[5])*speed_years;
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
        test_initial.algorithm(true, 2);
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
        test_initial.algorithm(true, 2);

        v += dv;
    }
}

void checking_gravitation(int years, Planet earth, Planet sun){
    double beta = 2.3;
    while (beta <= 3.2){
        string type = "beta-is-" + to_string(beta);
        Solver gravitation(type, true, 3);

        gravitation.add(earth);
        gravitation.add(sun);
        gravitation.algorithm(true, beta);

        beta += 0.3;
    }
}
