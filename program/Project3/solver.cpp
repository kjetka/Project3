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
    timeLimit = 1;
    numberofsteps = 100;
    //time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;
    numberOfPlanets =0;
    systemtype = systemtype_;
    // -------------------------------
    m_listPlanets.reserve(20);
}

void Solver::updateVelocity(Planet &current){
    //Teacher: CHANGE NAME and can have this single line in the verlet function!!!!
    // changed name
    current.velocity += dt_half*current.aks;
}

void Solver::updatePosition(Planet &current){
    //Teacher: CHANGE NAME and can have this single line in the verlet function!!!!
    //Kjetil: changed name
    current.position += dt*current.velocity; // + (dt*dt/2)*current.aks;
}

void Solver::updateTotalAcceleration(Planet &current){
    // finding force -> acceleration from all other planets
    // Setting the acceleration to 0, so we can sum over all the forces with the new distances

    current.aks = vec({0, 0});
    for (unsigned int i=0; i < numberOfPlanets; i++) {
        Planet &other = m_listPlanets.at(i);
        if(current.name != other.name){
            current.aks += current.acceleration(other);
        }

    }
    // question: should we instead have a get-function ans set-function?


        /*
        current.aks = vec({0, 0});

        Planet &other = m_listPlanets.at(i);

        if(current.name == other.name){
            // "The planet does feel force from it self"
        }else{
            // Sum over accelaration from all planets
            current.aks += current.acceleration(other);
        }
    }
    */
}

void Solver::velocityVerlet(Planet &current){
    //totalVelocity(current);

    current.velocity += dt_half*current.aks;
    updatePosition(current);
    updateTotalAcceleration(current);
    current.velocity += dt_half*current.aks;

    //totalVelocity(current);
}

void Solver::Euler(Planet &current){
    //works only for earth sun
    Planet other = m_listPlanets.at(1);
    current.aks = current.acceleration(other);
    current.velocity += current.aks*dt;
    current.position += current.velocity*dt;
}

void Solver::test_algorithm(){
    // question: What does this?

    // This is just to test the velocityVerlet for the sun-earth-system

    double time = 0;
    Planet &current = m_listPlanets.at(0);

    while (time <timeLimit){


        if (time <= pow(10,-8)) {  // if it is the first timestep we need to calculate the acceleration
            updateTotalAcceleration(current);
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
        cout <<time<<"Why not time =1 counted?"<<endl;

        for (unsigned int i=0; i < numberOfPlanets; i++) {
            Planet &current = m_listPlanets.at(i);

            writePosition(outFiles[i], current.position, current.velocity, current.dimension,  time);

            //cout <<filename<<endl;
            if(current.name != "sun"){
                // if it is the first timestep we need to calculate the acceleration
                if (time == 0) {
                    updateTotalAcceleration(current);
                    }
                //Euler(current);
                velocityVerlet(current);
                }

            //writePosition(outFiles[i], current.position, current.velocity, current.dimension,  time);

        }
        time = time + dt;
    }
    //closing open files
    for (unsigned int i=0; i < numberOfPlanets; i++) {
        outFiles[i].close();
    }




    //outfile.close();

    /*
    // all of this is for the file-printing ----------------
    ofstream outfile;
    outfile.open("../../results/position_all_planets.txt");
    outfile << "time" << "\t \t \t";
    for (unsigned int i=0; i < numberOfPlanets; i++) {

        Planet current = m_listPlanets.at(i);
        cout << "dimension: "<<current.dimension<<endl;

        outfile << current.name << "\t \t \t";
    }

    outfile << endl;
    outfile << "\t \t";

    for (unsigned int i=0; i < numberOfPlanets; i++) {
        outfile << "x" << "\t \t" << "y" << "\t \t";
    }
    outfile << endl;
    */
    // -----------------------------------------------------

}

void Solver::add(Planet thisplanet) {
    m_listPlanets.push_back(thisplanet);
    numberOfPlanets += 1;
}

void Solver::writeAllPlanetsPosition(ofstream& outfile, double time){
    outfile << std::fixed;
    outfile << std::setprecision(4);
    outfile << time << "\t";
    for(unsigned int i = 0; i<numberOfPlanets;i++){
        Planet &current = m_listPlanets.at(i);
        outfile << current.position(0)<< "\t" << current.position(1) << "\t";
    }
    outfile << endl;
}

void Solver::writePosition(ofstream& outfile, mat& r, mat& v, int dimension, double time){
    outfile << time;
    for(int i=0;i<dimension; i++){
        outfile << "\t" << "\t" << r(i);
    }
    for(int i=0;i<dimension; i++){
        outfile << "\t"<< "\t"  << v(i);
    }
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
