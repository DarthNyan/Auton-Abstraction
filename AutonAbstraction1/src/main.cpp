/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DriveLB              motor         15              
// DriveLM              motor         17              
// DriveLF              motor         14              
// DriveRB              motor         12              
// DriveRM              motor         16              
// DriveRF              motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-specific-defs.h"

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
  DriveStraight(45, 30);
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

//basic "spin the motors" command. Takes arguments in rpm
void Drive(int lrpm, int rrpm)
{
  DriveLB.spin(forward, lrpm, rpm);
  DriveLM.spin(forward, lrpm, rpm);
  DriveLF.spin(forward, lrpm, rpm);
  DriveRB.spin(forward, rrpm, rpm);
  DriveRM.spin(forward, rrpm, rpm);
  DriveRF.spin(forward, rrpm, rpm);
}

//drive straight. Arguments use inches and seconds
void DriveStraight(float dist, float speed)
{
  //initialize variables
  float lStart = DriveLB.position(turns);
  float rStart = DriveRB.position(turns);
  float lPosition = 0, rPosition = 0, targetPosition = 0;

  int ticksPerSecond = FULL_SECOND / FIFTIETH_SECOND;

  //while not at target yet
  while (targetPosition < dist)
  {
    //get encoder positions in inches
    lPosition = (DriveLB.position(turns) - lStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
    rPosition = (DriveRB.position(turns) - rStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
    
    //increment target by speed. 
    //Divide by ticks per second because this loop runs 50x per second
    //This way, the target increments by speed every second 
    targetPosition += speed / ticksPerSecond;

    //spin the motors
    Drive(speed * INPERSEC_TO_RPM/ENCODER_TO_WHEEL
            + DRIVE_KP * (targetPosition - lPosition), 
          speed * INPERSEC_TO_RPM/ENCODER_TO_WHEEL
            + DRIVE_KP * (targetPosition - rPosition));

    //wait a fiftieth of a second
    wait(FIFTIETH_SECOND, msec);
  }
  //stop the drive at the end
  Drive(0, 0);
}