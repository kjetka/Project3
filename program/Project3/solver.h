#ifndef SOLVER_H
#define SOLVER_H
#include "planet.h"
#include <vector>


    void euler(double x, double y, double vx, double vy, double timelimit, double integration_points);
    void writePosition(std::ofstream &output, mat r,mat v,  int dim, double time);
class Solver
{
    private:
        double m_pi;
        double fourpi2;

        double time;
        int numberofsteps;
        double dt;
        double timeLimit;
        double dt_half;

        std::vector<Planet*> m_planets;

    public:
        Solver();
        //Planet();
        void velocity(double &vx, double &vy, double ax, double ay);
        void velocityVerlet(double &x, double &y, double &vx, double &vy);

        void addPlanet(Planet* p);
};

#endif // SOLVER_H
