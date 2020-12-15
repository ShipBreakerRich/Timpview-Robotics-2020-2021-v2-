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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drive_functions.h"
#include "vision_functions.h"

using namespace vex;

// Run Settings
const bool skills = true;
const signature& allySignature = FrontVision__RED_BALL;
const signature& enemySignature = FrontVision__BLUE_BALL;
const signature& allySignatureInner = InnerVision__RED_BALL;
const signature& enemySignatureInner = InnerVision__BLUE_BALL;
// 0 = left corner | 1 = middle | 2 = right corner
const int autoStrategy = 0;

//Define competition object
competition Competition;

void checkSorter ()
{
  while (Competition.isAutonomous() || Competition.isDriverControl())
  {
    Controller1.Screen.setCursor(0, 0);
    if (detectSignatureInner(enemySignatureInner))
    {
      escalator.setSorterDirection(reverse);
    }
    else
    {
      escalator.setSorterDirection(forward);
    }
  }
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
  escalator.dir = 1;

  thread(checkSorter).detach();
  
  Competition.drivercontrol(driverControl);

  if (skills) Competition.autonomous(skillsAutonomous); else Competition.autonomous(autonomousMode);
}
