#include "main.h"

bool liftRaised = false;

void setLift() {
    while ( true ) {
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) ) {
            if ( liftRaised == false ) {
                lift.set_value(1);
                liftRaised = true;
            }
            else {
                lift.set_value(0);
                liftRaised = false;
            }
        }
        pros::delay(250);
    }
}
