#include <iostream>
#include <iostream>
#include "planet.h"
#include "solver.h"

using namespace std;
using namespace arma;

void findingInitialEscapeVelocity();
void findingInitialCircularVelocity(int years);
void checkingGravitation();
void readingInitialValues(string filename, double& x, double& y, double& z, double& vx, double& vy, double& vz);
void checkConvergenceEnergy();
void checkConvergenceTimestep();
void checkingPerihelion();
void velocityVerletAllPlanets(int years, double stepsPerYear);
void runWithEuler(int years, double stepsPerYear, bool printfile);
void runWithVelocityVerlet(int years, double stepsPerYear, bool printfile);

int main(){

    double m_sun = 2.0*1e30;
    int years = 50;
    int stepsPerYear = 1000;

    // Checking things -----------------------------------------------------------

//    checkConvergenceEnergy();
//    checkConvergenceTimestep();
//    checkingPerihelion();
//    checkingGravitation(); // only works for earth and sun
//    findingInitialEscapeVelocity();  // only works for earth and sun
//    findingInitialCircularVelocity(years);  // only works for earth and su


    // Running things ------------------------------------------------------------

    //velocityVerletAllPlanets(years, stepsPerYear);
    runWithVelocityVerlet(years, stepsPerYear, false);
    runWithEuler(years, stepsPerYear, false);


    // Here you can check how jupiter's mass changes the three body system, earth, sun and jupiter:

    //  Three body --------------------------------------------------------------

    //    mat massFactor = vec({1.0,10.0, 1000.0});

    //    for(unsigned int i = 0; i<massFactor.size();i++){
    //        Planet earth(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
    //        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    //        Planet jupiter(1.9e27/m_sun*massFactor[i], 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");
    //        string type = "massJupiter_" + to_string(massFactor[i]);
    //        Solver threeBody(type, true, years, stepsPerYear);
    //        threeBody.add(earth);
    //        threeBody.add(sun);
    //        threeBody.add(jupiter);
    //        threeBody.algorithm(true, 2, false);
    //    }

    // ------------------------------------------------------------------------------

    // Three body bodycentric coordinates -------------------------------------------

       // Finding centre of mass
/*
    Solver findR("findR", true, false, years, stepsPerYear);
    Planet earth_simple(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun_simple(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet jupiter_simple(1.9e27/m_sun, 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");
    double sun_vx = 0; double sun_vy = 0;


    findR.add(earth_simple);
    findR.add(sun_simple);
    findR.add(jupiter_simple);
    mat R = findR.findCenterOfMass();
    findR.momentumSun( sun_vx,  sun_vy);

    cout << sun_vx<< "   " << sun_vy <<endl;
    // Using centre of mass to do calculations
    Solver threeBodyCentric("3bodyCentric", true, false, years, stepsPerYear);

    Planet earth_bc(0.000030, 1.0-R[0], 0.000-R[1], 0.0, 2*M_PI, "earth");
    Planet sun_bc(1.0, 0.0-R[0],0.0-R[1],sun_vx,sun_vy, "sun");
    Planet jupiter_bc(1.9e27/m_sun, 5.2-R[0], 0.0-R[1], 0.0, 0.434*2*M_PI, "jupiter");

    threeBodyCentric.add(earth_bc);
    threeBodyCentric.add(sun_bc);
    threeBodyCentric.add(jupiter_bc);
    threeBodyCentric.algorithm(true, 2, false);

*/

/*
stepsPerYear = 800;
    // Finding centre of mass
    Solver findR("findR", true, false, years, stepsPerYear);
    Planet earth_simple(0.000030, 1.0, 0.000, 0.0, 2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun_simple(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet jupiter_simple(1.9e27/m_sun, 5.2, 0.0, 0.0, 0.434*2*M_PI, "jupiter");

    findR.add(earth_simple);
    findR.add(sun_simple);
    findR.add(jupiter_simple);
    mat R = findR.findCenterOfMass();

    // Using centre of mass to do calculations
    Solver threeBodyCentric("3bodyCentric", true, false, years, stepsPerYear);

    Planet earth_bc(0.000030, 1.0-R[0], 0.000-R[1], 0.0, 2*M_PI, "earth");
    Planet sun_bc(1.0, 0.0-R[0],0.0-R[1],0.0,0.0, "sun"); // WHAT IS THE INITIAL VELOCITY NEEDED? (MOMENT = 0)
    Planet jupiter_bc(1.9e27/m_sun, 5.2-R[0], 0.0-R[1], 0.0, 0.434*2*M_PI, "jupiter");

    threeBodyCentric.add(earth_bc);
    threeBodyCentric.add(sun_bc);
    threeBodyCentric.add(jupiter_bc);
    threeBodyCentric.algorithm(true, 2, false);

//checkingPerihelion();
*/
    // ----------------------------------------------------------------------------


    return 0;
}

void runWithEuler(int years, double stepsPerYear, bool printfile){
    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");

    clock_t start_, finish_;

    Solver euler("euler", false,false,  years, stepsPerYear);

    euler.add(sun);
    euler.add(earth);
    start_ = clock();
    euler.algorithm(printfile, 2, false); // true -> print to file // false -> don't print
    finish_ = clock();
    double time_euler = (double) (finish_ - start_)/double((CLOCKS_PER_SEC ));

    cout<< "CPU time Euler: " <<time_euler<<endl;
}

