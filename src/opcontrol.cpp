#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    pros::Task setLogo {[=] {
        if ( first_run == true ) {
            activeGif.clean();
            pros::delay(10);
            static Gif matchLogo("/usd/logo_stretched.gif", lv_scr_act());
            pros::delay(800);
            first_run = false;
        }
    }};

    driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    controller.set_text(1, 0, "Objective: Win");

    pros::Task endgameRumble {[=] {
        pros::delay(88000);
        controller.rumble("-");
        controller.set_text(1, 0, "Hang time!");
    }};

    pros::Task punch(setPuncher);
    pros::Task intake(setIntake);
    pros::Task lift(setLift);
    pros::Task wing(setWings);
    
    if (auton == 5) {
        // Score Preloads
        chassis.setPose(49, 58, 135);           // Start
        chassis.moveToPoint(60, 47, 500);       // Move diagonally to align with goal
        chassis.turnTo(60, 31, 300);            // Turn towards goal
        chassis.moveToPoint(60, 20, 1000);      // Ram 1st two triballs into goal

        // Match loads
        chassis.moveToPoint(60, 55, 750);       // Move in front of match-loading position
        chassis.turnTo(-45, 10, 500);           // Turn to face opposite goal
        wingBackRight.set_value(1);             // Extend right wing
    }
    while ( true ) {
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        chassis.arcade(leftY, rightX, 2.7);

        /*double left = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        double right = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        driveLeft.move(left);
        driveRight.move(right);*/
        pros::delay(10);
    }
}
