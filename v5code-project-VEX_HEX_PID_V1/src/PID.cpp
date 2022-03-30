#include<cmath>
#include<iostream>
#include<PID.h>

// PID::PID(double P, double I, double D, double maxP, double errorB) {
//   kP = P;
//   kI = I;
//   kD = D;
//   maxPower = std::abs(maxP);
//   errorBound = errorB;
// }

double PID::calculate(double sensor, double target) {
  achievedTarget = false;
  double error = sensor - target;
  double power = kP * error + kD * (error - prevError) + kI * totalError;

  if (std::abs(power) > maxPower) {
    power = maxPower * power / std::abs(power);
  }

  if (!((std::abs(power) == maxPower) && ((power / error) > 0))) {
    totalError += error;
  }

  prevError = error;

  if (std::abs(sensor - target) < errorBound) {
    totalError = 0.0;
    achievedTarget = true;
  }

  return power;
}

bool PID::atTarget() {
  return achievedTarget;
}

void PID::reset() {
  prevError = 0.0;
  totalError = 0.0;
  achievedTarget = false;
}

double PID::getErrorBound() {
  return errorBound;
}

void PID::setMax(double max) {
  maxPower = max;
}