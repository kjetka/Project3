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
        double fourpi2;

        double time;
        int numberofsteps;
        double dt;
        double timeLimit;
        double dt_half;


    public:
        vector<Planet> m_listPlanets;

        Solver();
        //Planet();
        void velocity_update(mat &v, mat &a);
        void velocityVerlet(mat& position, mat& velocity);

        void add(Planet thisplanet);
        void writePosition(ofstream &outfile, mat &r, mat &v, int dimension, double time);
        void alt();
};

#endif // SOLVER_H
