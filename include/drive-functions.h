#include "vex.h"

// Driver Control
extern const int intakePower;
extern const int escalatorPower;
extern const int rampPower;
extern const int drivetrainPower;
extern const int drivetrainTurnPower;

// Autonomous
extern const int intakePowerAuto;
extern const int escalatorPowerAuto;
extern const int rampPowerAuto;
extern const int drivetrainPowerAuto;
extern const int drivetrainTurnPowerAuto;

//Skills
extern const int drivetrainPowerAutoSkills;

void driveForTime (vex::directionType dir, int number, vex::timeUnits units) {}

class Intake {
  protected:
    motor& leftMotor;
    motor& rightMotor;

  public:
    Intake (motor& left, motor& right);
    void inward () {}
    void outward () {}
    void off () {}
    void setPower (int pow) {}
};

class Escalator {
  protected:
    motor& assignedMotor;
    void up () {}
    void down () {}

  public:
    bool is_running;
    int dir;
    Escalator (motor& m);
    void off () {}
    void toggleOrSwitch (int newDir) {}
    void toggle () {}
    void setPower (int pow) {}
};

extern Intake intake;
extern Escalator escalator;

void depositBalls (int number) {}

void removeBalls (int number) {}

void descoreCompletely () {}