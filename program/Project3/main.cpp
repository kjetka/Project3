#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
using namespace arma;

void findingInitialEscapeVelocity(int years, bool relativistic);
void findingInitialCircularVelocity(int years,bool relativistic);
void checkingGravitation(int years, Planet earth, Planet sun, double stepsPerYear);
void readingInitialValues(string filename, double& x, double& y, double& z, double& vx, double& vy, double& vz);
int main(){

    double m_sun = 2.0*1e30;
    string planetname;
    int years = 10;
    double stepsPerYear = 1000;
    bool relativistic = false;
// First choose how you want to initialize the planets, and which plantes you want:

// Bodycentric coordinates --------------------------------------------------

    double x,y,z,vx,vy,vz;

    planetname ="earth";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet earth(3e-6, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="sun";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet sun(1.0, x,y,vx,vy, planetname);

    planetname ="mars";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet mars(6.6e23/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="uranus";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet uranus(8.8e25/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="jupiter";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet jupiter(1.9e27/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="mercury";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet mercury(3.3e23/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="neptun";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet neptun(1.03e26/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="pluto";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet pluto(1.31e22/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="saturn";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet saturn(5.5e26/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

    planetname ="venus";
    readingInitialValues(planetname, x,  y,  z,  vx,  vy,  vz);
    Planet venus(4.9e24/m_sun, x, y, vx,vy, planetname); // (mass,x,y,vx,vy)

// ----------------------------------------------------------------------------


//Sun as origin --------------------------------------------------------------
    Planet earth_00(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun_00(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mercury_00(3.3e23/m_sun,0.3075, 0, 0, 12.44,"mercury");

// ----------------------------------------------------------------------------




// Euler's method -------------------------------------------------------------
/*
    clock_t start_, finish_;
    start_ = clock();

    Solver euler("euler", false,relativistic,  years, stepsPerYear);

    euler.add(sun);
    euler.add(earth);
    euler.algorithm(true, 2, false); // true -> print to file // false -> don't print
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

    cout<< "CPU time: " <<time_euler<<endl;
*/
// -----------------------------------------------------------------------------


// Velocity Verlet-------------------------------------------------------------

  /*  clock_t start_2, finish_2;
    start_2 = clock();
    stepsPerYear = 1000;
    //for Mercury: 7*3600*360;
    Solver verlet("verlet", true,relativistic, years, stepsPerYear);


    // OBS! ADD SUN FIRST
    verlet.add(sun);
    //verlet.add(mercury);
    verlet.add(earth);
    verlet.algorithm(true, 2, false); // true -> print to file // false -> don't print
    finish_2 = clock();

    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));
    cout << "CPU time: " << time_verlet<<endl;
*/
// ----------------------------------------------------------------------------


// Velocity Verlet all planets -----------------------------------------------------

//    clock_t start_2, finish_2;
//    start_2 = clock();
//    Solver verletAll("allplanets", relativistic, true, years, stepsPerYear);

//    // OBS! ADD SUN FIRST
//    verletAll.add(sun);
//    verletAll.add(mercury);
//    verletAll.add(earth);
//    verletAll.add(venus);
//    verletAll.add(pluto);
//    verletAll.add(uranus);
//    verletAll.add(jupiter);
//    verletAll.add(saturn);
//    verletAll.add(neptun);
//    verletAll.add(mars);

//    verletAll.algorithm(true, 2, false);
//    finish_2 = clock();

//    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));
//    cout << "CPU time: " << time_verlet<<endl;
// ----------------------------------------------------------------------------

// Here you can check how jupiter's mass changes the three body system, earth, sun and jupiter:


//  Three body --------------------------------------------------------------
/*
    Solver threeBody("threebody_masses",true,relativistic, 10, 50 );
    mat massFactor = vec({1.0,10.0, 1000.0});

    Planet earth_3(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun_3(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet jupiter_3(1.9e27/m_sun*massFactor[0], 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");

    threeBody.add(earth_3);
    threeBody.add(sun_3);
    threeBody.add(jupiter_3);
    double sun_vx = 0; double sun_vy = 0;
    threeBody.momentumSun( sun_vx,  sun_vy);
    Planet sun_3_new(1.0, 0.0,0.0,sun_vx,sun_vy, "sun");



    for(unsigned int i = 0; i<massFactor.size();i++){
        Planet earth(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        Planet jupiter(1.9e27/m_sun*massFactor[i], 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");
        string type = "massJupiter_" + to_string(massFactor[i]);
        Solver threeBody(type, true, relativistic,years, stepsPerYear);

        threeBody.add(earth);
        threeBody.add(sun);
        threeBody.add(jupiter);
        threeBody.algorithm(true, 2, false);
    }
*/
// ------------------------------------------------------------------------------

// Three body bodycentric coordinates -------------------------------------------
/*
    // Finding centre of mass
    Solver findR("findR", true, relativistic, years, stepsPerYear);
    Planet earth_simple(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun_simple(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet jupiter_simple(1.9e27/m_sun, 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");
    double sun_vx = 0; double sun_vy = 0;

    findR.add(earth_simple);
    findR.add(sun_simple);
    findR.add(jupiter_simple);
    mat R = findR.findCenterOfMass();
    findR.momentumSun( sun_vx,  sun_vy);

    // Using centre of mass to do calculations
    Solver threeBodyCentric("3bodyCentric", true, relativistic, years, stepsPerYear);

    Planet earth_bc(0.000030, 1.0-R[0], 0.000-R[1], 0.0, 2*M_PI, "earth");
    Planet sun_bc(1.0, 0.0-R[0],0.0-R[1],sun_vx,sun_vy, "sun"); // WHAT IS THE INITIAL VELOCITY NEEDED? (MOMENT = 0)
    Planet jupiter_bc(1.9e27/m_sun, 5.2-R[0], 0.0-R[1], 0.0, 0.434*2*M_PI, "jupiter");

    threeBodyCentric.add(earth_bc);
    threeBodyCentric.add(sun_bc);
    threeBodyCentric.add(jupiter_bc);
    threeBodyCentric.algorithm(true, 2, false);
*/
// -----------------------------------------------------------------------------

// Here you can check the energy convergence for different timesteps:

// Check energy convergence ----------------------------------------------------

//    Solver converg_verlet("converg_verlet", true, relativistic, 10, stepsPerYear);
//    Solver converg_euler("converg_euler", false, relativistic, 10, stepsPerYear);
//    converg_verlet.add(earth);
//    converg_verlet.add(sun);
//    converg_euler.add(earth);
//    converg_euler.add(sun);
//    double convergence_crit = 1e-11;
//    double dt = 1.0;
//    converg_verlet.checkConvergence(convergence_crit, dt);
//    converg_euler.checkConvergence(convergence_crit, dt);

// ----------------------------------------------------------------------------


// These are function to find different values and check different things:

// Different functions --------------------------------------------------------

//    checkingGravitation(years, earth, sun, stepsPerYear); // only works for earth and sun
//    findingInitialEscapeVelocity(years, false);  // only works for earth and sun
//    findingInitialCircularVelocity(years, relativistic);  // only works for earth and sun

// ----------------------------------------------------------------------------

//PERIPHELION CALC!!!

    clock_t start_3, finish_3;
    start_3 = clock();
    stepsPerYear = 7*3600*360;;
    years = 100;


    Solver peripeli("peripeli", true,true,  years, stepsPerYear);

    // OBS! ADD SUN FIRST
    peripeli.add(sun_00);
    peripeli.add(mercury_00);
    peripeli.algorithm(false, 2, true); // true -> print to file // false -> don't print
    finish_3 = clock();

    double time_verlet = (double) (finish_3 - start_3)/double((CLOCKS_PER_SEC ));
    cout << "CPU time: " << time_verlet<<endl;


cout << "------------------------------"<<endl;
cout << "Peripeli no rel:"<<endl;


     Solver peripeli_noRel("peripeli",true,false,  years, stepsPerYear);
    // OBS! ADD SUN FIRST
    peripeli_noRel.add(sun_00);
    peripeli_noRel.add(mercury_00);
    peripeli_noRel.algorithm(false, 2, true); // true -> print to file // false -> don't print


    return 0;
}


void readingInitialValues(string filename, double &x, double &y , double &z, double &vx, double &vy, double &vz){
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

void findingInitialCircularVelocity(int years, bool relativistic){
    double start_v = 1.9*M_PI;
    double end_v = 2.1*M_PI;
    double stepsPerYear = 50;
    double v = start_v;

    double dv = (end_v - start_v)/7.0;

    while (v <= end_v){
        Planet earth(0.000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, relativistic, years, stepsPerYear);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(true, 2, false);
        v += dv;
    }
}

void findingInitialEscapeVelocity(int years, bool relativistic ){
    double start_v = 0.97*2*sqrt(2)*M_PI;
    double end_v = 2*M_PI*sqrt(2);
    double stepsPerYear = 50;
    double v = start_v;

    double dv = (end_v - start_v)/5.0;

    while (v <= end_v){
        Planet earth(0.0000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, relativistic,years, stepsPerYear);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(true, 2, false);

        v += dv;
    }
}

void checkingGravitation(int years, Planet earth, Planet sun, double stepsPerYear, bool relativistic){
    double beta = 2.2;

    while (beta <= 3.1){
        string type = "beta-is-" + to_string(beta);
        Solver gravitation(type, true, relativistic,5, stepsPerYear);

        gravitation.add(earth);
        gravitation.add(sun);
        gravitation.algorithm(true, beta, false);

        beta += 0.3;
    }
}