void runWithVelocityVerlet(int years, double stepsPerYear, bool printfile){
    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");

    clock_t start_2, finish_2;
    Solver verlet("verlet", true,false,  years, stepsPerYear);

    verlet.add(sun);
    verlet.add(earth);
    start_2 = clock();
    verlet.algorithm( printfile, 2, false); // true -> print to file // false -> don't print
    finish_2 = clock();

    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));
    cout << "CPU time Verlet: " << time_verlet<<endl;

}

void velocityVerletAllPlanets(int years, double stepsPerYear){
    double m_sun = 2.0*1e30;
    string planetname;
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

    clock_t start_2, finish_2;
    start_2 = clock();
    Solver verletAll("allplanets", true,false,  years, stepsPerYear);

    // OBS! ADD SUN FIRST
    verletAll.add(sun);
    verletAll.add(mercury);
    verletAll.add(earth);
    verletAll.add(venus);
    verletAll.add(pluto);
    verletAll.add(uranus);
    verletAll.add(jupiter);
    verletAll.add(saturn);
    verletAll.add(neptun);
    verletAll.add(mars);
    verletAll.algorithm(true, 2, false);
    finish_2 = clock();

    double time_verlet = (double) (finish_2 - start_2)/double((CLOCKS_PER_SEC ));
    cout << "CPU time: " << time_verlet<<endl;
}


void checkingPerihelion(){
    double m_sun = 2.0*1e30;
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    Planet mercury(3.3e23/m_sun,0.3075, 0, 0, 12.44,"mercury");
    clock_t start_3, finish_3;
    double stepsPerYear =  7*360*3600;
    int years = 100;

    Solver periheli("periheli", true, false, 100, stepsPerYear);

    periheli.add(sun);
    periheli.add(mercury);
    start_3 = clock();
    periheli.algorithm(false, 2, true); // true -> print to file // false -> don't print
    finish_3 = clock();

    double time_perihelion = (double) (finish_3 - start_3)/double((CLOCKS_PER_SEC ));
    cout << "CPU time: " << time_perihelion<<endl;

}

void checkConvergenceTimestep(){
    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
    string type, type2;
    int years = 100;

    mat stepsPerYear = vec({10, 100, 1000});
    for (unsigned int i=0; i<stepsPerYear.size(); i++){
        type = to_string(stepsPerYear[i]) + "timestep_eu";
        Solver timesteps_eu(type, false, false, years, stepsPerYear[i]);

        type2 = to_string(stepsPerYear[i]) + "timestep_ve";
        Solver timesteps_ve(type2, true, false, years, stepsPerYear[i]);

        timesteps_eu.add(sun);
        timesteps_eu.add(earth);
        timesteps_ve.add(sun);
        timesteps_ve.add(earth);

        timesteps_eu.algorithm(true, 2, false);
        timesteps_ve.algorithm(true, 2, false);

    }
}

void checkConvergenceEnergy(){
    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth");
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");

    double stepsPerYear;
    Solver converg_verlet("converg_verlet", true,false,  10, stepsPerYear);
    Solver converg_euler("converg_euler", false,false,  10, stepsPerYear);
    converg_verlet.add(earth);
    converg_verlet.add(sun);
    converg_euler.add(earth);
    converg_euler.add(sun);
    double convergence_crit = 1e-11;
    double dt = 1.0;
    converg_verlet.checkConvergence(convergence_crit, dt);
    converg_euler.checkConvergence(convergence_crit, dt);
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

void findingInitialCircularVelocity(int years){
    double start_v = 1.9*M_PI;
    double end_v = 2.1*M_PI;
    double stepsPerYear = 50;
    double v = start_v;

    double dv = (end_v - start_v)/7.0;

    while (v <= end_v){
        Planet earth(0.000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, false, years, stepsPerYear);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(true, 2, false);
        v += dv;
    }
}

void findingInitialEscapeVelocity(){
    double start_v = 2*sqrt(2)*M_PI-0.2;
    double end_v = 2*M_PI*sqrt(2)+0.2;
    double stepsPerYear = 100;
    double years = 5000;
    double v = start_v;

    while (v < end_v){
        Planet earth(0.0000030, 1.0, 0.000, 0.0, v, "earth"); // (mass,x,y,vx,vy)
        Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");
        string type = "v_ini_is" + to_string(v);
        Solver test_initial(type, true, false, years, stepsPerYear);

        test_initial.add(earth);
        test_initial.add(sun);
        test_initial.algorithm(true, 2, false);

        v += 0.2;
    }
}

void checkingGravitation(){
    Planet earth(3e-6, 1.0, 0.000, 0.0,2*M_PI, "earth"); // (mass,x,y,vx,vy)
    Planet sun(1.0, 0.0,0.0,0.0,0.0, "sun");

    double years = 5;
    double beta = 2.2;
    double stepsPerYear = 1000;

    while (beta <= 3.1){
        string type = "beta-is-" + to_string(beta);
        Solver gravitation(type, true, false, years, stepsPerYear);

        gravitation.add(earth);
        gravitation.add(sun);
        gravitation.algorithm(true, beta, false);

        beta += 0.3;
    }
}
