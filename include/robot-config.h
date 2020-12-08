using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern smartdrive Drivetrain;
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor EscalatorRamp;
extern motor Sorter;
extern signature FrontVision__SIG_1;
extern signature FrontVision__SIG_2;
extern signature FrontVision__SIG_3;
extern signature FrontVision__SIG_4;
extern signature FrontVision__SIG_5;
extern signature FrontVision__SIG_6;
extern signature FrontVision__SIG_7;
extern vision FrontVision;
extern signature InnerVision__SIG_1;
extern signature InnerVision__SIG_2;
extern signature InnerVision__SIG_3;
extern signature InnerVision__SIG_4;
extern signature InnerVision__SIG_5;
extern signature InnerVision__SIG_6;
extern signature InnerVision__SIG_7;
extern vision InnerVision;
extern bumper BallDetector;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );