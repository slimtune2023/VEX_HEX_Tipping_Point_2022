/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include<cmath>
#include<iostream>
#include<Autonomous.h>

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void calibrateInertial() {
  Inertial.calibrate();
  while (Inertial.isCalibrating()) {
    wait(100, msec);
  }
}

void driveSetStopping(brakeType b) {
  LeftDriveSmart.setStopping(b);
  RightDriveSmart.setStopping(b);
}

void temperatures() {
  Brain.Screen.setCursor(1, 1);

  Brain.Screen.print("LeftDriveSmart temperature: ");
  Brain.Screen.print(LeftDriveSmart.temperature());
  Brain.Screen.newLine();

  Brain.Screen.print("RightDriveSmart temperature: ");
  Brain.Screen.print(RightDriveSmart.temperature());
  Brain.Screen.newLine();

  Brain.Screen.print("ArmMotors temperature: ");
  Brain.Screen.print(ArmMotors.temperature());
  Brain.Screen.newLine();

  Brain.Screen.print("ClawMotor temperature: ");
  Brain.Screen.print(ClawMotor.temperature());
  Brain.Screen.newLine();

  Brain.Screen.print("BackClawMotor temperature: ");
  Brain.Screen.print(BackClawMotor.temperature());
  Brain.Screen.newLine();
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  calibrateInertial();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Autonomous auton;

  wait(50, msec);

  auton.drivePID.setMax(100);
  auton.openClaw(false);
  wait(50, msec);
  auton.driveForD(46.0);
  wait(50, msec);
  auton.closeClaw(true);
  wait(50, msec);
  auton.driveFast(-46);


}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
