#include "main.h"

void update_screen() {
    while (true) {
        lemlib::Pose pose = chassis.getPose();          // Get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x);           // Print the x position
        pros::lcd::print(1, "y: %f", pose.y);           // Print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // Print the heading
        pros::delay(10);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	chassis.calibrate(); // Calibrate the chassis
    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

    driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveMiddleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveMiddleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    pros::lcd::initialize();                    // Display the default PROS screen on the Brain screen
    pros::Task screenTask(update_screen); // Create a task to print the position to the screen
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    Gif newGif("/usd/logo_stretched.gif", lv_scr_act());
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	gif.clean();
    selector::init();
}
