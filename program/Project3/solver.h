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

        void updateTotalAcceleration_andPotEnergy(Planet &currentPlanet, double beta);
        void updateVelocity(Planet &currentPlanet);
        void updatePosition(Planet &currentPlanet);
        void updateTotalAcceleration(Planet &currentPlanet);
        void checkConvergence(double eps, double &dt);

        void testEnergy( Planet current);
        void testCircular(Planet current, double time);
        void testAngularmoment(Planet current);

        void findingPerihelion(Planet &current, double time);
        mat findCenterOfMass();


        //void writeAllPlanetsPosition(ofstream &outfile, double time);
        void writeValues(ofstream& outfile, Planet& current, double time);
        void writeHeader(ofstream& outfile, int dimension);
        void initializeFiles(ofstream *outFiles, string nameinfo);

};

#endif // SOLVER_H
