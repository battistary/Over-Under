#include "main.h"

void setPuncher() {
    // Puncher rotation sensor positions:
    // 140* up
    // 275* middle
    // 193* down
    // 151 - 200* slip gear

    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) ) {
            while ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) ) {
                puncher = 127;
            }
            while ( rotationSensor.get_angle() < 35000 ) {
                puncher = 127;
            }
            while ( rotationSensor.get_angle() > 35000 ) {
                puncher = 127;
            }
            puncher = 0;
        }
        pros::delay(2);
    }
}
