#include "main.h"

// 127 = intake
// -127 = extake

void setIntake() {
    while ( true ) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            intake = 127.0;
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            intake = -127.0;
        }
        else {
            intake = 0;
        }
    }
}
