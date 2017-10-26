#include "solver.h"
#include "planet.h"
#include <ctime>
#include <ratio>
#include <chrono>
#include <cmath>

#include <armadillo>
using namespace arma;
using namespace std;
using namespace std::chrono;

Solver::Solver(string systemtype_, bool choiseOfMethod_, double timelimit){
    //Systemtype: appends to the filename - easy to see the variables.

    // Variables ----------------------
    pi = M_PI;
    stepsPerYear = 20000;
    //for Mercury: 7*3600*360;
    fourpi2 = 4*pi*pi;
    timeLimit = timelimit;
    numberOfSteps = timeLimit*stepsPerYear;
    dt = timeLimit/(numberOfSteps-1);
    dt_half = dt/2;
    numberOfPlanets =0;
    systemtype = systemtype_;
    choiseOfMethod = choiseOfMethod_; // True -> velocity verlet // False -> Euler

    // -------------------------------
    m_listPlanets.reserve(20);
    energy_prev = 0;
}


void Solver::updateTotalAcceleration_potEN(Planet &current, double beta){
    // finding force -> acceleration from all other planets

    current.acceleration = vec({0, 0});
    current.potEnergy = 0;
    for (int i=0; i < numberOfPlanets; i++) {
        Planet &other = m_listPlanets.at(i);
        if(current.name != other.name){
            double reldistance = current.relativeDistance(other);

            current.acceleration += current.accelerationFromOther(other, reldistance, beta);
            mat accelerationFromOther(mat &a_other, double &distance);

            //current.FromOtherPotEnergy must be after current.accelerationFromOther!!!!!!!!!!!

            current.potEnergy += current.FromOtherPotEnergy(other, reldistance);
            // cout << "carefull with the potential energy "<<endl;
        }

    }
}

void Solver::test_energy(Planet current){
    double Kinetic = 0.5*current.mass*dot(current.velocity,current.velocity);
    double energy_current = current.potEnergy+ Kinetic;
    double tolerance_energy= 8e-5;
    if (fabs( energy_current - energy_prev)>tolerance_energy){
        cout << "Exit: energy not conserved within " << tolerance_energy<<endl;
        exit(3);
    }
    //cout << energy_current << "\t" << current.potEnergy<<endl;


    energy_prev = energy_current;
}

void Solver::test_angularmoment(Planet current){
    //double L = current.mass*current.distance*pow(dot(current.velocity, current.velocity),0.5);
    // cout << current.name <<"   "<<L<< endl;
    //cout << current.velocity<<endl;
}

void Solver::test_circular(Planet current, double time){
    double tolerance_pos= 1e-2;
    double r_now = dot(current.position, current.position);

    if (fabs(r_now-current.absposition_start)>tolerance_pos){
        cout << "Exit: Not a circular motion for planet " << current.name <<"Diverged after time = "<< time<< endl;
        exit(3);
    }

}

void Solver::velocityVerlet(Planet &current, double beta){
    current.velocity += dt_half*current.acceleration;
    current.position += dt*current.velocity;
    updateTotalAcceleration_potEN(current, beta);
    current.velocity += dt_half*current.acceleration;
}

void Solver::Euler(Planet &current, double beta){
    //works only for earth sun
    Planet other = m_listPlanets.at(1);
    updateTotalAcceleration_potEN(current, beta);
    //current.acceleration = current.accelerationFromOther(other, distance);
    current.velocity += current.acceleration*dt;
    current.position += current.velocity*dt;

}

