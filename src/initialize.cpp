#include "main.h"

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
    puncher.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    pros::c::adi_pin_mode(LIMIT_SWITCH, INPUT); // Limit switch
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
    bool start = true;
    logo.clean();
    pros::delay(10);
    Gif skills("/usd/skills.gif", lv_scr_act());
    skills.clean();
    Gif close("/usd/close.gif", lv_scr_act());
    close.clean();
    Gif far("/usd/far.gif", lv_scr_act());
    far.clean();

    while ( true ) {
        if ( start == true ) {
            Gif far("/usd/far.gif", lv_scr_act());
            start = false;
            pros::delay(800);
        }

        if ( pros::c::adi_digital_read(LIMIT_SWITCH) == HIGH ) {   
            auton++;

            if ( auton > 4 ) {
                auton = 1;
            }

            if ( auton == 1 ) {
                skills.clean();
                pros::delay(10);
                Gif far("/usd/far.gif", lv_scr_act());
                pros::delay(800);
            }
            
            else if ( auton == 2 ) {
                far.clean();
                pros::delay(10);
                Gif close("/usd/close.gif", lv_scr_act());
                pros::delay(800);
            }
    
            else if ( auton == 3 ) {
                close.clean();
                pros::delay(10);
                Gif skills("/usd/skills.gif", lv_scr_act());
                pros::delay(800);
            }

            else if ( auton == 4 ) {
                skills.clean();
                pros::delay(10);
                Gif skills("/usd/easter_egg.gif", lv_scr_act());
                pros::delay(800);
            }
        }
        pros::delay(10);
    }
}
