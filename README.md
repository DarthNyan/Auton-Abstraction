# Auton-Abstraction

###These files contain modules of varying levels of complexity to build 4886T's autonomous abstraction from tipping point.


######Setup
Download the files and reconfigure your motors to the ports they're plugged in. You need at least DriveLB and DriveRB, and if you have 4 or 6 motors on your drive you can also reconfigure DriveLM, DriveLF, DriveRM, and DriveRF. The motors' direction is configured as though the motor drives a pinion driving the wheel - the motor spins in the opposite direction as the wheel. If your motors spin in the same direction as the wheel, such as direct drive or chain drive, you will need to flip the "reversed" slider on all of them. If your gearboxes are 200rpm or 100rpm, you will also need to change that.

You will also need a vex inertial sensor for modules 4-6.

In the "robot-specific-defs.h" file are a number of values specific to each robot. They are configured for my drive chassis, which uses 4 inch wheels geared down 3:7 from the motors and are 12 inches apart, you will need to set your WHEEL_CIRCUMFRENCE, INPERSEC_TO_RPM (which is just 60/WHEEL_CIRCUMFRENCE), ENCODER_TO_WHEEL gear ratio (1 for direct drive), and WHEEL_TO_WHEEL_DIST to fit your own robot.

DRIVE_KP and STEERING_KP are PID constants that will want to be fine tuned for optimal performance, but should run decently without adjustment on most bots.

####The modules introduce the following topics and build on the previous:

######Module 0:
Most basic, "Drive forward a certain number of degrees then stop"

######Module 1:
Friendly units (inches, seconds), following a target

######Module 2:
Acceleration and deceleration, driving backward

######Module 3:
Using the inertial sensor, wrap detection and unwrapping

######Module 4:
Turning and arcing at a given radius

######Module 5:
Turning and arcing in reverse

######Module 6:
Correcting steering while driving straight.
