#include "main.h"

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
    //auton = 3;
    controller.set_text(1, 0, "Hi Preston!");

    pros::Task screenTask([&]() {
        pros::lcd::initialize();    // Display default PROS log screen
        lemlib::Pose pose(0, 0, 0);
        while ( true ) {
            pros::lcd::print(0, "X: %f", chassis.getPose().x);
            pros::lcd::print(1, "Y: %f", chassis.getPose().y);
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta);
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            pros::delay(50);
        }
    });

    // Set drivetrain brake mode to brake
    driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    if ( auton == 1 ) {
        /*----------------------------------*/
        /* Far Side 5 Ball Mid Rush (ELIMS) */
        /*----------------------------------*/

        chassis.setPose(36, -56, 0);                    // Start
        intake.move(127);
        intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        chassis.moveToPoint(26, -9, 2000);
        wingFrontRight.set_value(1);
        pros::delay(100);
        wingFrontRight.set_value(0);
        chassis.waitUntilDone();
        pros::delay(100);
        intake.move(84);
        chassis.moveToPoint(28, -36, 1000, false);
        chassis.turnTo(60, -36, 350);                   // Turn
        chassis.waitUntilDone();
        intake.move(-127);                              // Bleuugh!
        pros::delay(350);
        intake.move(0);
        chassis.turnTo(7, -27, 350);
        intake.move(127);
        chassis.moveToPoint(7, -27, 1000);
        chassis.waitUntilDone();
        pros::delay(300);
        intake.move(84);
        wingFrontRight.set_value(1);
        chassis.moveToPoint(43, -43, 1600, false);
        chassis.waitUntil(10);
        wingFrontRight.set_value(0);
        chassis.turnTo(30, -56, 350, false);
        chassis.waitUntilDone();
        intake.move(-127);                              // Bleuugh!
        pros::delay(300);
        intake.move(0);
        chassis.moveToPoint(30, -63, 1000, false);
        chassis.waitUntilDone();
        chassis.setPose(39, chassis.getPose().y, imu.get_heading());
        chassis.waitUntilDone();
        intake.move(127);
        chassis.turnTo(7, -64, 350);
        chassis.moveToPoint(7, -64, 900);
        chassis.waitUntilDone();
        pros::delay(300);
        intake.move(84);
        chassis.moveToPoint(36, -64, 900, false);
        chassis.turnTo(48, -55, 350, false);
        chassis.moveToPoint(52, -55, 900, false);
        wingBackLeft.set_value(1);
        chassis.turnTo(55, -24, 350, false);    // knock out
        chassis.moveToPoint(55, -24, 800, false);
        chassis.moveToPoint(55, -54, 1000);
        chassis.waitUntilDone();
        wingBackLeft.set_value(0);
        chassis.moveToPoint(68, -10, 1000);
        pros::delay(350);
        intake.move(-127);
        chassis.moveToPoint(68, -40, 900, false);
        driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
        chassis.moveToPoint(68, -40, 500, false);
        intake.move(0);
        wingFrontLeft.set_value(0);
    }

    else if ( auton == 2 ) {
        /*-------------------------------*/
        /* Far Side 6 Ball + AWP (QUALS) */
        /*-------------------------------*/

        // First three triballs 
        chassis.setPose(10, -60, 270);                      // Start
        intake.move(127);                                   // Spin intake
        chassis.moveToPoint(8, -60, 200);                   // Move slightly foreward towards first triball
        chassis.waitUntilDone();
        pros::delay(100);                                   // Grab 1st triball
        intake.move(84);
        chassis.moveToPoint(34, -60, 1000, false, 100);     // Move towards match load zone & push preload
        chassis.waitUntilDone();
        wingBackLeft.set_value(1);                          // Extend left wing
        chassis.moveToPoint(41, -60, 500);                  // Align to knock out match load triball
        chassis.moveToPoint(55, -52, 500);                  // Align to knock out match load triball
        chassis.waitUntilDone();
        wingBackRight.set_value(1);                         // Extend right wing
        chassis.turnTo(63, -72, 400, false, 50);            // Push out match load triball
        chassis.waitUntilDone();
        wingBackRight.set_value(0);                         // Retract right wing
        wingBackLeft.set_value(0);                          // Retract left wing
        chassis.turnTo(65, -39, 500, true);                 // Turn to align better for ram
        chassis.moveToPoint(65, -39, 500);                  // Move to align better for ram
        chassis.turnTo(65, 0, 400, true);                   // Turn for ram
        chassis.moveToPoint(65, 0, 600);                    // Ram first two triballs with vigor
        chassis.moveToPoint(65, -40, 500);                  // Back up from goal
        chassis.turnTo(65, 0, 600);                         // Turn to goal
        chassis.waitUntilDone();
        intake.move(-127);                                  // BLAUUGGH -> spit triball
        pros::delay(500);                                   // Wait 500 milliseconds
        chassis.moveToPoint(65, 0, 700);                    // Ram last triball with vigor
        chassis.waitUntilDone();
        pros::delay(10);
        chassis.moveToPoint(65, -30, 600);                  // Back up from goal -27 -> -31
        //chassis.waitUntilDone();
        //chassis.setPose(58, -41, imu.get_heading() - 90);   // -37 -> -41

        // Last three triballs
        chassis.turnTo(0, -22, 400);                        // Turn to adjust angle   6->2
        chassis.waitUntilDone();
        intake.move(127);                                   // Spin intake
        chassis.moveToPoint(12, -26, 1000);                 // Move to 4th triball
        chassis.waitUntilDone();
        pros::delay(300);                                   // Grabby grabby triball
        intake.move(84);
        chassis.turnTo(17, -18, 300);                       // Turn to align for 5th triball
        chassis.moveToPoint(17, -18, 500);                  // Move to align for 5th triball
        chassis.turnTo(47, -10, 300);                       // Turn to spit out 4th triball towards goal
        chassis.waitUntilDone();
        intake.move(-127);                                  // BLAUUGGH -> spit triball
        pros::delay(400);                                   // Wait 400 milliseconds
        intake.move(0);                                     // Stop intake
        chassis.turnTo(5, -3, 400);                         // Turn towards 5th triball
        chassis.waitUntilDone();
        intake.move(127);                                   // Spin intake
        chassis.moveToPoint(5, -3, 500);                    // Intake 5th triball
        chassis.waitUntilDone();
        pros::delay(400);                                   // Intake reeeaal good
        intake.move(84);
        chassis.turnTo(47, -3, 500);                        // Turn to face away from goal
        chassis.waitUntilDone();
        intake.move(-127);                                  // Spit out 5th triball
        pros::delay(400);                                   // BLAUUGGH 2 -> spit 2nd triball
        intake.move(0);                                     // Stop intake
        chassis.turnTo(-72, -3, 400);                       // Turn to face away from goal
        chassis.waitUntilDone();
        wingBackLeft.set_value(1);                          // Extend left wing
        wingBackRight.set_value(1);                         // Extend right wing
        pros::delay(300);           
        chassis.moveToPoint(47, -7, 800);                   // Ram last three triballs into goal
        chassis.moveToPoint(3, -45, 2000, false);           // Back up from goal
        chassis.waitUntilDone();
        wingBackRight.set_value(1);
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
        chassis.setPose(49, 58, 135);                       // Start
        chassis.moveToPoint(60, 47, 500);                   // Move diagonally to align with goal
        chassis.turnTo(60, 31, 300);                        // Turn towards goal
        chassis.moveToPoint(60, 20, 1000);                  // Ram 1st two triballs into goal

        // Match loads
        chassis.moveToPoint(60, 55, 750);                   // Move in front of match-loading position
        chassis.turnTo(-45, 10, 500);                       // Turn to face opposite goal
        wingBackRight.set_value(1);                         // Extend right wing
        
        // Set drivetrain brake mode to hold
        driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

        puncher = 127;                                      // Wham bam punch kick pow boom wowie zowie
        pros::delay(launchTime);                            // 30 second delay
        puncher = 0;                                        // Stop puncher
        
        while ( rotationSensor.get_angle() < 35000 ) {      // While puncher is too high
            puncher = 127;                                  // Lower puncher
        }
        while ( rotationSensor.get_angle() > 35000 ) {      // While puncher is too low
            puncher = 127;                                  // Lower puncher
        }
        puncher = 0;                                        // Stop puncher
        wingBackRight.set_value(0);                         // Retract right wing

        // Set drivetrain brake mode to brake
        driveLeft.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
        driveRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

        chassis.setPose(54, 54, 244.7);                     // setPose after match loads (puncher causes error in IMEs)

        chassis.moveToPoint(51, 51, 500);                   // Move away from match load bar
        chassis.turnTo(66, 37, 400);                        // Turn for crossing alignment
        chassis.moveToPoint(36, 65, 750);                   // Move for crossing alignment
        chassis.turnTo(72, 55, 500);                        // Turn to cross field
        chassis.moveToPoint(-26, 55, 1500);                 // Cross field

        // 1st & 1.5th ram set
        chassis.turnTo(-6, 69, 500);                        // Turn to pass match load bar
        wingBackLeft.set_value(1);                          // Extend back left wing
        wingBackRight.set_value(1);                         // Extend back right wing
        chassis.moveToPoint(-46, 41, 1000);                 // Move parallel with match load bar
        wingBackLeft.set_value(0);                          // Retract back left wing
        wingBackRight.set_value(0);                         // Retract back right wing
        chassis.turnTo(-58, 50, 300);                       // Turn for ram
        chassis.moveToPoint(-58, 24, 500);                  // Ram
        chassis.moveToPoint(-46, 41, 1000);                 // Move back towards match load bar
        chassis.turnTo(-77, 60, 1000);                      // Turn towards middle
        wingBackRight.set_value(1);                         // Retract back right wing
        chassis.moveToPoint(-14, 33, 1000);                 // Move towards middle
        wingBackLeft.set_value(1);                          // Extend right wing
        chassis.turnTo(0, 42, 500);                         // Turn to ram
        chassis.moveToPoint(-42, 15, 1000);                 // Ram
        wingBackRight.set_value(0);                         // Retract right wing
        chassis.moveToPoint(-14, 33, 1000);                 // Back up

        // 2nd ram set
        wingBackRight.set_value(1);                         // Extend right wing
        chassis.turnTo(-15, 72, 500);                       // Turn to align for next ram
        wingBackLeft.set_value(1);                          // Extend left wing
        chassis.moveToPoint(-15, 2, 750);                   // Move to align for next ram
        chassis.turnTo(72, 2, 500);                         // Turn for ram
        wingBackLeft.set_value(1);                          // Extend left wing
        pros::delay(500);                                   // 500 millisecond delay
        chassis.moveToPoint(-72, 2, 1000);                  // Ram 
        chassis.moveToPoint(-16, 2, 1000);                  // Back up
        wingBackLeft.set_value(0);                          // Retract left wing
        wingBackRight.set_value(0);                         // Retract right wing

        // 3rd ram set 
        chassis.turnTo(-16, 50, 500);                       // Turn for next ram
        chassis.moveToPoint(-16, -27, 750);                 // Move to align for ram
        wingBackRight.set_value(1);                         // Extend right wing
        chassis.turnTo(40, -64, 500);                       // Turn for ram
        pros::delay(200);
        wingBackLeft.set_value(1);                          // Extend left wing
        chassis.moveToPoint(-72, 0, 1000);                  // Ram
        chassis.moveToPoint(-16, -32, 1000);                // Back up
        
        // 4th ram set
        //chassis.turnTo(-16, -72, 300);                    // Turn to move for final ram
        //chassis.moveToPoint(-16, 10, 1000);               // Move for final ram
        chassis.turnTo(2, -16, 500);                        // Turn for next ram
        wingBackLeft.set_value(0);                          // Retract left wing
        wingBackRight.set_value(0);                         // Retract right wing
        chassis.moveToPoint(-36, -40, 750);                 // Move to match-load bar
        //chassis.turnTo(-27, -63, 500);                    // Turn to align with goal
        //chassis.moveToPoint(-27, -63, 500);               // Move to scoop triballs
        chassis.turnTo(-36, 0, 500);
        chassis.moveToPoint(-36, -63, 500);
        chassis.turnTo(0, -63, 500);                        // Turn to PUSH
        wingBackLeft.set_value(1);
        //chassis.turnTo(43, -60, 500);
        chassis.moveToPoint(-43, -63, 500);
        chassis.turnTo(-20, -80, 500);
        chassis.moveToPoint(-64, -43, 750);                 // Move along match-load bar
        chassis.turnTo(-64, -72, 500);                      // Turn to goal
        wingBackLeft.set_value(1);                          // Extend left wing
        intake.move(-127);                                  // Spit out any triballs
        chassis.moveToPoint(-64, 0, 1000);                  // Ram
        chassis.moveToPoint(-64, -43, 500);                 // Back up
        //chassis.moveToPoint(-64, 0, 1000);                // Ram
        //chassis.moveToPoint(-64, -43, 500);               // Back up
        wingBackLeft.set_value(0);                          // Retract left wing
        intake.move(0);
    }
}
