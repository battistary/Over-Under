#include "main.h"

// 127 = intake
// -127 = extake

void setIntake() {
    while ( true ) {
        intake = 127 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
        pros::delay(10);
    }
}
