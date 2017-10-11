#include "solver.h"
#include "planet.h"

#include <armadillo>
using namespace arma;

Solver::Solver(){

    fourpi2 = 4*M_PI*M_PI;
    timeLimit = 1.0;
    numberofsteps = 10000;
    time = 0;
    dt = timeLimit/numberofsteps;
    dt_half = dt/2;

    m_listPlanets.reserve(20);

}
void Solver::velocity_update(mat& v, mat& a){
    // question: Make this inliner?
   v = v + dt_half*a;
    //vx = vx + dt_half*ax;
    //vy = vy + dt_half*ay;
}

void Solver::velocityVerlet(mat &position, mat& velocity){
    position = vec({1,0}); // (x,y)
    velocity = vec({0,2*M_PI});
    mat acleration = vec({0,0}); // question: destroys everything???
    double distance; // asbolute value of position

    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        //Question: take out loop over sun? Is one extra loop....
        Planet current = m_listPlanets.at(i); // m_planets[i];

        current.acceleration(position,acleration, 2, distance);
        // Question: fix relative distance between two different planets

        current.relativeDistance(position, 2, distance); // (position, dimension, distance)
        current.acceleration(position, acleration, 2,distance); //(mat& position, mat& aks, int dimension, double absDistance );

        ofstream outfile;
        outfile.open("../../results/test1.txt");
        outfile << "time "<< "\t" << "x"<< "\t" << "y"<< "\t" << "vx" << "\t" << "vy"<<endl;
        double time = 0;

        while(time<timeLimit){

            velocity_update(velocity, acleration);
            position = position + dt*velocity;
            //x = x + dt*vx;
            //y = y + dt*vy;

            current.relativeDistance(position, 2,distance);

            current.acceleration(position, acleration, 2, distance);

            velocity_update(velocity,acleration); // finale vel. per time step
            time = time + dt;


            writePosition(outfile, position, velocity, 2, time);

        }
        //cout <<"i="<<i<<  current.position<< endl;
        //cout <<"i="<<i<<  "time ="<<time<< endl;

        outfile.close();

        }

}

void Solver::add(Planet thisplanet) { // question: Inliner?
    m_listPlanets.push_back(thisplanet);
}

void Solver::writePosition(ofstream& outfile, mat& r, mat& v, int dimension, double time){
    outfile << time;
    for(int i=0;i<dimension; i++){
        outfile << "\t" << "\t" << r(i);
    }
    for(int i=0;i<dimension; i++){
        outfile << "\t"<< "\t"  << v(i);}
    outfile << endl;

}

void Solver::alt(){
    Planet current = m_listPlanets.at(0); // m_planets[i];

    velocityVerlet(current.position,  current.velocity);

    //velocityVerlet(planet_i.position, planet_i.velocity);
}


void Solver::euler(mat& position,mat& velocity, double timeLimit, double integrationPoints){
    // Euler-Cromer method:
    /*double r;
    mat a = vec({0,0});

    double fourpi2 = 4*M_PI*M_PI;

    double time = 0;
    double dt = timeLimit/integrationPoints;
    double r;

    ofstream outfile("../../results/euler.txt");
    for (unsigned int i=0; i < m_listPlanets.size(); i++) {
        //Question: take out loop over sun? Is one extra loop....
        Planet current = m_listPlanets.at(i); // m_planets[i];

        current.acceleration(position,acleration, 2, distance);
        // Question: fix relative distance between two different planets

        current.relativeDistance(position, 2, r); // (position, dimension, distance)
        current.acceleration(position, acleration, 2,distance); //(mat& position, mat& aks, int dimension, double absDistance );
        while(time<=timeLimit){

            a = (-fourpi2/pow(r,3))*position;
            velocity += dt*a;
            position = position + dt*velocity;
            writePosition(outfile, position, position, 2, time);

            time = time + dt;
        }

        cout << "Euler:" << endl;
        cout << "Position: " << "(" << x << " , " << y << " ) " << endl;
        cout << "Velocity: " << "(" << vx << " , " << vy << " ) " << endl;

    }
    */
}

