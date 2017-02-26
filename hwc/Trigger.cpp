/* 
* Trigger.cpp
*
* Created: 2017.02.25. 19:12:17
* Author: huszty
*/


#include "Trigger.h"

Trigger::Trigger(TimedOutput *newOutput,
                 unsigned short newHoldOffTime): SoftTimerHandler(false, false, false),
                                                 output(newOutput),
                                                 holdOffTime(newHoldOffTime) {  
}

Trigger::~Trigger() {
}

void Trigger::activate() {
  if(!myTimer.get()) {
    myTimer.set(holdOffTime);
    output->start();
  }
}
