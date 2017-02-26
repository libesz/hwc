/* 
* Trigger.h
*
* Created: 2017.02.25. 19:12:17
* Author: huszty
*/


#ifndef __TRIGGER_H__
#define __TRIGGER_H__

#include "SoftTimer.h"
#include "BlinkingLed.h"

class Trigger: public SoftTimerHandler {
	Trigger( const Trigger &c );
	Trigger& operator=( const Trigger &c );
  BlinkingLed *output;
  unsigned short holdOffTime;
public:
  Trigger(BlinkingLed *newOutput, unsigned short newHoldOffTime);
  ~Trigger();
  void activate();
};

#endif //__TRIGGER_H__
