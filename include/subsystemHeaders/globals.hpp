#include "main.h"

// Variables
extern bool show_logo;
extern Gif gif;
extern double fw_output;
extern double target_fw_rpm;

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

// Pneumatic Pistons
extern pros::ADIDigitalOut lift;
extern pros::ADIDigitalOut wingRight;
extern pros::ADIDigitalOut wingLeft;
extern pros::ADIDigitalOut liftRachet;

// Inertial Sensor
extern pros::Imu imu;

// LemLib chassis object
extern lemlib::Chassis chassis;
