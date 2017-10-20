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
        int numberOfPlanets;
        string systemtype;

    public:
        vector<Planet> m_listPlanets;
        //vector<string> outfile_list;

        Solver(string systemtype_);
        //Planet();
        friend class Planet;
        void velocityVerlet(Planet &current);

        void add(Planet thisplanet);
        void writePosition(ofstream &outfile, mat &r, mat &v, int dimension, double time);
        void writeheader(ofstream& outfile, int dimension);
        void initializeFiles(ofstream *outFiles, string nameinfo);
        void algorithm();
        void test_algorithm();
        void Euler(Planet &currentplanet);
        void updateTotalAcceleration(Planet &currentPlanet);
        void pretests();
        void find_velocity();


};

#endif // SOLVER_H