void Solver::algorithm(bool printfile, double beta){
    //cout <<"Steps:  "<< stepsPerYear<<endl;
    if (choiseOfMethod==true){     cout << "Running velocity verlet"<<endl;}
    else                    cout << "Running Euler" << endl;

    double time = 0;

    //initializing and opening files
    ofstream *outFiles = new ofstream [numberOfPlanets];
    if (printfile) initializeFiles(outFiles, systemtype);

    while (time <= timeLimit){
        for (signed int i=0; i < numberOfPlanets; i++) {
            Planet &current = m_listPlanets.at(i);

            writevalues(outFiles[i], current,  time);

            /*  If it is the first timestep we need to
                calculate the acceleration from the initial values */
            if (time == 0) {
                updateTotalAcceleration_potEN(current, beta);
            }


            if (choiseOfMethod==true) {
                velocityVerlet(current, beta);}

            else {Euler(current, beta);}

            findingPerihelion(Planet &current)

            //test_energy(current);
            //test_circular( current, time);
            //test_angularmoment(current);
            current.kinEnergyUpdate();
            //cout << current.kinEnergy << "\t" << current.potEnergy << "\t " << current.kinEnergy+ current.potEnergy<<endl;

            // This is for calculation the Perihelion

        }

        time  += dt;
    }

    //closing open files
    if(printfile){
        for (signed int i=0; i < numberOfPlanets; i++) {
            outFiles[i].close();
        }
    }

}

void Solver::findingPerihelion(Planet &current){
    if((current.name != "sun") && ( time > 100-0.241)){
        current.sunDistance = sqrt(current.position[0]*current.position[0] + current.position[1]*current.position[1]);
        if (current.sunDistance < current.minimum){
            current.minimum = current.sunDistance;
            current.min_x_after = current.position[0];
            current.min_y_after = current.position[1];
    }
    if((current.name != "sun") && (time > timeLimit-dt)){
        cout << "Perihelion position after 100 years: " << current.min_x_after <<", " << current.min_y_after << endl;
        cout << "Perihelion angle after 100 years: " << atan(current.min_y_after/current.min_x_after)*206264.806 << " arc seconds" << endl;

        }

    }
}

void Solver::add(Planet thisplanet){
    m_listPlanets.push_back(thisplanet);
    numberOfPlanets += 1;
}

void Solver::writevalues(ofstream& outfile, Planet& current, double time){
    outfile << time;
    double dimension = current.dimension;
    for(int i=0;i<dimension; i++){
        outfile << "\t" << "\t" << current.position(i);
    }
    for(int i=0;i<dimension; i++){
        outfile << "\t"<< "\t"  << current.velocity(i);
    }
    outfile << "\t"<< "\t" << setprecision(10) << current.kinEnergy;
    outfile << "\t"<< "\t" <<current.potEnergy;

    outfile << endl;
}

void Solver::writeheader(ofstream &outfile, int dimension){
    string r[] = {"x", "y", "z"};
    string v[] = {"vx", "vy", "vz"};
    outfile << "time";
    for(int i=0;i<dimension; i++){
        outfile << "\t" << "\t" << r[i];
    }
    for(int i=0;i<dimension; i++){
        outfile << "\t"<< "\t"  << v[i];
    }
    outfile <<  "\t"<< "\t"  << "KineticEnergy";
    outfile <<  "\t"<< "\t"  << "PotentialEnergy";

    outfile << endl;
}

void Solver::initializeFiles(ofstream *outFiles, string nameinfo){
    string filename;
    string location = "../../results/text/";
    string filetype = ".txt";
    for (int i=0; i < numberOfPlanets; i++) {
        Planet &current = m_listPlanets.at(i);
        filename = location + current.name +"-"+ nameinfo+ filetype;
        outFiles[i].open(filename);
        writeheader(outFiles[i], current.dimension);
    }
}

void Solver::pretests(){
    for(int i=0; i<numberOfPlanets; i++){
        Planet current = m_listPlanets.at(i);

        for(int j=0; j<numberOfPlanets; j++){
            if (j!=i){
                Planet other = m_listPlanets.at(j);
                if((current.dimension =! other.dimension)){
                    cout <<"Dimensions doesn't match"<<endl;
                    exit(2);
                }
            }
        }
    }
}

