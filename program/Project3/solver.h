#ifndef SOLVER_H
#define SOLVER_H


class Solver
{
    private:
        double pi;
        double fourpi2;

        double time;
        int numberofsteps;
        double dt;
        double timeLimit;
        double dt_half;

    public:
        Solver();
        Planet();
        void velocity(double &vx, double &vy, double ax, double ay);
        void velocityVerlet(double &x, double &y, double &vx, double &vy);
};

#endif // SOLVER_H
