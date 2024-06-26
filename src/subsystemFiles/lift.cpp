#include "main.h"

bool liftRaised = false;

void setLift() {
    while ( true ) {
        if ( controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) ) {
            lift.set_value(!liftRaised);
            liftRaised = !liftRaised;
        }
        pros::delay(250);
    }
}
