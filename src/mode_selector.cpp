#include "vex.h"
#include "mode_selector.h"

ModeSelector::ModeSelector (pot& p, int n) : potentiometer(p), num_modes(n)  {}

int ModeSelector::mode ()
{
  int val = potentiometer.value(percent) / (100/num_modes);
  
  return std::max(0, std::min(val,num_modes-1));
}