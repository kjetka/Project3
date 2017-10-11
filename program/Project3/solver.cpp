#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;

Solver::Solver(){

    // Variables ----------------------

    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = 1.0;
    numberofsteps = 100;
    //time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    // -------------------------------

    m_listPlanets.reserve(20);
}

void Solver::totalVelocity(Planet &currentPlanet){

    currentPlanet.velocity += dt_half*currentPlanet.aks;
}

void Solver::totalPosition(Planet &currentPlanet){

    currentPlanet.position += dt*currentPlanet.velocity; // + (dt*dt/2)*currentPlanet.aks;
}

void Solver::totalAcceleration(Planet &currentPlanet){

    // finding force -> acceleration from all other planets
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {

        // Setting the acceleration to 0, so we can sum over all the forces with the new distances
        currentPlanet.aks = vec({0, 0});

        Planet &otherPlanet = m_listPlanets.at(i);

        if(currentPlanet.name == otherPlanet.name){
            // "The planet does feel force from it self"
        }else{
            // Sum over accelaration from all planets
            currentPlanet.aks += currentPlanet.acceleration(otherPlanet);
        }
        // question: should we instead have a get-function ans set-function?
    }
}


void Solver::velocityVerlet(Planet &currentPlanet){

    totalVelocity(currentPlanet);
    totalPosition(currentPlanet);

    totalAcceleration(currentPlanet);

    totalVelocity(currentPlanet);
}

void Solver::Euler(Planet &currentPlanet){
    Planet otherPlanet = m_listPlanets.at(1);
    currentPlanet.aks = currentPlanet.acceleration(otherPlanet);
    currentPlanet.velocity += currentPlanet.aks*dt;
    currentPlanet.position += currentPlanet.velocity*dt;
}

void Solver::test_algorithm(){
    // This is just to test the velocityVerlet for the sun-earth-system

    double time = 0;

    while (time <timeLimit){

        Planet &currentPlanet = m_listPlanets.at(0);

        if (time <= pow(10,-8)) {  // if it is the first timestep we need to calculate the acceleration
            totalAcceleration(currentPlanet);
        }

        velocityVerlet(currentPlanet);

        time = time + dt;
        currentPlanet.position.print("r:");
    }
}

void Solver::algorithm(){

    double time = 0;

    // all of this is for the file-printing ----------------
    ofstream outfile;
    outfile.open("../../results/position_all_planets.txt");
    outfile << "time" << "\t \t \t";
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {

        Planet currentPlanet = m_listPlanets.at(i);
        outfile << currentPlanet.name << "\t \t \t";
    }

    outfile << endl;
    outfile << "\t \t";

    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        outfile << "x" << "\t \t" << "y" << "\t \t";
    }
    outfile << endl;

    // -----------------------------------------------------

    while (time <timeLimit){
        cout << "time: " << time << endl;
        for (unsigned int i=0; i < m_listPlanets.size(); i++) {
            Planet &currentPlanet = m_listPlanets.at(i);

            if((abs(currentPlanet.position(0)) <= 0.000001) & (abs(currentPlanet.position(1)) <= 0.000001)){ //If sun is origo, skip the sun

            }else{
                //outfile << "time "<< "\t" << "x"<< "\t" << "y"<< "\t" << "vx" << "\t" << "vy"<<endl;

                if (time <= pow(10,-8)) {  // if it is the first timestep we need to calculate the acceleration
                    totalAcceleration(currentPlanet);
                }
                // Here we can choose the method we want to use: -----------------

                //Euler(currentPlanet);

                velocityVerlet(currentPlanet);

                // ---------------------------------------------------------------

                currentPlanet.position.print("r=");

                // question: How to write positions into seperate files?

            }
        }

        time = time + dt;

        writeAllPlanetsPosition(outfile, time);
        //writePosition(outfile, current.position, current.velocity, current.position.size(), time);

    }
    outfile.close();
}

void Solver::add(Planet thisplanet) { // question: Inliner?
    m_listPlanets.push_back(thisplanet);
}

void Solver::writeAllPlanetsPosition(ofstream& outfile, double time){
    outfile << std::fixed;
    outfile << std::setprecision(4);
    outfile << time << "\t";
    for(unsigned int i = 0; i<m_listPlanets.size();i++){
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

