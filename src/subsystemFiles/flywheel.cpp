#include "main.h"

// Flywheel TBH loop variables
double current_fw_rpm = 0.0;
double error = 0.0;
double prev_error = 0.0;
double tbh = 0.0;
double gain = 0.01; //0.01;

// Flywheel control functions
void setFlywheel() {
    // L1 forward, L2 disabled
    // Spins at 10v without TBH
    flywheel = 127.0 / 12.0 * 10.0 * controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
}

void flywheelTBHLoopOPControl() {
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
    
    if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) ) {
        // Set the flywheel motor speeds based on the fw_output voltage
        flywheel.move_velocity(fw_output);
    }
    else {
        current_fw_rpm = flywheel.get_actual_velocity();
        fw_output = 0.0;
        tbh = 0.0;
        prev_error = 0.0;
        flywheel.brake();
    }
    pros::lcd::set_text(1, std::to_string(current_fw_rpm));
}

void flywheelTBHLoopAuton() {
    while ( true ) {
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
    }
}

void resetFlywheelTBH() {
    if ( controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) ) {
        flywheel.brake();
        error = 0.0;
        prev_error = 0.0;
        fw_output = 0.0;
        tbh = 0.0;
    }
}

void stopAndResetFlywheelTBH() {
    current_fw_rpm = flywheel.get_actual_velocity();
    fw_output = 0.0;
    tbh = 0.0;
    prev_error = 0.0;
    flywheel.brake();

    flywheel.brake();
    double error = 0.0;
    double prev_error = 0.0;
    fw_output = 0.0;
    double tbh = 0.0;
}
