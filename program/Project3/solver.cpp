#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;
using namespace std;

Solver::Solver(string systemtype_, bool vverlet_, double timelimit){
    //Systemtype: appends to the filename - easy to see the variables.

    // Variables ----------------------
    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = timelimit;
    numberofsteps = timeLimit*100;
    //time = 0;
    dt = timeLimit/(numberofsteps-1);
    dt_half = dt/2;
    numberOfPlanets =0;
    systemtype = systemtype_;
    vverlet = vverlet_;
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
            writevalues(outFiles[i], current,  time);

                // if it is the first timestep we need to calculate the acceleration
                if (time == 0) {
                    updateTotalAcceleration_potEN(current);
                    }
                if (vverlet) {
                    velocityVerlet(current);}

                else {Euler(current);}

                current.energyUpdate();

               cout << current.kinEnergy+ current.potEnergy<<endl;
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
    outfile << "\t"<< "\t" <<current.kinEnergy;
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
