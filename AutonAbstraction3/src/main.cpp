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
// DriveLB              motor         14              
// DriveLM              motor         17              
// DriveLF              motor         15              
// DriveRB              motor         11              
// DriveRM              motor         16              
// DriveRF              motor         12              
// Gyro                 inertial      3               
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

  //calibrate the inertial sensor. It MUST remain motionless for 2 seconds once you run the program
  Gyro.calibrate();
  wait(2, sec);

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
  
  //Increment gyroOffset by gyroAbsPos.
  //This makes it so gyroAbsPos returns the position since the start of last auton run
  //without this, 0 would be the direction your robot faces when the program starts,
  //not the direction it faces when autonomous starts.
  gyroOffset += gyroAbsPos();
  
  while(true)
  {
    //clear the screen and reset the cursor
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    //print the current yaw of your robot
    Brain.Screen.print(gyroAbsPos());

    //wait to prevent wasted resources.
    wait(20, msec);
  }
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

//drive straight. Arguments use inches and seconds.
//dist can be positive or negative for forward and backward
//maxVel and accel should be positive
void DriveStraight(float dist, float maxVel, float accel)
{
  //initialize variables
  int lStart = DriveLB.position(turns); 
  int rStart = DriveRB.position(turns);
  int lPosition = 0, rPosition = 0;
  
  float vel = 0, pos = 0;
  
  int currentTick = vexTimer, tickLength = FIFTIETH_SECOND, ticksPerSecond = FULL_SECOND / tickLength;
  
  // if going forward
  if (dist > 0)
  {
    //while going forward
    while (vel >= 0) 
    {
      //get encoder positions in inches
      lPosition = (DriveLB.position(turns) - lStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
      rPosition = (DriveRB.position(turns) - rStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
      
      //if the distance we've traveled plus the distance to stop reaches the target dist,
      if (pos + stopDistance(vel, accel) >= dist) 
      {
        //it's time to deccelerate. Divide by ticksPerSecond because the loop iterates 50x/s
        vel -= accel / ticksPerSecond; 
      }
      //else, if we're not at maximum velocity yet, accelerate
      else if (vel < maxVel) 
      {
        vel += accel / ticksPerSecond;
      }
      else vel = maxVel;

      //increment position by velocity. Again divide by FIFTIETH_SECOND
      pos += vel / ticksPerSecond; 
      
      //spin the motors.
      Drive(vel * INPERSEC_TO_RPM/ENCODER_TO_WHEEL //velocity in in/s converted to rpm
              + DRIVE_KP * (pos - lPosition), //p loop to keep near position target
            vel * INPERSEC_TO_RPM/ENCODER_TO_WHEEL //right side is same as left
              + DRIVE_KP * (pos - rPosition));

      //wait until a fiftieth of a second has passed since the last iteration.
      //because it might take time to do everything above, this gives more precise loop times.
      currentTick += tickLength; 
      while(vexTimer < currentTick) {}
    }
  }
  //going reverse
  else if(dist < 0)
  {
    //while going reverse
    while (vel <= 0) 
    {
      //get encoder positions in inches
      lPosition = (DriveLB.position(turns) - lStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
      rPosition = (DriveRB.position(turns) - rStart) * ENCODER_TO_WHEEL * WHEEL_CIRCUMFERENCE;
      
      //if the distance we've traveled plus the distance to stop reaches the target dist,
      //dist and pos are both negative now, but stopDistance is positive, so subtract stopDistance
      if (pos - stopDistance(vel, accel) <= dist) 
      {
        //it's time to deccelerate. Divide by FIFTIETH_SECOND because the loop iterates 50x/s
        //since vel is negative here, increase its value to decelerate
        vel += accel / ticksPerSecond; 
      }
      //else, if we're not at maximum velocity yet, accelerate
      else if (vel > -maxVel) 
      {
        vel -= accel / ticksPerSecond;
      }
      else vel = -maxVel;

      //increment position by velocity. Again divide by FIFTIETH_SECOND
      //since vel is negative and we want pos to be negative, we can add like normal here
      pos += vel / ticksPerSecond; 
      
      //spin the motors.
      Drive(vel * INPERSEC_TO_RPM/ENCODER_TO_WHEEL //velocity in in/s converted to rpm
              + DRIVE_KP * (pos - lPosition), //p loop to keep near position target
            vel * INPERSEC_TO_RPM/ENCODER_TO_WHEEL //right side is same as left
              + DRIVE_KP * (pos - rPosition));

      //wait until a fiftieth of a second has passed since the last iteration.
      //because it might take time to do everything above, this gives more precise loop times.
      currentTick += tickLength; 
      while(vexTimer < currentTick) {}
    }
  }
  //stop the drive
  Drive(0, 0);
}
float stopDistance(float vel, float accel)
{
  //recall from physics that V² = V0² + 2a(x-x0)
  //substituting 0 in for V, we find x-x0 = -V0²/2a
  return vel*vel / (2*accel);
}

//Gyro.orientation(yaw, degrees) overflows from 180 to -179 and vice versa.
//this returns the gyro's absolute yaw in degrees. Use instead of Gyro.orientation
int GyroRollOvers = 0, PreviousGyro = 0, CurrentGyro, gyroOffset = 0;
int gyroAbsPos()
{
  CurrentGyro = Gyro.orientation(yaw, degrees);

  //if the difference between the current gyro position and the previous > 300, gyro has rolled from -179 to 180
  //decrement gyroRollOvers because gyro is turning in negative direction
  if(CurrentGyro - PreviousGyro > GYRO_MARIGIN_ROLLOVER) GyroRollOvers --;
  //same line of thinking for rolling from 180 to -179
  else if(CurrentGyro - PreviousGyro < -GYRO_MARIGIN_ROLLOVER) GyroRollOvers ++;
  PreviousGyro = CurrentGyro;

  //returns the absolute yaw of the gyro in degrees.
  return (CurrentGyro + GyroRollOvers * DEG_PER_TURN) - gyroOffset;

}