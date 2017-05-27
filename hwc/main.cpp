/*
 * hwc.cpp
 *
 * Created: 2017.02.08. 20:46:19
 * Author : huszty
 * Chop   : ATTINY45 @ 1MHz
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "SoftTimerSet.h"
#include "TimedOutput.h"

#include "Trigger.h"

//Config BEGIN
#define OUTPUT_ON_TIME 120
#define TRIGGER_HOLD_OFF_TIME 1200
//Config END

#define OUTPUT_PORT_MASK 1<<4
#define INIT_OUTPUT()  DDRB|=OUTPUT_PORT_MASK;                                 // PORTB3 -> output
#define INIT_TRIGGER() PORTB|=1<<2;MCUCR|=1<<ISC01;GIMSK|=1<<INT0; // PORTB2 -> input (by default), activate pull-up and falling edge interrupt

#define INIT_TIMER0() TCCR0B|=1<<CS02|1<<CS00;TIMSK|=1<<TOIE0; // Set TIMER0 prescaler to 1024; this will cause 3.8 tick/sec (~4HZ)
#define SECOND_PRESCALER 4
volatile unsigned int overflow_counter = 0;

SoftTimerSet<2> gSoftTimerSet;
Trigger *gTrigger = 0;

ISR(TIMER0_OVF_vect) {
  if(++overflow_counter == SECOND_PRESCALER) {
    gSoftTimerSet.tick();
    overflow_counter = 0;
  }
}

ISR(INT0_vect) {
  gTrigger->activate();
}

int main(void) {
  INIT_OUTPUT();
  INIT_TRIGGER();
  INIT_TIMER0();
  TimedOutput output((volatile void *)&PORTB, OUTPUT_PORT_MASK, OUTPUT_ON_TIME);
  gSoftTimerSet.add(&output);
  Trigger trigger(&output, TRIGGER_HOLD_OFF_TIME);
  gSoftTimerSet.add(&trigger);
  gTrigger = &trigger;
  sei();
  while(1);
}

