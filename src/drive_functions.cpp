#include "vex.h"
#include "drive_functions.h"

// Driver Control
const int intakePower = 100;
const int escalatorPower = 100;
const int sorterPower = 100;
const int drivetrainPower = 50;
const int drivetrainTurnPower = 100;

// Autonomous
const int intakePowerAuto = 100;
const int escalatorPowerAuto = 100;
const int drivetrainPowerAuto = 50;
const int sorterPowerAuto = 100;
const int drivetrainTurnPowerAuto = 50;

//Skills
const int drivetrainPowerAutoSkills = 40;

bool slowmode = false;

void driveForTime (directionType dir, int number, timeUnits units)
{
  Drivetrain.drive(dir);
  wait(number, units);
  Drivetrain.stop();
}

Intake::Intake (motor& left, motor& right) : leftMotor(left), rightMotor(right) {}

void Intake::inward ()
{
  leftMotor.spin(reverse);
  rightMotor.spin(forward);
}

void Intake::outward ()
{
  leftMotor.spin(forward);
  rightMotor.spin(reverse);
}

void Intake::off ()
{
  leftMotor.stop();
  rightMotor.stop();
}

void Intake::setPower (int pow)
{
  leftMotor.setVelocity(pow, percent);
  rightMotor.setVelocity(pow, percent);
}

Escalator::Escalator (motor& m, motor& s) : assignedMotor(m), sorterMotor(s) {}

void Escalator::off ()
{
  is_running = false;
  assignedMotor.stop();
  sorterMotor.stop();
}


void Escalator::up ()
{
  is_running = true;  
  assignedMotor.spin(forward);
  sorterMotor.spin(sorterDirection);
}

void Escalator::down ()
{
  is_running = true;
  assignedMotor.spin(reverse);
  sorterMotor.spin(sorterDirection);
}

void Escalator::toggle ()
{
  if (is_running)
  {
    off();
  } else
  {
    if (dir > 0)
    {
      up();
    } else
    {
      down();
    }
  }
}

void Escalator::setPower (int pow)
{
  assignedMotor.setVelocity(pow, percent);
  sorterMotor.setVelocity(pow, percent);
}

void Escalator::setSorterDirection (directionType dir)
{
  sorterDirection = dir;
  if (is_running)
  {
    sorterMotor.spin(dir);
  } else
  {
    sorterMotor.stop();
  }
}

Intake intake (IntakeLeft, IntakeRight);
Escalator escalator (EscalatorRamp, Sorter);

void depositBalls (int number)
{
  escalator.up();
  wait(number, sec);
  escalator.off();
}

void removeBalls (int number)
{
  intake.inward();
  escalator.up();
  wait(number, sec);
  intake.off();
  escalator.off();
}

void descoreCompletely ()
{
  int descored = 0;
  int maxDescored = 3;
  int maxAttempts = 5;

  intake.inward();
  escalator.up();
  for (int attempts = 0; attempts < maxAttempts && descored < maxDescored; attempts++)
  {
    Drivetrain.drive(forward);
    wait(500, msec);
    Drivetrain.driveFor(reverse, 6, inches);
    if (BallDetector.pressing())
    {
      descored++;
    }
    wait(500, msec);

    if (descored == 0 && attempts >= 3)
    {
      driveForTime(forward, 500, msec);
    }
  }
  Drivetrain.driveFor(reverse, 6, inches);
  Drivetrain.turnFor(left, 180, degrees);
  wait(4, sec);
  intake.off();
  escalator.off();
}

void toggleSlowModeAuto (int amount)
{
  slowmode = !slowmode;
  if (slowmode)
  {
    Drivetrain.setDriveVelocity(drivetrainPowerAuto / amount, percent);
  } else
  {
    Drivetrain.setDriveVelocity(drivetrainPowerAuto, percent);
  }
}

void shimmy (int timeAmountForward, int timeAmountBackward, timeUnits units, int iterations, int waitTime)
{
  for (int i = 0; i < iterations; i++) 
  {
    escalator.off();
    driveForTime(reverse, timeAmountForward, units);
    escalator.up();
    driveForTime(forward, timeAmountBackward, units);
    wait(waitTime, units);
  }
}