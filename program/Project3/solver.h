#ifndef SOLVER_H
#define SOLVER_H
#include "planet.h"
#include <vector>

using namespace std;

    void euler(double x, double y, double vx, double vy, double timelimit, double integration_points);
    void writePosition(std::ofstream &output, mat r,mat v,  int dim, double time);
class Solver
{
    private:
        double pi;
        double fourpi2;
        //double time;
        int numberofsteps;
        double dt;
        double timeLimit;
        double dt_half;


    public:
        vector<Planet> m_listPlanets;
        //vector<string> outfile_list;

        Solver();
        //Planet();
        friend class Planet;
        void velocityVerlet(Planet &current);

        void add(Planet thisplanet);
        void writePosition(ofstream &outfile, mat &r, mat &v, int dimension, double time);
        void algorithm();
        void test_algorithm();
        void Euler(Planet &currentplanet);
        void totalAcceleration(Planet &currentPlanet);
        void totalVelocity(Planet &currentPlanet);
        void totalPosition(Planet &currentPlanet);
        void writeAllPlanetsPosition(ofstream &outfile, double time);
};

#endif // SOLVER_H
