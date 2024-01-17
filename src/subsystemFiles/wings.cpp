#include "main.h"

bool leftWing = false;
bool rightWing = false;
bool pushBotMode = false;

void setWings() {
    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) ) {
            if ( leftWing == false ) {
                wingLeft.set_value(1);
                leftWing = true;
                pros::delay(250);
            }
            else {
                wingLeft.set_value(0);
                leftWing = false;
                pros::delay(250);
            }
        }

        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) ) {
            if ( rightWing == false ) {
                wingRight.set_value(1);
                rightWing = true;
                pros::delay(250);
            }
            else {
                wingRight.set_value(0);
                rightWing = false;
                pros::delay(250);
            }
        }

        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ) {
            if ( pushBotMode == false ) {
                wingRight.set_value(1);
                wingLeft.set_value(1);
                pushBotMode = true;
                leftWing = true;
                rightWing = true;
                pros::delay(250);
            }
            else {
                wingRight.set_value(0);
                wingLeft.set_value(0);
                pushBotMode = false;
                leftWing = false;
                rightWing = false;
                pros::delay(250);
            }
        }
    }
}
