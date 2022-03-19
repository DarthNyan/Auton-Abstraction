#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor DriveLB = motor(PORT15, ratio6_1, true);
motor DriveLM = motor(PORT17, ratio6_1, true);
motor DriveLF = motor(PORT14, ratio6_1, true);
motor DriveRB = motor(PORT12, ratio6_1, false);
motor DriveRM = motor(PORT16, ratio6_1, false);
motor DriveRF = motor(PORT11, ratio6_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}