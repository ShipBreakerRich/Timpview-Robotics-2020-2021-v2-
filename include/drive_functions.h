#ifndef DRIVE_FUNCTIONS_H_
#define DRIVE_FUNCTIONS_H_

#include "vex.h"

// Driver Control
extern const int intakePower;
extern const int escalatorPower;
extern const int sorterPower;
extern const int drivetrainPower;
extern const int drivetrainTurnPower;

// Autonomous
extern const int intakePowerAuto;
extern const int escalatorPowerAuto;
extern const int sorterPowerAuto;
extern const int drivetrainPowerAuto;
extern const int drivetrainTurnPowerAuto;

//Skills
extern const int drivetrainPowerAutoSkills;

void driveForTime (vex::directionType dir, int number, vex::timeUnits units);

class Intake {
  protected:
    motor& leftMotor;
    motor& rightMotor;

  public:
    Intake (motor& left, motor& right);
    void inward ();
    void outward ();
    void off ();
    void setPower (int pow);
};

class Escalator {
  protected:
    motor& assignedMotor;
    motor& sorterMotor;
    directionType sorterDirection;
  public:
    bool is_running;
    int dir;
    Escalator (motor& m, motor& s);
    void off ();
    void up ();
    void down ();
    void toggleOrSwitch (int newDir);
    void toggle ();
    void setPower (int pow);
    void setSorterDirection(directionType dir);
};

extern Intake intake;
extern Escalator escalator;

void depositBalls (int number);

void removeBalls (int number);

void descoreCompletely ();

void toggleSlowModeAuto (int amount = 2);

void shimmy (int timeAmountForward, int timeAmountBackward, vex::timeUnits units, int iterations, int waitTime = 500);
#endif