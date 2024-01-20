#include "main.h"

// Variables
extern Gif logo;
extern bool first_run;
extern double fw_output;
extern double target_fw_rpm;
extern bool liftRaised;
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

extern pros::Motor flywheel;
extern pros::Motor intake;

// Motor Groups
extern pros::Motor_Group driveLeft;
extern pros::Motor_Group driveRight;

// ADI Digital Outputs
extern pros::ADIDigitalOut wingLeft;
extern pros::ADIDigitalOut wingRight;
extern pros::ADIDigitalOut liftRachetLeft;
extern pros::ADIDigitalOut liftRachetRight;
extern pros::ADIDigitalOut lift;
// Limit switch in port D

// Inertial Sensor
extern pros::Imu imu;

// LemLib chassis object
extern lemlib::Chassis chassis;
