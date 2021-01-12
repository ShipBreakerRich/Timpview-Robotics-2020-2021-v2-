/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mm023739                                         */
/*    Created:      Tue Dec 08 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 3, 4, 9   
// IntakeLeft           motor         5               
// IntakeRight          motor         6               
// EscalatorRamp        motor         8               
// Sorter               motor         7               
// FrontVision          vision        10              
// InnerVision          vision        20              
// BallDetector         bumper        G               
// Controller1          controller                    
// TeamSwitcher         limit         H               
// ModePotentiometer    pot           F               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drive_functions.h"
#include "vision_functions.h"
#include "mode_selector.h"

using namespace vex;

// Run Settings
const bool skills = true;

signature* allySignatureInner;
signature* enemySignatureInner;

signature* allySignature;
signature* enemySignature;

//Define competition object
competition Competition;
ModeSelector modeSelector(ModePotentiometer, 4);

//Modes:
//0: Left Corner
//1: 
//2: Right Corner
//3: 

void checkSorter ()
{
  while (Competition.isAutonomous() || Competition.isDriverControl())
  {
    if (enemySignatureInner)
    {
      escalator.setSorterDirection(reverse);
    }
    else
    {
      escalator.setSorterDirection(forward);
    }
  }
}

void autonomousConfig()
{
  // Set Autonomous Specific Speeds
  EscalatorRamp.setVelocity(escalatorPowerAuto, velocityUnits::pct);
  IntakeLeft.setVelocity(intakePowerAuto, velocityUnits::pct);
  IntakeRight.setVelocity(intakePowerAuto, velocityUnits::pct);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, velocityUnits::pct);
  Drivetrain.setTurnVelocity(drivetrainTurnPowerAuto, velocityUnits::pct);
}

void cornerStrategy ()
{
  int angleModifier = modeSelector.mode() == 0 ? 1 : -1;
  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnFor(left, 135*angleModifier, degrees);
  centerOn(*allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
  collectSignature(*allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  if (modeSelector.mode() == 2)
  {
    Drivetrain.driveFor(forward, 6, inches);
  }
  centerOn(FrontVision__GOAL);
  intake.outward();
  Drivetrain.drive(forward);
  wait(500, msec);
  Drivetrain.stop();
  escalator.up();
  wait(3, sec);
  Drivetrain.driveFor(reverse, 6, inches);
  Drivetrain.driveFor(forward, 6, inches);
  wait(1, sec);
  Drivetrain.driveFor(reverse, 6, inches);
  wait(2, sec);
  intake.outward();
  escalator.off();
}

void driverControl ()
{
  //Intake system
  Controller1.ButtonL2.pressed([](){intake.inward();});
  Controller1.ButtonL2.released([](){intake.off();});
  Controller1.ButtonL1.pressed([](){intake.outward();});
  Controller1.ButtonL1.released([](){intake.off();});

  //Escalator system
  Controller1.ButtonA.pressed([](){escalator.toggle();});
}

void skillsAutonomous ()
{
  autonomousConfig();

  Drivetrain.setDriveVelocity(drivetrainPowerAutoSkills, percent);

  depositBalls(1);

  Drivetrain.driveFor(reverse, 12, inches);
  Drivetrain.turnFor(left, 135, degrees);
  Drivetrain.driveFor(forward, 48, inches);
  Drivetrain.turnFor(right, 90, degrees);
  centerOn(*enemySignature);
  driveForTime(forward, 750, msec);
  wait(500, msec);
  descoreCompletely();
  Drivetrain.driveFor(forward, 18, inches);
  Drivetrain.turnFor(right, 130, degrees);
  driveForTime(forward, 1, sec);
  centerOn(*enemySignature);
  driveForTime(forward, 1, sec);
  centerOn(*enemySignature);
  driveForTime(forward, 750, msec);
  centerOn(*enemySignature);
  driveForTime(forward, 750, msec);
  centerOn(*enemySignature);
  descoreCompletely();
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.turnFor(right, 45, degrees);
  Drivetrain.driveFor(forward, 40, inches);
  Drivetrain.turnFor(right, 90, degrees);
  centerOn(*enemySignature);
  driveForTime(forward, 1, sec);
  descoreCompletely();
  Drivetrain.driveFor(forward, 6, inches);
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 36, inches);
  Drivetrain.turnFor(right, 45, degrees);
  centerOn(*enemySignature);
  driveForTime(forward, 1, sec);
  descoreCompletely();
}

void autonomousMode ()
{
  autonomousConfig();

  switch (modeSelector.mode())
  {
    case (0):
    case (2):
      cornerStrategy();
    break;
    case (1):
      intake.inward();
      Drivetrain.driveFor(forward, 5, inches);
      depositBalls(1);
      intake.outward();
      Drivetrain.driveFor(reverse, 40, inches);
      Drivetrain.turnFor(right, 100, degrees);
      centerOn(*allySignature);
      intake.off();
      escalator.up();
      intake.outward();
      Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
      collectSignature(*allySignature);
      Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
      wait(1500, msec);
      depositBalls(1);
      removeBalls(2);
    break;
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  allySignatureInner = TeamSwitcher.pressing() ? &InnerVision__RED_BALL : &InnerVision__BLUE_BALL;
  enemySignatureInner = TeamSwitcher.pressing() ? &InnerVision__BLUE_BALL : &InnerVision__RED_BALL;

  allySignature = TeamSwitcher.pressing() ? &FrontVision__RED_BALL : &FrontVision__BLUE_BALL;
  enemySignature = TeamSwitcher.pressing() ? &FrontVision__BLUE_BALL : &FrontVision__RED_BALL;

  intake.setPower(intakePower);
  escalator.setPower(escalatorPower);
  Sorter.setVelocity(sorterPower, percent);
  Drivetrain.setDriveVelocity(drivetrainPower, percent);
  Drivetrain.setTurnVelocity(drivetrainTurnPower, percent);
  escalator.dir = 1;

  thread(checkSorter).detach();
  
  Competition.drivercontrol(driverControl);

  if (skills) Competition.autonomous(skillsAutonomous); else Competition.autonomous(autonomousMode);
}
