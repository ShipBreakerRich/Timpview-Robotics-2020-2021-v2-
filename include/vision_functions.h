#ifndef VISION_FUNCTIONS_H_
#define VISION_FUNCTIONS_H_

#include "vex.h"

extern int centerX;
extern int centerY;
extern int collectedW;
extern int slack;

void centerOn (vision::signature type);

void collectSignature (vision::signature front_type);

bool detectSignature (vision::signature sig);

bool detectSignatureInner (vision::signature sig);

#endif