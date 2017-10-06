#ifndef SOLVER_H
#define SOLVER_H
#include <cmath>
#include <vector>
#include <iostream>
#include <armadillo>
using namespace std;
using namespace arma;


class Solver {
private:
    double m_pi;

public:
    Solver();
    //inline double pi(){return  acos(-1.0);};

    void euler(double x, double y, double vx, double vy, double timelimit, double integration_points);

    void writePosition(std::ofstream &output, mat r,mat v,  int dim, double time);


};

#endif // SOLVER_H
