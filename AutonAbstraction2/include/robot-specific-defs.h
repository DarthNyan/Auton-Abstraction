
// translation between wheels and encoders
#define WHEEL_CIRCUMFERENCE 13.2
#define INPERSEC_TO_RPM (60/WHEEL_CIRCUMFERENCE)
#define ENCODER_TO_WHEEL ((float)3/7)

// PID constants
#define DRIVE_KP 20


// useful constants and renamings
#define pi 3.14159
#define vexTimer vex::timer::system()
#define FIFTIETH_SECOND 20
#define FULL_SECOND 1000


// function prototypes
void Drive(int lrpm, int rrpm);
void DriveStraight(float dist, float maxVel, float accel);
float stopDistance(float vel, float accel);