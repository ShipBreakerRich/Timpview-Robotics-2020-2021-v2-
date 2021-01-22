#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT1, ratio18_1, false);
motor leftMotorB = motor(PORT2, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT3, ratio18_1, true);
motor rightMotorB = motor(PORT4, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial TurnGyroSmart = inertial(PORT9);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart, 319.19, 320, 40, mm, 1);
motor IntakeLeft = motor(PORT6, ratio18_1, false);
motor IntakeRight = motor(PORT5, ratio18_1, false);
motor EscalatorRamp = motor(PORT8, ratio18_1, false);
motor Sorter = motor(PORT7, ratio18_1, false);
/*vex-vision-config:begin*/
signature FrontVision__RED_BALL = signature (1, 2249, 9645, 5947, -811, 1, -405, 1, 0);
signature FrontVision__BLUE_BALL = signature (2, -3111, -1821, -2466, 6795, 12309, 9552, 3, 0);
signature FrontVision__GOAL = signature (3, -5857, -5621, -5739, -5687, -5257, -5472, 4.6, 0);
signature FrontVision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature FrontVision__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature FrontVision__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature FrontVision__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision FrontVision = vision (PORT10, 50, FrontVision__RED_BALL, FrontVision__BLUE_BALL, FrontVision__GOAL, FrontVision__SIG_4, FrontVision__SIG_5, FrontVision__SIG_6, FrontVision__SIG_7);
/*vex-vision-config:end*/
/*vex-vision-config:begin*/
signature InnerVision__RED_BALL = signature (1, 1519, 6827, 4173, -989, -143, -566, 1, 0);
signature InnerVision__BLUE_BALL = signature (2, -2613, -1739, -2176, 6629, 10877, 8753, 2.5, 0);
signature InnerVision__GOAL = signature (3, -5269, -4659, -4964, -4775, -4017, -4396, 2.5, 0);
vision InnerVision = vision (PORT20, 50, InnerVision__RED_BALL, InnerVision__BLUE_BALL, InnerVision__GOAL);
/*vex-vision-config:end*/
bumper BallDetector = bumper(Brain.ThreeWirePort.G);
controller Controller1 = controller(primary);
limit TeamSwitcher = limit(Brain.ThreeWirePort.H);
pot ModePotentiometer = pot(Brain.ThreeWirePort.F);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}