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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  LeftDriveSmart.setStopping(coast);
  RightDriveSmart.setStopping(coast);

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


 // Drivetrain.setDriveVelocity(50, percent); // Prevent drift with lower speeds
 // Drivetrain.setTurnVelocity(50, percent);
 // Drivetrain.driveFor(6, inches);
  // LeftDriveSmart.spin(forward); // Start the use of an inertial sensor
  // RightDriveSmart.spin(reverse); // starts turning the robot by moving one side back and one side forward
  // Waits until the motor reaches a 90 degree turn and stops the Left and
  // Right Motors.
  //waitUntil((Inertial.rotation(degrees) <= 45.0)); // while loop to control the bot movement
  //LeftDriveSmart.stop(); // Stops the motors once the angle is passed
  //RightDriveSmart.stop();
  //Drivetrain.driveFor(20, inches);
  //ClawMotor.spinFor(-80, degrees);// Clamps claw down
  //ClawMotor.setStopping(brake);// Keeps claw in place
  //ArmMotors.spinFor(90, degrees);
  //ArmMotors.stop(brake);
  //Drivetrain.setDriveVelocity(80, percent);
  //Drivetrain.driveFor(-20, inchZ

  // ClawMotor.stop(brake);
  // Drivetrain.setDriveVelocity(50, percent);
  // Drivetrain.setTurnVelocity(50, percent);
  // Drivetrain.driveFor(6, inches);
  // Drivetrain.turnFor(70,degrees);
  // Drivetrain.driveFor(20, inches);
  // ClawMotor.spinFor(-180, degrees);
  // ClawMotor.setStopping(brake);
  // ArmMotors.spinFor(90, degrees);
  // ArmMotors.stop(brake);
  // // Drivetrain.driveFor(-10, inches);
  // Drivetrain.turnFor(-240, degrees);

  ClawMotor.rotateTo(120, degrees);
  Drivetrain.setDriveVelocity(90, percent);
  Drivetrain.setTurnVelocity(30, percent);
  Drivetrain.driveFor(58, inches);
  Drivetrain.setDriveVelocity(40, percent);
  Drivetrain.driveFor(6, inches);
  wait(100, msec);
  
  ClawMotor.setStopping(brake);
  ClawMotor.rotateTo(30, degrees);
  //ArmMotors.rotateTo(90, degrees);
  Drivetrain.setDriveVelocity(90, percent);
  Drivetrain.driveFor(-57, inches);
  ClawMotor.setStopping(hold);

 
 


  
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
