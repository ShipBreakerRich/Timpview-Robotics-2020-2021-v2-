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
#include "drive-functions.h"
#include "vision-functions.h"

using namespace vex;

void driverControl ()
{
  //Intake system
  Controller1.ButtonL2.pressed([](){intake.inward();});
  Controller1.ButtonL2.released([](){intake.off();});
  Controller1.ButtonL1.pressed([](){intake.outward();});
  Controller1.ButtonL1.released([](){intake.off();});

  //Escalator system
  Controller1.ButtonR2.pressed([](){escalator.toggleOrSwitch(1);});
  Controller1.ButtonR1.pressed([](){escalator.toggleOrSwitch(-1);});
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  driveForTime(forward, 1, sec);
}
