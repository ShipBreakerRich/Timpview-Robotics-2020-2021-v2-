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
// EscalatorRamp        motor         7               
// Sorter               motor         8               
// FrontVision          vision        10              
// InnerVision          vision        11              
// BallDetector         bumper        G               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drive_functions.h"
#include "vision_functions.h"

using namespace vex;

// Run Settings
const bool skills = true;
const signature& allySignature = FrontVision__RED_BALL;
const signature& enemySignature = FrontVision__BLUE_BALL;
// 0 = left corner | 1 = middle | 2 = right corner
const int autoStrategy = 0;

//Define competition object
competition Competition;

void driverControl ()
{
  // //Intake system
  // Controller1.ButtonL2.pressed([](){intake.inward();});
  // Controller1.ButtonL2.released([](){intake.off();});
  // Controller1.ButtonL1.pressed([](){intake.outward();});
  // Controller1.ButtonL1.released([](){intake.off();});

  // //Escalator system
  // Controller1.ButtonR2.pressed([](){escalator.toggleOrSwitch(1);});
  // Controller1.ButtonR1.pressed([](){escalator.toggleOrSwitch(-1);});

  while (true)
  {
    wait(1, msec);
    if (Controller1.ButtonL2.pressing()) intake.inward(); else intake.off();
    if (Controller1.ButtonL1.pressing()) intake.outward(); else intake.off();
    if (Controller1.ButtonR1.pressing()) escalator.toggleOrSwitch(-1);
    if (Controller1.ButtonR2.pressing()) escalator.toggleOrSwitch(1);

    if (detectSignature(enemySignature)) escalator.setSorterDirection(reverse); else escalator.setSorterDirection(forward);
  }
}

void skillsAutonomous ()
{

}

void autonomousMode ()
{

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  intake.setPower(intakePower);
  escalator.setPower(escalatorPower);
  Sorter.setVelocity(sorterPower, percent);
  Drivetrain.setDriveVelocity(drivetrainPower, percent);
  Drivetrain.setTurnVelocity(drivetrainTurnPower, percent);
  
  Competition.drivercontrol(driverControl);

  if (skills) Competition.autonomous(skillsAutonomous); else Competition.autonomous(autonomousMode);
}
