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
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT) ) {
            wingBackLeft.set_value(!leftBackWing);
            leftBackWing = !leftBackWing;
        }

        // Back Right Wing
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT) ) {
            wingBackRight.set_value(!rightBackWing);
            rightBackWing = !rightBackWing;
        }

        // Both Back Wings (Back Pushbot Mode)
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) ) {
            wingBackLeft.set_value(!backPushBotMode);
            wingBackRight.set_value(!backPushBotMode);
            leftBackWing = !backPushBotMode;
            rightBackWing = !backPushBotMode;
            backPushBotMode = !backPushBotMode;
        }

        // Front Left Wing
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN) ) {
            wingFrontLeft.set_value(!leftFrontWing);
            leftFrontWing = !leftFrontWing;
        }

        // Front Right Wing
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) ) {
            wingFrontRight.set_value(!rightFrontWing);
            rightFrontWing = !rightFrontWing;
        }

        // Both Front Wings (Front Pushbot Mode)
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) ) {
            wingFrontLeft.set_value(!frontPushBotMode);
            wingFrontRight.set_value(!frontPushBotMode);
            leftFrontWing = !frontPushBotMode;
            rightFrontWing = !frontPushBotMode;
            frontPushBotMode = !frontPushBotMode;
        }

        // TRUE PUSHBOT MODE (Beyblade Mode)
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X) ) {
            if ( backPushBotMode == false || frontPushBotMode == false ) {
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
            }
        }
        pros::delay(10);
    }
}
