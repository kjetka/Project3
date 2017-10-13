#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;
using namespace std;

Solver::Solver(string systemtype_){
    //Systemtype: appends to the filename - easy to see the variables.

    // Variables ----------------------
    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = 1.0;
    numberofsteps = 10000;
    //time = 0;
    dt = timeLimit/(numberofsteps-1);
    dt_half = dt/2;
    numberOfPlanets =0;
    systemtype = systemtype_;
    // -------------------------------
    m_listPlanets.reserve(20);
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

        }

    }
    // question: should we instead have a get-function ans set-function?
}

void Solver::velocityVerlet(Planet &current){

    current.velocity += dt_half*current.acceleration;
    current.position += dt*current.velocity; // + (dt*dt/2)*current.aks;
    updateTotalAcceleration_potEN(current);
    current.velocity += dt_half*current.acceleration;
}

void Solver::Euler(Planet &current){
    //works not only for earth sun
    Planet other = m_listPlanets.at(1);
   double  distance = current.relativeDistance(other);

    current.acceleration = current.accelerationFromOther(other, distance);
    current.velocity += current.acceleration*dt;
    current.position += current.velocity*dt;
}

void Solver::test_algorithm(){
    // question: Remove

    // This is just to test the velocityVerlet for the sun-earth-system

    double time = 0;
    Planet &current = m_listPlanets.at(0);

    while (time <timeLimit){


        if (time <= pow(10,-8)) {  // if it is the first timestep we need to calculate the acceleration
            updateTotalAcceleration_potEN(current);
        }

        velocityVerlet(current);

        time += dt;
        current.position.print("r:");
    }
}


void Solver::algorithm(){
    double time = 0;
    //initializing and opening files
    ofstream *outFiles = new ofstream [numberOfPlanets];
    initializeFiles(outFiles, systemtype);

    while (time <= timeLimit){

        for (unsigned int i=0; i < numberOfPlanets; i++) {
            Planet &current = m_listPlanets.at(i);
            writevalues(outFiles[i], current.position, current.velocity,current.kinEnergy,  current.dimension,  time);

                // if it is the first timestep we need to calculate the acceleration
                if (time == 0) {
                    updateTotalAcceleration_potEN(current);
                    }
                //Euler(current);
                velocityVerlet(current);
                current.energyUpdate();
                cout<< current.kinEnergy<<endl;
                }

        time = time + dt;
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

void Solver::writevalues(ofstream& outfile, mat& r, mat& v, double& kineticenergy, int dimension, double time){
    outfile << time;
    for(int i=0;i<dimension; i++){
        outfile << "\t" << "\t" << r(i);
    }
    for(int i=0;i<dimension; i++){
        outfile << "\t"<< "\t"  << v(i);
    }
    outfile << kineticenergy;
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
