#include "vex.h"

// Driver Control
const int intakePower = 100;
const int escalatorPower = 100;
const int rampPower = 100;
const int drivetrainPower = 50;
const int drivetrainTurnPower = 100;

// Autonomous
const int intakePowerAuto = 100;
const int escalatorPowerAuto = 100;
const int rampPowerAuto = 100;
const int drivetrainPowerAuto = 100;
const int drivetrainTurnPowerAuto = 50;

//Skills
const int drivetrainPowerAutoSkills = 40;

void driveForTime (vex::directionType dir, int number, vex::timeUnits units)
{
  Drivetrain.drive(dir);
  wait(number, units);
  Drivetrain.stop();
}

class Intake {
  protected:
    motor& leftMotor;
    motor& rightMotor;

  public:
    Intake (motor& left, motor& right) : leftMotor(left), rightMotor(right) {}

    void inward ()
    {
      leftMotor.spin(directionType::rev);
      rightMotor.spin(directionType::fwd);
    }

    void outward ()
    {
      leftMotor.spin(directionType::fwd);
      rightMotor.spin(directionType::rev);
    }

    void off ()
    {
      leftMotor.stop();
      rightMotor.stop();
    }

    void setPower (int pow)
    {
      leftMotor.setVelocity(pow, velocityUnits::pct);
      rightMotor.setVelocity(pow, velocityUnits::pct);
    }
};

class Escalator {
  protected:
    motor& assignedMotor;

  public:
    bool is_running;
    int dir;

    Escalator (motor& m) : assignedMotor(m) {}

    void off ()
    {
      is_running = false;
      assignedMotor.stop();
    }

    
    void up ()
    {
      is_running = true;  
      assignedMotor.spin(directionType::fwd);
    }

    void down ()
    {
      is_running = true;
      assignedMotor.spin(directionType::rev);
    }

    void toggleOrSwitch (int newDir)
    {      
      if (is_running)
      {
        if (newDir != dir)
        {
          if (newDir > 0)
          {
            up();
          } else
          {
            down();
          }
        } else 
        {
          off();
        }
      } else
      {
        if (newDir > 0)
        {
          up();
        } else
        {
          down();
        }
      }
      dir = newDir;
    }

    void toggle ()
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

    void setPower (int pow)
    {
      Brain.Screen.print(pow);
      assignedMotor.setVelocity(pow, velocityUnits::pct);
    }
};

Intake intake (IntakeLeft, IntakeRight);
Escalator escalator (EscalatorRamp);

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