#include "main.h"

bool rachet = false;
bool hold = false;

void setLift() {
    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ) {
            lift.set_value(1);
            pros::delay(250);
        }
        else if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ) {
            lift.set_value(0);
            pros::delay(250);
        }

        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) ) {
            if ( rachet == false ) {
                liftRachet.set_value(1);
                rachet = true;
                pros::delay(250);
        }
            else {
                liftRachet.set_value(0);
                rachet = false;
                pros::delay(250);
            }
        }

    }
}
