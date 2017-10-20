#include "solver.h"
#include "planet.h"
#include <ctime>
#include <ratio>
#include <chrono>

#include <armadillo>
using namespace arma;
using namespace std;
using namespace std::chrono;

Solver::Solver(string systemtype_, bool vverlet_, double timelimit){
    //Systemtype: appends to the filename - easy to see the variables.

    // Variables ----------------------
    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = timelimit;
    numberofsteps = timeLimit*600;
    //time = 0;
    dt = timeLimit/(numberofsteps-1);
    dt_half = dt/2;
    numberOfPlanets =0;
    systemtype = systemtype_;
    vverlet = vverlet_;
    // -------------------------------
    m_listPlanets.reserve(20);
    energy_prev = 0;
}


void Solver::updateTotalAcceleration_potEN(Planet &current){
    // finding force -> acceleration from all other planets

    current.acceleration = vec({0, 0});
    current.potEnergy = 0;
    for (unsigned int i=0; i < numberOfPlanets; i++) {
        Planet &other = m_listPlanets.at(i);
        if(current.name != other.name){
            double reldistance = current.relativeDistance(other);

            current.acceleration += current.accelerationFromOther(other, reldistance);
            mat accelerationFromOther(mat &a_other, double &distance);

            //current.FromOtherPotEnergy must be after current.accelerationFromOther!!!!!!!!!!!

            current.potEnergy += current.FromOtherPotEnergy(other, reldistance);
           // cout << "carefull with the potential energy "<<endl;
        }

    }
    // question: should we instead have a get-function ans set-function?
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
    double L = current.mass*current.distance*pow(dot(current.velocity, current.velocity),0.5);
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

void Solver::velocityVerlet(Planet &current){
    current.velocity += dt_half*current.acceleration;
    current.position += dt*current.velocity; //  + (dt*dt/2)*current.acceleration;
    updateTotalAcceleration_potEN(current);
    current.velocity += dt_half*current.acceleration;
}

void Solver::Euler(Planet &current){
    //works only for earth sun
    Planet other = m_listPlanets.at(1);
    updateTotalAcceleration_potEN(current);
    //current.acceleration = current.accelerationFromOther(other, distance);
    current.velocity += current.acceleration*dt;
    current.position += current.velocity*dt;






    /*
    //ONLYE SUN EARTH!!!!!!!
    distance = sqrt(dot(current.position, current.position));

    ax = (-fourpi2/pow(r,3))*x;
    ay = (-fourpi2/pow(r,3))*y;
    vx = vx + dt*ax;
    vy = vy + dt*ay;
    x = x + dt*vx;
    y = y + dt*vy;

    */


}



void Solver::algorithm(){
    if (vverlet==true){     cout << "Running velocity verlet"<<endl;}
    else                    cout << "running Euler" << endl;
    double time = 0;
    //initializing and opening files
    ofstream *outFiles = new ofstream [numberOfPlanets];
    initializeFiles(outFiles, systemtype);

    while (time <= timeLimit){
       for (unsigned int i=0; i < numberOfPlanets; i++) {
            Planet &current = m_listPlanets.at(i);
            writevalues(outFiles[i], current,  time);
                // Timing:

                // if it is the first timestep we need to calculate the acceleration
                if (time == 0) {
                    updateTotalAcceleration_potEN(current);
                    }
                if (vverlet==true) {
                    velocityVerlet(current);}

                else {Euler(current);}



                //test_energy(current);
                //test_circular( current, time);
                //test_angularmoment(current);
                current.energyUpdate();

                //cout << current.kinEnergy << "\t" << current.potEnergy << "\t " << current.kinEnergy+ current.potEnergy<<endl;

        }
        time  += dt;
    }
    //closing open files
    for (unsigned int i=0; i < numberOfPlanets; i++) {
        outFiles[i].close();
    }
}

void Solver::add(Planet thisplanet) {
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
    string location = "../../results/";
    string filetype = ".txt";
    for (unsigned int i=0; i < numberOfPlanets; i++) {
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
                if(current.dimension =! other.dimension){
                    cout <<"Dimensions doesn't match"<<endl;
                    exit(2);
                }
            }
        }
    }
}

