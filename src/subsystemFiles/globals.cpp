#include "main.h"

// Variables
static Gif logo("/usd/logo_stretched.gif", lv_scr_act());
Gif activeGif = logo;
bool first_run = true;
int auton = 1;

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor driveLeftFront(2, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveMiddleLeft(3, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(4, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveMiddleRight(5, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(20, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor puncher(17, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(6, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);

// Motor Groups
pros::Motor_Group driveLeft({driveLeftFront, driveLeftBack, driveMiddleLeft});
pros::Motor_Group driveRight({driveRightFront, driveRightBack, driveMiddleRight});

// ADI Digital Outputs
pros::ADIDigitalOut wingBackLeft('A', false);
pros::ADIDigitalOut wingBackRight('B', false);
pros::ADIDigitalOut wingFrontLeft('E', false);
pros::ADIDigitalOut wingFrontRight('F', false);
pros::ADIDigitalOut lift('C', false);
// Limit switch in port 'D'

// Sensors
pros::Imu imu(11);
pros::Rotation rotationSensor(16);

// Drivetrain struct
lemlib::Drivetrain drivetrain(
    &driveLeft,     // left drivetrain motors
    &driveRight,    // right drivetrain motors
    11,             // 11" track width
    lemlib::Omniwheel::NEW_275,  // 2.75" wheel diameter
    450,             // 450 RPM drivetrain
    2
);

// Lateral motion controller
lemlib::ControllerSettings lateralController(
    20,     // kP
    0,      // kI
    20,     // kD
    0,      // anti windup
    1,      // smallErrorRange
    100,    // smallErrorTimeout
    3,      // largeErrorRange
    500,    // largeErrorTimeout
    26      // slew rate (max acceleration)
);
 
// Angular motion controller
lemlib::ControllerSettings angularController(
    5,      // kP
    0,      // kI
    47,     // kD
    3,      // anti windup
    1,      // smallErrorRange
    100,    // smallErrorTimeout
    3,      // largeErrorRange
    500,    // largeErrorTimeout
    0       // slew rate (max acceleration)
);

// Odometry struct
lemlib::OdomSensors sensors(
    nullptr, // N/A - vertical tracking wheel 1
    nullptr, // N/A - vertical tracking wheel 2
    nullptr, // N/A - horizontal tracking wheel 1
    nullptr, // N/A - hortizontal tracking wheel 2
    &imu     // inertial sensor
);

// Create chassis object
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
