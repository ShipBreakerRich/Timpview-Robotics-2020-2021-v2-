#ifndef MODE_SELECTOR_H_
#define MODE_SELECTOR_H_

#include "vex.h"

class ModeSelector
{
  public:
    ModeSelector (pot& p, int n);
    int mode ();

  private:
    pot& potentiometer;
    int num_modes;
};

#endif