#include "strategies.h"

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
  Drivetrain.driveFor(reverse, 18, inches);
  Drivetrain.turnFor(right, 45*angleModifier, degrees);
  centerOn(*allySignature);
  intake.inward();
  driveForTime(forward, 800, msec);
  escalator.up();
  centerOn(*allySignature);
  driveForTime(forward, 300, msec);
  wait(1500, msec);
  shimmy(300, 500, msec, 3);
  wait(2, sec);
  escalator.off();
  intake.off();
  // intake.outward();
  driveForTime(reverse, 500, msec);
  


  // int angleModifier = modeSelector.mode() == 0 ? 1 : -1;
  // Drivetrain.driveFor(reverse, 36, inches);
  // Drivetrain.turnFor(left, 135*angleModifier, degrees);
  // centerOn(*allySignature);
  // Drivetrain.setDriveVelocity(drivetrainPowerAuto/3, percent);
  // collectSignature(*allySignature);
  // Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  // if (modeSelector.mode() == 2)
  // {
  //   Drivetrain.driveFor(forward, 6, inches);
  // }
  // centerOn(FrontVision__GOAL);
  // intake.outward();
  // Drivetrain.drive(forward);
  // wait(500, msec);
  // Drivetrain.stop();
  // escalator.up();
  // wait(3, sec);
  // Drivetrain.driveFor(reverse, 6, inches);
  // Drivetrain.driveFor(forward, 6, inches);
  // wait(1, sec);
  // Drivetrain.driveFor(reverse, 6, inches);
  // wait(2, sec);
  // intake.outward();
  // escalator.off();
}

void middleStrategy ()
{
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
  // collectSignature(*allySignature);
  Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  wait(1500, msec);
  depositBalls(1);
  removeBalls(2);
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