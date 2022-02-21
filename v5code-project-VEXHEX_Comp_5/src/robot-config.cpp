#include "vex.h"
#include<cmath>

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT1, ratio18_1, true);
motor leftMotorB = motor(PORT3, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT9, ratio18_1, false);
motor rightMotorB = motor(PORT10, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 259.34, 295, 40, mm, 2.3333333333333);
controller Controller1 = controller(primary);
motor ArmMotorsMotorA = motor(PORT2, ratio36_1, true);
motor ArmMotorsMotorB = motor(PORT4, ratio36_1, false);
motor_group ArmMotors = motor_group(ArmMotorsMotorA, ArmMotorsMotorB);
motor ClawMotor = motor(PORT20, ratio36_1, false);
inertial Inertial = inertial(PORT5);
motor BackClawMotor = motor(PORT11, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
bool Controller1ButtonsXBControlMotorsStopped = true;

// bool DriveDirectionSwitched = false;

int BCrotateUp() {
  BackClawMotor.rotateTo(0, degrees);

  return 1;
}

int BCrotateDown() {
  BackClawMotor.rotateTo(-490, degrees);

  return 1;
}


int logarithmic(int speed) {
  int sign = speed / std::abs(speed);
  int l_speed = sign * speed * speed / 127;

  return l_speed;
}

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int temp1 = logarithmic(Controller1.Axis1.position()) / 2;
      int temp3 = logarithmic(Controller1.Axis3.position());

      int drivetrainLeftSideSpeed = temp3 + temp1;
      int drivetrainRightSideSpeed = temp3 - temp1;
      
      /*
      if (DriveDirectionSwitched) {
        drivetrainLeftSideSpeed = Controller1.Axis1.position() - Controller1.Axis3.position();
        drivetrainRightSideSpeed = 0 - Controller1.Axis3.position() - Controller1.Axis1.position();
      }
      */

      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
      // check the ButtonL1/ButtonL2 status to control ArmMotors
      if (Controller1.ButtonL1.pressing()) {
        if (ArmMotors.rotation(degrees) < 400) {
          ArmMotors.spin(forward);
          Controller1LeftShoulderControlMotorsStopped = false;
        }
      } else if (Controller1.ButtonL2.pressing()) {
        if (ArmMotors.rotation(degrees) > 0) {
          ArmMotors.spin(reverse);
          Controller1LeftShoulderControlMotorsStopped = false;
        }
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        ArmMotors.setStopping(hold);// Locks the arms when button is released
        ArmMotors.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }

      // check the ButtonR1/ButtonR2 status to control ClawMotor
      if (Controller1.ButtonR1.pressing()) {
        if (ClawMotor.rotation(degrees) < 70) {
          ClawMotor.spin(forward);
          Controller1RightShoulderControlMotorsStopped = false;
        }
      } else if (Controller1.ButtonR2.pressing()) {
        if (ClawMotor.rotation(degrees) > 40) {
          ClawMotor.spin(reverse);
          Controller1RightShoulderControlMotorsStopped = false;
        }
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        ClawMotor.setStopping(hold);
        ClawMotor.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
      // check the ButtonX/ButtonB status to control BackClawMotor
      if (Controller1.ButtonY.pressing()) {
        if (BackClawMotor.rotation(degrees) < 20) {
          BackClawMotor.spin(forward);
          Controller1ButtonsXBControlMotorsStopped = false;
        }
      } else if (Controller1.ButtonRight.pressing()) {
        if (BackClawMotor.rotation(degrees) > -480) {
          BackClawMotor.spin(reverse);
          Controller1ButtonsXBControlMotorsStopped = false;
        }
      } else if (!Controller1ButtonsXBControlMotorsStopped) {
        BackClawMotor.stop();
        BackClawMotor.setStopping(hold);// Locks the arms when button is released
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1ButtonsXBControlMotorsStopped = true;
      }

      if (Controller1.ButtonB.pressing()) {
        task BCrotateUp_task(BCrotateUp);
      } else if (Controller1.ButtonDown.pressing()) {
        task BCrotateDown_task(BCrotateDown);
      }

      Brain.Screen.print(ClawMotor.rotation(degrees));
      
    }

    /*
    if (Controller1.ButtonB.pressing()) {
      DriveDirectionSwitched = false;
    } else if (Controller1.ButtonDown.pressing()) {
      DriveDirectionSwitched = true;
    }
    */

    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}
