
// translation between wheels and encoders
#define WHEEL_CIRCUMFERENCE 13.2
#define INPERSEC_TO_RPM (60/WHEEL_CIRCUMFERENCE)
#define ENCODER_TO_WHEEL ((float)3/7)

//distance between wheels
#define WHEEL_TO_WHEEL_DIST 12

// PID constants
#define DRIVE_KP 20
#define STEERING_KP 150

//gyro constants
#define GYRO_MARIGIN_ROLLOVER 300
#define DEG_PER_TURN 360

// useful constants and renamings
#define pi 3.14159
#define RAD_TO_DEG (180/pi)
#define DEG_TO_RAD (pi/180)
#define vexTimer vex::timer::system()
#define FIFTIETH_SECOND 20
#define FULL_SECOND 1000

//extern global variables
extern int gyroOffset;
extern int xCursor;
extern float currentHeading;

// function prototypes
void Drive(int lrpm, int rrpm);
void DriveStraight(float dist, float maxVel, float accel);
void DriveTurn(float radians, float outerRadius, float maxVel, float accel, bool reversed = false);
void HoldHeading(int duration);
float stopDistance(float vel, float accel);
int gyroAbsPos();
void GraphDebuggerVars(int Red, int Blue = 0, int Green = 0, int Purple = 0, int Orange = 0, int Yellow = 0);