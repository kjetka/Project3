#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;

Solver::Solver(){

    pi = M_PI;
    fourpi2 = 4*pi*pi;
    timeLimit = 1.0;
    numberofsteps = 100;
    //time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    m_listPlanets.reserve(20);
    //outfile_list.reserve(20);
}
void Solver::totalVelocity(Planet &currentPlanet){
  //  currentPlanet.aks.print("before v - a: ");
  //  currentPlanet.aks.print("before v - v: ");
    currentPlanet.velocity+= dt_half*currentPlanet.aks;
    currentPlanet.velocity.print("v= ");
}

void Solver::totalPosition(Planet &currentPlanet){
    currentPlanet.position += dt*currentPlanet.velocity;
    currentPlanet.position.print("r= ");
}

void Solver::totalAcceleration(Planet &currentPlanet){
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        currentPlanet.aks = vec({0, 0});
        Planet &otherPlanet = m_listPlanets.at(i);

        if(currentPlanet.name == otherPlanet.name){
            //           cout << "Don't get affected by myself" << endl;
        }else{
            //   cout << otherPlanet.name << endl;
            currentPlanet.aks += currentPlanet.acceleration(otherPlanet);
            currentPlanet.aks.print("a= ");
        }
        // question: should we instead have a get-function ans set-function?
    }
}


void Solver::velocityVerlet(Planet &currentPlanet){
    /*    mat position = currentPlanet.position;  // vec({1,0}); // (x,y)
    mat velocity = currentPlanet.velocity; // vec({0,2*pi});
    mat accleration = currentPlanet.aks;
    double distance; // asbolute value of position
*/
   // for (unsigned int i=0; i < m_listPlanets.size(); i++) {

       // if((currentPlanet.position(0) <= pow(10,-8)) & (currentPlanet.position(1) <= pow(10,-8))){ //If sun is origo, skip the sun
         //   cout << "don't need the sun" << endl;
        //}else{
   //         Planet otherPlanet = m_listPlanets.at(i); // m_planets[i];

            totalVelocity(currentPlanet);
            totalPosition(currentPlanet);

            totalAcceleration(currentPlanet);

            totalVelocity(currentPlanet); // finale vel. per time step
        //}
  //  }
    //cout <<"i="<<i<<  current.position<< endl;
    //cout <<"i="<<i<<  "time ="<<time<< endl;

}

void Solver::algorithm(){

    double time = 0;
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

        while (time <timeLimit){
            cout << "time: " << time << endl;
            for (unsigned int i=0; i < m_listPlanets.size(); i++) {
                Planet &currentPlanet = m_listPlanets.at(i); // m_planets[i];

                if((abs(currentPlanet.position(0)) <= 0.000001) & (abs(currentPlanet.position(1)) <= 0.000001)){ //If sun is origo, skip the sun

                }else{
                    //outfile << "time "<< "\t" << "x"<< "\t" << "y"<< "\t" << "vx" << "\t" << "vy"<<endl;

                    if (time <= pow(10,-8)) {  // if it is the first timestep we need to calculate the acceleration
                        totalAcceleration(currentPlanet);
                        //cout << "first a: " << currentPlanet.aks << endl;
                    }

                    velocityVerlet(currentPlanet);

                    // question: writePosistions of all planets in one file?
                    //writePosition(outfile, current.position, current.velocity, current.position.size(), time);
                }
            }

            time = time + dt;
       //     cout << currentPlanet.aks<< endl;
            writeAllPlanetsPosition(outfile, time);

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

