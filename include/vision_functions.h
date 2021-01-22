#ifndef VISION_FUNCTIONS_H_
#define VISION_FUNCTIONS_H_

#include "vex.h"

extern int centerX;
extern int centerY;
extern int collectedW;
extern int slack;

void centerOn (vision::signature type);

void collectSignature (vision::signature inner_type, vision::signature front_type, int threshold);

vision::object detectSignature (vision::signature sig);

vision::object detectSignatureInner (vision::signature sig);

#endif