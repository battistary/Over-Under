#include "main.h"

bool rachet = false;
bool liftRaised = false;
bool hold = false;

void setLift() {
    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) ) {
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

        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) ) {
            if ( rachet == false ) {
                liftRachetLeft.set_value(1);
                liftRachetRight.set_value(1);
                rachet = true;
                pros::delay(250);
        }
            else {
                liftRachetLeft.set_value(0);
                liftRachetRight.set_value(0);
                rachet = false;
                pros::delay(250);
            }
        }
    }
}
