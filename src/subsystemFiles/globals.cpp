#include "main.h"

// Variables
bool show_logo = true;
Gif gif("/usd/logo_stretched.gif", lv_scr_act());
double fw_output = 0.0;
double target_fw_rpm = 560.0;

// Controllers
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motors
pros::Motor driveLeftFront(11, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveMiddleLeft(12, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveLeftBack(13, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(20, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveMiddleRight(19, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightBack(18, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor flywheel(21, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor intake(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_COUNTS);

// Motor Groups
pros::Motor_Group driveLeft({driveLeftFront, driveLeftBack, driveMiddleLeft});
pros::Motor_Group driveRight({driveRightFront, driveRightBack, driveMiddleRight});

// ADI Digital Outputs
pros::ADIDigitalOut lift('A', false);
pros::ADIDigitalOut wingRight('B', false);
pros::ADIDigitalOut wingLeft('C', false);
pros::ADIDigitalOut liftRachet('H', false);

// Inertial Sensor
pros::Imu imu(17);

// Drivetrain struct
lemlib::Drivetrain_t drivetrain {
    &driveLeft,     // left drivetrain motors
    &driveRight,    // right drivetrain motors
    11,             // 11" track width
    2.75,           // 2.75" wheel diameter
    450             // 450 RPM drivetrain
};

// Odometry struct
lemlib::OdomSensors_t sensors {
    nullptr, // N/A - vertical tracking wheel 1
    nullptr, // N/A - vertical tracking wheel 2
    nullptr, // N/A - horizontal tracking wheel 1
    nullptr, // N/A - hortizontal tracking wheel 2
    &imu     // inertial sensor
};

// Forward/backward PID
lemlib::ChassisController_t lateralController {
    8,      // kP
    30,     // kD
    1,      // smallErrorRange
    100,    // smallErrorTimeout
    3,      // largeErrorRange
    500,    // largeErrorTimeout
    5       // slew rate
};
 
// Turning PID
lemlib::ChassisController_t angularController {
    4,      // kP
    40,     // kD
    1,      // smallErrorRange
    100,    // smallErrorTimeout
    3,      // largeErrorRange
    500,    // largeErrorTimeout
    0       // slew rate
};

// Create chassis object
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
