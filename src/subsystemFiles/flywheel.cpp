#include "main.h"

// Flywheel TBH loop variables
double current_fw_rpm = 0.0;
double error = 0.0;
double prev_error = 0.0;
double tbh = 0.0;
double gain = 0.01;
double fw_output = 0.0;
double target_fw_rpm = 300.0;

// Flywheel control functions
void setFlywheel() {
    while ( true ) {
        // L1 forward, L2 disabled
        // Spins at 10v without TBH
        flywheel = 127.0 / 12.0 * 10.0 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
    }
}

void flywheelTBHLoopOPControl() {
    while ( true ) {
        if ( liftRaised ) {
            target_fw_rpm = 300.0;
        }
        else {
            target_fw_rpm = 480.0;
        }

        // Get the current RPM of the flywheel
        current_fw_rpm = flywheel.get_actual_velocity();
        
        // Calculate the error between the current RPM and the target RPM
        error = target_fw_rpm - current_fw_rpm;

        fw_output += gain * error;

        if ( (error > 0 && prev_error < 0) || (error < 0 && prev_error > 0) ) {
            fw_output = 0.5 * (fw_output + tbh);
            tbh = fw_output;
            prev_error = error;
        }
        
        // Set the flywheel motor speeds based on the fw_output voltage
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ) {
            flywheel.move_velocity(fw_output);
        }
        else if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) ) {
            flywheel.move_velocity(-1 * fw_output);
        }
        else {
            current_fw_rpm = flywheel.get_actual_velocity();
            fw_output = 0.0;
            tbh = 0.0;
            prev_error = 0.0;
            flywheel.brake();
        }
        pros::lcd::set_text(1, std::to_string(current_fw_rpm));
        pros::delay(10);
    }
}

void flywheelTBHLoopAuton(uint32_t stop) {
    while ( pros::millis() < stop ) {
        // Get the current RPM of the flywheel
        current_fw_rpm = flywheel.get_actual_velocity();
        
        // Calculate the error between the current RPM and the target RPM
        error = target_fw_rpm - current_fw_rpm;

        fw_output += gain * error;

        if ( (error > 0 && prev_error < 0) || (error < 0 && prev_error > 0) ) {
            fw_output = 0.5 * (fw_output + tbh);
            tbh = fw_output;
            prev_error = error;
        }
        
        // Set the flywheel motor speeds based on the fw_output voltage
        flywheel.move_velocity(fw_output);
        pros::delay(10);
    }
}

void resetFlywheelTBH() {
    while ( true ) {
        if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_B) ) {
            flywheel.brake();
            error = 0.0;
            prev_error = 0.0;
            fw_output = 0.0;
            tbh = 0.0;
        }
        pros::delay(10);
    }
}

void stopAndResetFlywheelTBH() {
    current_fw_rpm = flywheel.get_actual_velocity();
    fw_output = 0.0;
    tbh = 0.0;
    prev_error = 0.0;
    flywheel.brake();

    flywheel.brake();
    error = 0.0;
    prev_error = 0.0;
    fw_output = 0.0;
    tbh = 0.0;
}
