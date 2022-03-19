using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor DriveLB;
extern motor DriveLM;
extern motor DriveLF;
extern motor DriveRB;
extern motor DriveRM;
extern motor DriveRF;
extern inertial Gyro;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );