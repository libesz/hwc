/*
 * hwc.cpp
 *
 * Created: 2017.02.08. 20:46:19
 * Author : huszty
 * Chop   : ATTINY45 @ 1MHz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define TIMERSETSIZE 2

#include "SoftTimerSet.h"
#include "TimedOutput.h"

#include "Trigger.h"

//Config BEGIN
#define OUTPUT_ON_TIME 60
#define TRIGGER_HOLD_OFF_TIME 1200
//Config END

#define INIT_OUTPUT() DDRB|=1<<3;   // PORTB3 -> output
#define INIT_TRIGGER() PORTB|=1<<4; // PORTB4 -> input (by default) and activate pull-up

#define INIT_TIMER0() TCCR0B|=1<<CS02|1<<CS00;TIMSK|=1<<TOIE0; // Set TIMER0 prescaler to 1024; this will cause 3.8 tick/sec (~4HZ)
#define SECOND_PRESCALER 4
volatile unsigned int overflow_counter = 0;

SoftTimerSet gSoftTimerSet;

ISR(TIMER0_OVF_vect) {
	++overflow_counter;
	switch(overflow_counter) {
		case SECOND_PRESCALER:
    gSoftTimerSet.tick();
		overflow_counter = 0;
		break;
	}
}

int main(void) {
  INIT_OUTPUT();
  INIT_TRIGGER();
	INIT_TIMER0();
  TimedOutput output((volatile void *)&PORTB, 1<<3, OUTPUT_ON_TIME);
  gSoftTimerSet.add(&output);
  Trigger trigger(&output, TRIGGER_HOLD_OFF_TIME);
  gSoftTimerSet.add(&trigger);
	sei();
  while(1) {
	  if(!(PINB&(1<<4)))
		  trigger.activate();
  }
}