void Solver::check_convergence(double eps, double &dt){
    Planet &planet = m_listPlanets.at(0);
    Planet &sun = m_listPlanets.at(1);
    double beta = 2;
    dt = 1.0;

    ofstream outfile;
    outfile.open("../../results/text/convergence.txt");

    mat pos_start_e, vel_start_e, acc_start_e;
    double kin_start_e, pot_start_e, r_start_e, dist_start_e;
    pos_start_e = planet.position;
    vel_start_e = planet.velocity;
    acc_start_e = planet.acceleration;
    kin_start_e= planet.kinEnergy;
    pot_start_e = planet.potEnergy;
    r_start_e = planet.absposition_start;
    dist_start_e = planet.distance;

    mat pos_start_s, vel_start_s, acc_start_s;
    double kin_start_s, pot_start_s, r_start_s, dist_start_s;
    pos_start_s = sun.position;
    vel_start_s = sun.velocity;
    acc_start_s = sun.acceleration;
    kin_start_s= sun.kinEnergy;
    pot_start_s = sun.potEnergy;
    r_start_s = sun.absposition_start;
    dist_start_s = sun.distance;

    double start_energy = kin_start_e + pot_start_e + sun.potEnergy + sun.kinEnergy;

    double end_energy = start_energy*2;
    //double kin_start_s= sun.kinEnergy;
    //double pot_start_s = sun.potEnergy;
    //cout << sun.potEnergy + sun.kinEnergy << endl;

    outfile << "Timelimit= "<< timeLimit << ". Convergence criteria: dE <  "<< eps  <<endl;
    outfile <<endl;

    outfile << "dt \t" << "Total energy \t " << "Change in energy \t"<<endl;

    int interaction = 0;
    int interactionLimit = 15;

    while ((abs(start_energy - end_energy) > eps) && (interaction < interactionLimit)){
        dt = dt/10.0;
        dt_half= dt/2.;
        cout << "-------------------"<<endl;
        planet.position = pos_start_e;
        planet.position=  pos_start_e;
        planet.velocity = vel_start_e;
        planet.acceleration = acc_start_e;
        planet.kinEnergy = kin_start_e;
        planet.potEnergy = pot_start_e;
        planet.absposition_start = r_start_e;
        planet.distance =   dist_start_e;

        sun.position = pos_start_s;
        sun.position=  pos_start_s;
        sun.velocity = vel_start_s;
        sun.acceleration = acc_start_s;
        sun.kinEnergy = kin_start_s;
        sun.potEnergy = pot_start_s;
        sun.absposition_start = r_start_s;
        sun.distance =   dist_start_s;

        algorithm(false, beta); //not printing!!!

        end_energy =  planet.kinEnergy + planet.potEnergy + sun.kinEnergy + sun.potEnergy;

        //cout << "position end: " << planet.position << endl;
        //cout << planet.name <<"end:   Kinetic, Potential:   " << planet.kinEnergy << ", "<< planet.potEnergy << endl;
        //cout << "Energy : " << setprecision(10)<< " kin e "<<planet.kinEnergy << " pot e " <<planet.potEnergy <<" kin s "<< sun.kinEnergy << " pot sun "<<  sun.potEnergy << endl;

        outfile <<dt  << "\t"<< end_energy<< "\t"<<abs(start_energy-end_energy)<<endl;
        interaction += 1;
    }

    if(interaction == interactionLimit){
        cout << "Did not reach the convergence criteria" << endl;
        cout << "The energy difference reached was: " << start_energy - end_energy << endl;
        cout << "I think we have reached the difference in the occillation, so we can't get it smaller." << endl;
        cout << "Maybe we can find the occillation ampltude and substract it from this difference. Is the amplitude constant?" << endl;
        cout << "Is dE = 10^-3 good enough?" << endl;
    }else{
        cout << "For the energy to be converged, the timestep has to be:" << dt << endl;
        cout << "Energy difference: " << start_energy - end_energy << endl;
    }
    outfile.close();
}

mat Solver::find_center_of_mass(){
    mat top = vec({0,0});
    mat bottom = vec({0,0});
    for(unsigned int i = 0; i<m_listPlanets.size(); i++){
        Planet current = m_listPlanets[i];
        top += current.mass*current.position;
        bottom += current.mass;
    }
    mat centerofmass = top/bottom;
    return centerofmass;
}
