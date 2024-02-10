#include "main.h"

void update_screen() {
    while (true) {
        lemlib::Pose pose = chassis.getPose();          // Get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x);           // Print the x position
        pros::lcd::print(1, "y: %f", pose.y);           // Print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // Print the heading
        pros::delay(10);
    }
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    //pros::lcd::initialize();                    // Display default PROS log screen
    //pros::Task screenTask(update_screen);       // Create a task to print the position to the screen

    // Set drivetrain brake mode to brake
    driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveMiddleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    driveMiddleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    if ( auton == 1 ) {
        /*-------------------------*/
        /* Six Ball Far Side Auton */
        /*-------------------------*/

        // First three triballs
        chassis.setPose(12, -60, 270);          // Start
        chassis.moveTo(6, -60, 300);            // Move slightly foreward towards first triball
        intake.move(127);                       // Drop intake
        pros::delay(500);                       // Grab 1st triball
        chassis.moveTo(34, -60, 700);           // Move towards match load zone & push preload
        wingLeft.set_value(1);                  // Extend left wing
        chassis.moveTo(41, -60, 500);           // Align to knock out match load triball
        chassis.moveTo(55, -53, 500);           // Align to knock out match load triball
        wingRight.set_value(1);                 // Extend right wing
        chassis.turnTo(63, -72, 400, false, 80);// Push out match load triball
        wingRight.set_value(0);                 // Retract right wing
        wingLeft.set_value(0);                  // Retract left wing
        chassis.turnTo(70, -39, 500, true);     // Turn to align better for ram
        chassis.moveTo(70, -39, 500);           // Move to align better for ram
        chassis.turnTo(70, 0, 400, true);       // Turn for ram
        chassis.moveTo(70, 0, 600);             // Ram first three triballs with vigor
        chassis.moveTo(70, -40, 500);           // Back up from goal
        chassis.turnTo(70, 0, 400);             // Turn to goal
        intake.move(-127);                      // BLAUUGGH -> spit triball
        pros::delay(500);                       // Wait 500 milliseconds
        chassis.moveTo(70, 0, 600);             // Ram first three triballs with vigor
        chassis.moveTo(70, -27, 500);           // Back up from goal
        chassis.setPose(58, -37, imu.get_heading() - 90);

        // Last three triballs
        chassis.turnTo(34, -30, 300);           // Turn to point towards 4th triball
        chassis.moveTo(34, -30, 600);           // Move towards 4th triball
        chassis.turnTo(6, -23, 300);           // Turn to adjust angle
        intake.move(127);                       // Spin intake
        chassis.moveTo(6, -23, 500);           // Move to 4th triball
        pros::delay(300);                       // Grabby grabby triball
        chassis.turnTo(17, -18, 300);           // Turn to align for 5th triball
        chassis.moveTo(17, -18, 500);           // Move to align for 5th triball
        chassis.turnTo(47, -10, 300);           // Turn to spit out 4th triball towards goal
        intake.move(-127);                      // BLAUUGGH -> spit triball
        pros::delay(400);                       // Wait 400 milliseconds
        intake.move(0);                         // Stop intake
        chassis.turnTo(3, -2, 300);             // Turn towards 5th triball
        intake.move(127);                       // Spin intake
        chassis.moveTo(3, -2, 500);             // Intake 5th triball
        chassis.turnTo(47, -2, 500);            // Turn to face away from goal
        intake.move(-127);                      // Spit out 5th triball
        pros::delay(400);                       // BLAUUGGH 2 -> spit 2nd triball
        intake.move(0);                         // Stop intake
        chassis.turnTo(-72, -2, 300);           // Turn to face away from goal
        wingLeft.set_value(1);                  // Extend left wing
        wingRight.set_value(1);                 // Extend right wing
        chassis.moveTo(47, -2, 800);            // Ram last three triballs into goal
        chassis.moveTo(20, -2, 500);            // Back up from goal
    }

    else if ( auton == 2 ) {
        /*----------------------------*/
        /* Four Ball Close Side Auton */
        /*----------------------------*/

        // Clear match load triball
        chassis.setPose(-48, -60, 135);         // Start
        wingRight.set_value(1);                 // Extend wing
        pros::delay(500);                       // Wait 500 milliseconds
        chassis.turnTo(72, -60, 500);           // Turn to knock out triball
        pros::delay(500);                       // Wait 500 milliseconds
        wingRight.set_value(0);                 // Retract wing
        //chassis.moveTo(-38, -65, 500);        // Align for move towards middle

        // Go for middle triball
        intake.move(127);                       // Spin intake
        chassis.turnTo(-33, -13, 1000);         // Turn towards middle triball
        chassis.moveTo(-33, -13, 3500, 100);    // Drive to middle triball

        // Move back, shoot, & contact elevation bar
        chassis.turnTo(-48, -60, 400);
        chassis.moveTo(-48, -60, 2000, 100);    // Move back from middle
        chassis.turnTo(0, -60, 750);            // Turn
        intake.move(-127);                      // Shoot triball across
        pros::delay(500);                       // Delay
        intake.move(0);                         // Stop intake
        chassis.turnTo(-72, -60, 750);          // Turn 180 degrees
        chassis.moveTo(-1, -58, 1500, 100);      // Contact elevation bar
    }

    else if ( auton == 3 || auton == 4 ) {
        /*--------------------*/
        /* Programming Skills */
        /*--------------------*/
        
        int launchTime = 30000;
        if ( auton == 4 ) {
            launchTime = 2000;
        }

        // Score Preloads
        chassis.setPose(49, 58, 135);           // Start
        chassis.moveTo(60, 47, 500);            // Move diagonally to align with goal
        chassis.turnTo(60, 31, 300);            // Turn towards goal
        chassis.moveTo(60, 20, 1000);           // Ram 1st two triballs into goal

        // Match loads
        chassis.moveTo(60, 55, 750);            // Move in front of match-loading position
        chassis.turnTo(-45, 10, 500);           // Turn to face opposite goal
        wingRight.set_value(1);                 // Extend right wing
        
        // Set drivetrain brake mode to hold
        driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveMiddleRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        driveMiddleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        puncher = 127;                        // Wham bam punch kick pow boom wowie zowie
        pros::delay(launchTime);              // 30 second delay
        puncher = 0;                          // Stop puncher
        
        while ( rotationSensor.get_angle() < 35000 ) {      // While puncher is too high
            puncher = 127;                                  // Lower puncher
        }
        while ( rotationSensor.get_angle() > 35000 ) {      // While puncher is too low
            puncher = 127;                                  // Lower puncher
        }
        puncher = 0;                                        // Stop puncher

        wingRight.set_value(0);                             // Retract right wing

        // Set drivetrain brake mode to brake
        driveLeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveLeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveRightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveRightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveMiddleRight.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
        driveMiddleLeft.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

        chassis.setPose(54, 54, 244.7);         // setPose after match loads (puncher causes error in IMEs)

        chassis.moveTo(51, 51, 500);            // Move away from match load bar
        chassis.turnTo(66, 37, 400);            // Turn for crossing alignment
        chassis.moveTo(36, 65, 1000);           // Move for crossing alignment
        chassis.turnTo(72, 55, 500);            // Turn to cross field
        chassis.moveTo(-26, 55, 1500);          // Cross field

        // 1st ram set
        chassis.turnTo(-6, 69, 1000);           // Turn to pass cross bar
        chassis.moveTo(-46, 41, 1000);          // Move parallel with cross bar
        chassis.turnTo(-77, 60, 1000);          // Turn towards middle
        chassis.moveTo(-14, 33, 1000);          // Move towards middle
        wingRight.set_value(1);                 // Extend right wing
        chassis.turnTo(0, 42, 500);             // Turn to ram
        chassis.moveTo(-42, 15, 1000);          // Ram
        wingRight.set_value(0);                 // Retract right wing
        chassis.moveTo(-14, 33, 1000);          // Back up

        // 2nd ram set
        wingRight.set_value(1);                 // Extend right wing
        chassis.turnTo(-15, 72, 500);           // Turn to align for next ram
        wingLeft.set_value(1);                  // Extend left wing
        chassis.moveTo(-15, 2, 750);            // Move to align for next ram
        chassis.turnTo(72, 2, 500);             // Turn for ram
        wingLeft.set_value(1);                  // Extend left wing
        pros::delay(500);                       // 600 millisecond delay
        chassis.moveTo(-72, 2, 1000);           // Ram 
        chassis.moveTo(-16, 2, 1000);           // Back up
        wingLeft.set_value(0);                  // Retract left wing
        wingRight.set_value(0);                 // Retract right wing

        // 3rd ram set 
        chassis.turnTo(-16, 50, 500);           // Turn for next ram
        chassis.moveTo(-16, -10, 750);          // Move to align for ram
        wingRight.set_value(1);                 // Extend right wing
        chassis.turnTo(72, -10, 500);           // Turn for ram
        wingLeft.set_value(1);                  // Extend left wing
        chassis.moveTo(-72, -10, 1000);         // Ram
        chassis.moveTo(-16, -10, 1000);         // Back up
        
        // 4th ram set
        chassis.turnTo(-2, 5, 500);             // Turn for next ram
        wingLeft.set_value(0);                  // Retract left wing
        wingRight.set_value(0);                 // Retract right wing
        chassis.moveTo(-48, -55, 750);          // Move to match-load bar
        chassis.turnTo(-37, -67, 500);          // Turn to align with goal
        chassis.moveTo(-59, -43, 750);          // Move along match-load bar
        chassis.turnTo(-59, -72, 500);          // Turn to goal
        wingLeft.set_value(1);                  // Extend left wing
        chassis.moveTo(-59, 0, 1000);           // Ram
        chassis.moveTo(-59, -43, 500);          // Back away
        chassis.moveTo(-59, 0, 1000);           // Ram
        chassis.moveTo(-59, -43, 500);          // Back away
        wingLeft.set_value(0);                  // Retract left wing
    }

    if ( first_run == true ) {
        Gif matchLogo("/usd/logo_stretched.gif", lv_scr_act());
        pros::delay(800);
        first_run = false;
    }
}
