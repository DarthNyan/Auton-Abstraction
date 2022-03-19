
// translation between wheels and encoders
#define WHEEL_CIRCUMFERENCE 13.2
#define INPERSEC_TO_RPM (60/WHEEL_CIRCUMFERENCE)
#define ENCODER_TO_WHEEL ((float)3/7)

// PID constants
#define DRIVE_KP 20

//gyro constants
#define GYRO_MARIGIN_ROLLOVER 300
#define DEG_PER_TURN 360

// useful constants and renamings
#define pi 3.14159
#define vexTimer vex::timer::system()
#define FIFTIETH_SECOND 20
#define FULL_SECOND 1000

//extern global variables
extern int gyroOffset;

// function prototypes
void Drive(int lrpm, int rrpm);
void DriveStraight(float dist, float maxVel, float accel);
float stopDistance(float vel, float accel);
int gyroAbsPos();