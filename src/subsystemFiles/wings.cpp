#include "main.h"

bool leftBackWing = false;
bool rightBackWing = false;
bool leftFrontWing = false;
bool rightFrontWing = false;
bool frontPushBotMode = false;
bool backPushBotMode = false;

void setWings() {
    while ( true ) {
        // Back Left Wing
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) ) {
            if ( leftBackWing == false ) {
                wingBackLeft.set_value(1);
                leftBackWing = true;
                pros::delay(250);
            }
            else {
                wingBackLeft.set_value(0);
                leftBackWing = false;
                pros::delay(250);
            }
        }

        // Back Right Wing
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) ) {
            if ( rightBackWing == false ) {
                wingBackRight.set_value(1);
                rightBackWing = true;
                pros::delay(250);
            }
            else {
                wingBackRight.set_value(0);
                rightBackWing = false;
                pros::delay(250);
            }
        }

        // Both Back Wings (Back Pushbot Mode)
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ) {
            if ( backPushBotMode == false ) {
                wingBackRight.set_value(1);
                wingBackLeft.set_value(1);
                backPushBotMode = true;
                leftBackWing = true;
                rightBackWing = true;
                pros::delay(250);
            }
            else {
                wingBackRight.set_value(0);
                wingBackLeft.set_value(0);
                backPushBotMode = false;
                leftBackWing = false;
                rightBackWing = false;
                pros::delay(250);
            }
        }

        // Front Left Wing
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) ) {
            if ( leftFrontWing == false ) {
                wingFrontLeft.set_value(1);
                leftFrontWing = true;
                pros::delay(250);
            }
            else {
                wingFrontLeft.set_value(0);
                leftFrontWing = false;
                pros::delay(250);
            }
        }

        // Front Right Wing
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ) {
            if ( rightFrontWing == false ) {
                wingFrontRight.set_value(1);
                rightFrontWing = true;
                pros::delay(250);
            }
            else {
                wingFrontRight.set_value(0);
                rightFrontWing = false;
                pros::delay(250);
            }
        }

        // Both Front Wings (Front Pushbot Mode)
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ) {
            if ( frontPushBotMode == false ) {
                wingFrontRight.set_value(1);
                wingFrontLeft.set_value(1);
                frontPushBotMode = true;
                leftFrontWing = true;
                rightFrontWing = true;
                pros::delay(250);
            }
            else {
                wingFrontRight.set_value(0);
                wingFrontLeft.set_value(0);
                frontPushBotMode = false;
                leftFrontWing = false;
                rightFrontWing = false;
                pros::delay(250);
            }
        }

        // TRUE PUSHBOT MODE (Beyblade Mode)
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) ) {
            if ( backPushBotMode == false && frontPushBotMode ) {
                wingBackRight.set_value(1);
                wingBackLeft.set_value(1);
                wingFrontRight.set_value(1);
                wingBackLeft.set_value(1);
                backPushBotMode = true;
                frontPushBotMode = true;
                leftBackWing = true;
                rightBackWing = true;
                leftFrontWing = true;
                rightFrontWing = true;
                pros::delay(250);
            }
            else {
                wingBackRight.set_value(0);
                wingBackLeft.set_value(0);
                wingFrontRight.set_value(0);
                wingFrontLeft.set_value(0);
                backPushBotMode = false;
                frontPushBotMode = false;
                leftFrontWing = true;
                rightFrontWing = true;
                leftBackWing = false;
                rightBackWing = false;
                pros::delay(250);
            }
        }
    }
}
