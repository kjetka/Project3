#ifndef SOLVER_H
#define SOLVER_H
#include <ctime>
#include <ratio>
#include <chrono>

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
        int numberOfSteps;
        double dt;
        double timeLimit;
        double dt_half;
        int numberOfPlanets;
        string systemtype;
        bool choiseOfMethod;
        double energy_prev;
        double stepsPerYear;

    public:
        friend class Planet;

        vector<Planet> m_listPlanets;
        Solver(string systemtype_, bool choiseOfMethod, double timelimit, double stepsPerYear_);
        void add(Planet thisplanet);

        void velocityVerlet(Planet &current, double beta);
        void Euler(Planet &currentplanet, double beta);


        void algorithm(bool printfile, double beta);

        void updateTotalAcceleration_potEN(Planet &currentPlanet, double beta);
        void updateVelocity(Planet &currentPlanet);
        void updatePosition(Planet &currentPlanet);
        void updateTotalAcceleration(Planet &currentPlanet);
        void check_convergence(double eps, double &dt);

        void test_energy( Planet current);
        void test_circular(Planet current, double time);
        void test_angularmoment(Planet current);

        void findingPerihelion(Planet &current);
        mat find_center_of_mass();


        //void writeAllPlanetsPosition(ofstream &outfile, double time);
        void writevalues(ofstream& outfile, Planet& current, double time);
        void writeheader(ofstream& outfile, int dimension);
        void initializeFiles(ofstream *outFiles, string nameinfo);

};

#endif // SOLVER_H
