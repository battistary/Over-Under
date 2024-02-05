#include "main.h"

bool liftRaised = false;

void setLift() {
    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) ) {
            if ( liftRaised == false ) {
                lift.set_value(1);
                liftRaised = true;
                pros::delay(250);
        }
            else {
                lift.set_value(0);
                liftRaised = false;
                pros::delay(250);
            }
        }
    }
}
