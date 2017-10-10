#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;

Solver::Solver(){

    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = 1.0;
    numberofsteps = 100;
    time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    m_listPlanets.reserve(20);
    //outfile_list.reserve(20);
}
void Solver::totalVelocity(Planet currentPlanet){
    currentPlanet.velocity = currentPlanet.velocity + dt_half*currentPlanet.aks;
}

void Solver::totalPosition(Planet currentPlanet){
    currentPlanet.position = currentPlanet.position + dt*currentPlanet.velocity;
}

void Solver::totalAcceleration(Planet currentPlanet){
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        Planet otherPlanet = m_listPlanets.at(i);
        currentPlanet.aks += currentPlanet.acceleration(otherPlanet);

    }
}

void Solver::velocityVerlet(Planet currentPlanet){
    /*    mat position = currentPlanet.position;  // vec({1,0}); // (x,y)
    mat velocity = currentPlanet.velocity; // vec({0,2*pi});
    mat accleration = currentPlanet.aks;
    double distance; // asbolute value of position
*/
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        //Question: take out loop over sun? Is one extra loop....

        Planet otherPlanet = m_listPlanets.at(i); // m_planets[i];

        //double d =0;

        totalVelocity(currentPlanet);
        totalPosition(currentPlanet);
        //currentPlanet.velocity = currentPlanet.velocity + dt_half*currentPlanet.aks;
        //currentPlanet.position = currentPlanet.position + dt*currentPlanet.velocity;

        totalAcceleration(currentPlanet);

        totalVelocity(currentPlanet); // finale vel. per time step

    }
    //cout <<"i="<<i<<  current.position<< endl;
    //cout <<"i="<<i<<  "time ="<<time<< endl;

}

void Solver::algorithm(){

    time = 0;
    ofstream outfile;
    outfile.open("../../results/position_all_planets.txt");
    outfile << "time" << "\t";
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {

        Planet current = m_listPlanets.at(i);

        //outfile_list.push_back = "file_" + to_string(m_listPlanets.at(i)) + ".txt";
        //string path_to_file = "../../results/" + to_string(outfile_list(i));
        //outfile.open(path_to_file);

        outfile << current.name << "\t" << "\t";
    }
    outfile << endl;

    while (time <timeLimit){

        for (unsigned int i=0; i < m_listPlanets.size(); i++) {

            Planet current = m_listPlanets.at(i); // m_planets[i];

            //outfile << "time "<< "\t" << "x"<< "\t" << "y"<< "\t" << "vx" << "\t" << "vy"<<endl;

            if (time <= pow(10,-8)) totalAcceleration(current);

            velocityVerlet(current);
        }

        time = time + dt;

        writeAllPlanetsPosition(outfile, time);

        // question: writePosistions of all planets in one file?
        //writePosition(outfile, current.position, current.velocity, current.position.size(), time);
    }

    outfile.close();
}

void Solver::add(Planet thisplanet) { // question: Inliner?
    m_listPlanets.push_back(thisplanet);
}

void Solver::writeAllPlanetsPosition(ofstream& outfile, double time){
    outfile << time << "\t";
    for(unsigned int i = 0; i<m_listPlanets.size();i++){
        Planet current = m_listPlanets.at(i);
        outfile << "(" << current.position(0) << ", " << current.position(1) << ")" << "\t";
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

