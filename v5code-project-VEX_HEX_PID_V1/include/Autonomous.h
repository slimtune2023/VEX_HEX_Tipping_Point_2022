#include "vex.h"
#include<cmath>
#include<PID.h>

using namespace vex;

class Autonomous {
  public:
    Autonomous();

    void rotateBackClawDown(bool wait);
    void rotateBackClawUp(bool wait);
    void rotateBackClaw(int degees);

    void rotateArmUp(bool wait);
    void rotateArmDown(bool wait);
    void rotateArm(int degees);

    void openClaw(bool wait);
    void closeClaw(bool wait);

    void turnBy(double degees);
    void turnTo(double degees);
    double angleTransform(double angel, double target);
    void turnByBad(double degees);
    void driveForD(double dist);
    void driveFast(double dist);
    void balance();

    void setUp();

    PID turnPID;
    PID drivePID;
    PID balancePID;

};