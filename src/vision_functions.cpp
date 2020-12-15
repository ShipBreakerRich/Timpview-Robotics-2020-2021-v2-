#include "drive_functions.h"
#include "vex.h"
#include "vision_functions.h"

int centerX = 150;
int centerY = 190;
int collectedW = 150;
int slack = 80;

void centerOn (vision::signature type)
{
  bool aligned = false;
  int loopCounter = 0;
  FrontVision.takeSnapshot(type);
  while (!aligned)
  {
    if (FrontVision.largestObject.exists)
    {
      if (centerX - slack > FrontVision.largestObject.centerX)
      {
        Drivetrain.turn(left);
      } 
      else if (centerX + slack < FrontVision.largestObject.centerX)
      {
        Drivetrain.turn(right);
      } 
      else 
      {
        Drivetrain.stop();
        aligned = true;
      }
      FrontVision.takeSnapshot(type);
    } else
    {
      if (++loopCounter > 5)
      {
        break;
      }
    }
  }
}

void collectSignature (vision::signature front_type)
{
  double maxCollectionTime = 5000;
  timer collectionTimer;
  intake.inward();
  while (!BallDetector.pressing() && collectionTimer.time() < maxCollectionTime)
  {
    wait(100, msec);
    centerOn(front_type);
    Drivetrain.drive(forward);
  }
  Drivetrain.stop();
  intake.off();
}

bool detectSignature (vision::signature sig)
{
  FrontVision.takeSnapshot(sig);
  return FrontVision.largestObject.exists;
}

bool detectSignatureInner (vision::signature sig)
{
  InnerVision.takeSnapshot(sig);
  return InnerVision.largestObject.exists;

}