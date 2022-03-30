#include "vex.h"
#include<cmath>
#include<Autonomous.h>

using namespace vex;

Autonomous::Autonomous() : turnPID(1.0, 0.0, 0.0, 50, 0.1), drivePID(0.25, 0.0, 0.75, 50, 10), balancePID(0.5, 0.0, 0.5, 30, 0.1) {
  turnPID.reset();
  drivePID.reset();
  balancePID.reset();
  setUp();
}

int BCrotateUp1() {
  BackClawMotor.rotateTo(0, degrees);

  return 1;
}

int BCrotateDown1() {
  BackClawMotor.rotateTo(-535, degrees);

  return 1;
}

void Autonomous::rotateBackClawUp(bool wait) {
  if (wait) {
    BackClawMotor.rotateTo(0, degrees);
  } else {
    task BCrotateUp_task1(BCrotateUp1);
  }
}

void Autonomous::rotateBackClawDown(bool wait) {
  if (wait) {
    BackClawMotor.rotateTo(-535, degrees);
  } else {
    task BCrotateDown_task1(BCrotateDown1);
  }
}

void Autonomous::rotateBackClaw(int degees) {
  BackClawMotor.rotateTo(degees, degrees);
}

double Autonomous::angleTransform(double angel, double target) {
  while ((angel > (target + 180)) && (angel < (target - 180))) {
    if ((target + 180) < angel) {
      angel -= 360;
    } else if ((target - 180) > angel) {
      angel += 360;
    }
  }
  
  return angel;
}

void Autonomous::turnTo(double degees) {
  turnPID.reset();
  
  double errorB = turnPID.getErrorBound();

  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(reverse);

  int time = 0;

  while (std::abs(angleTransform(Inertial.heading(), degees) - degees) > errorB) {
    double v = turnPID.calculate(angleTransform(Inertial.heading(), degees), degees);

    LeftDriveSmart.setVelocity(-v, percent);
    RightDriveSmart.setVelocity(v, percent);

    time += 1;

    if (time > 100) {
      break;
    }


    wait(20, msec);
  }

  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

void Autonomous::turnBy(double degees) {
  double initDegrees = Inertial.heading();

  turnTo(initDegrees + degees);
}

void Autonomous::driveForD(double dist) {
  double wheelDiam = 3.25 * 5 / 3;
  double degees = dist / (M_PI * wheelDiam) * 360;
  drivePID.reset();
  LeftDriveSmart.resetRotation();
  RightDriveSmart.resetRotation();

  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);

  double errorB = drivePID.getErrorBound();

  while (std::abs(degees - LeftDriveSmart.rotation(degrees)) > errorB) {
    double v = drivePID.calculate(LeftDriveSmart.rotation(degrees), degees);

    LeftDriveSmart.setVelocity(-v, percent);
    RightDriveSmart.setVelocity(-v, percent);

    wait(20, msec);
  }

  LeftDriveSmart.stop();
  RightDriveSmart.stop();

}

void Autonomous::driveFast(double dist) {
  double wheelDiam = 3.25 * 5 / 3;
  double degees = dist / (M_PI * wheelDiam) * 360;
  drivePID.reset();
  LeftDriveSmart.resetRotation();
  RightDriveSmart.resetRotation();

  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);

  double errorB = drivePID.getErrorBound();
  bool b = true;

  LeftDriveSmart.setVelocity(dist / std::abs(dist) * 80, percent);
  RightDriveSmart.setVelocity(dist / std::abs(dist) * 80, percent);

  while (std::abs(degees - LeftDriveSmart.rotation(degrees)) > errorB) {

    if (std::abs(degees - LeftDriveSmart.rotation(degrees)) < 100 && b) {
      b = false;

      LeftDriveSmart.setVelocity(dist / std::abs(dist) * 50, percent);
      RightDriveSmart.setVelocity(dist / std::abs(dist) * 50, percent);

    }

    wait(20, msec);
  }

  LeftDriveSmart.setStopping(hold);
  RightDriveSmart.setStopping(hold);
  LeftDriveSmart.stop();
  RightDriveSmart.stop();

}

void Autonomous::balance() {
  balancePID.reset();

  LeftDriveSmart.setStopping(coast);
  RightDriveSmart.setStopping(coast);

  driveForD(4.0);

  LeftDriveSmart.spin(forward);
  RightDriveSmart.spin(forward);
  
  double errorB = balancePID.getErrorBound();

  int time = 0;

  while (std::abs(Inertial.pitch()) > errorB) {
    double v = turnPID.calculate(Inertial.pitch(), 0.0);

    LeftDriveSmart.setVelocity(v, percent);
    RightDriveSmart.setVelocity(v, percent);

    time += 1;

    if (time > 1000) {
      break;
    }


    wait(20, msec);
  }

  LeftDriveSmart.stop();
  RightDriveSmart.stop();
}

int ArmRotateUp1() {
  ArmMotors.rotateTo(372.0, degrees);

  return 1;
}

int ArmRotateDown1() {
  ArmMotors.rotateTo(0, degrees);

  return 1;
}

void Autonomous::rotateArmUp(bool wait) {
  if (wait) {
    ArmMotors.rotateTo(372.0, degrees);
  } else {
    task ArmRotateUp_task1(ArmRotateUp1);
  }
}

void Autonomous::rotateArmDown(bool wait) {
  if (wait) {
    ArmMotors.rotateTo(60, degrees);
  } else {
    task ArmRotateDown_task1(ArmRotateDown1);
  }
}

void Autonomous::rotateArm(int degees) {
  ArmMotors.rotateTo(degees, degrees);
}

int ClawClose1() {
  ClawMotor.rotateTo(40.00, degrees);

  return 1;
}

int ClawOpen1() {
  ClawMotor.rotateTo(140.00, degrees);

  return 1;
}

void Autonomous::closeClaw(bool wait) {
  if (wait) {
    ClawMotor.rotateTo(40.00, degrees);
  } else {
    task ClawClose_task1(ClawClose1);
  }
}

void Autonomous::openClaw(bool wait) {
  if (wait) {
    ClawMotor.rotateTo(140.00, degrees);
  } else {
    task ClawOpen_task1(ClawOpen1);
  }
}

void Autonomous::setUp() {
  ClawMotor.setStopping(hold);
  ArmMotors.setStopping(hold);
  LeftDriveSmart.setStopping(brake);
  RightDriveSmart.setStopping(brake);
  BackClawMotor.setStopping(hold);
}