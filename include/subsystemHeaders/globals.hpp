#include "main.h"

// Variables
extern Gif far;
extern Gif close;
extern Gif skills;
extern Gif easter_egg;
extern Gif logo;
extern bool first_run;
extern int auton;

// Controllers
extern pros::Controller controller;

// Motors
extern pros::Motor driveLeftFront;
extern pros::Motor driveMiddleLeft;
extern pros::Motor driveLeftBack;
extern pros::Motor driveRightFront;
extern pros::Motor driveMiddleRight;
extern pros::Motor driveRightBack;

extern pros::Motor puncher;
extern pros::Motor intake;

// Motor Groups
extern pros::Motor_Group driveLeft;
extern pros::Motor_Group driveRight;

// ADI Digital Outputs
extern pros::ADIDigitalOut wingBackLeft;
extern pros::ADIDigitalOut wingBackRight;
extern pros::ADIDigitalOut wingFrontLeft;
extern pros::ADIDigitalOut wingFrontRight;
extern pros::ADIDigitalOut lift;
// Limit switch in port D

// Inertial Sensor
extern pros::Imu imu;
extern pros::Rotation rotationSensor;

// LemLib chassis object
extern lemlib::Chassis chassis;
