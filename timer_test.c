#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <stdio.h>
#include "common.h"
#include "timer.h"
#include "uart.h"

#define LED_PIN     (1 << PINB5)      // arduino led is on pin PB5
#define TIMER_COUNT 500               // timer count
#define TIMER_UNIT  TIMER_UNIT_MSEC   // timer units

//----------------------------------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------------------------------
int main(void)
	{
	uart_init_baud(); // initialize uart

	// set up led pin
	DDRB |= LED_PIN;       // set led pin for output

	// set up sleep mode
	SMCR = SLEEP_MODE_IDLE; // set sleep mode to idle
	sei();                  // enable interrupts
printf("initialized\n");

	// start timer
	timer_start(TIMER_COUNT, TIMER_UNIT, TIMER_REPEAT_TRUE);
//	timer_start(TIMER_COUNT, TIMER_UNIT, TIMER_REPEAT_FALSE);
		
	while(1)
		{
		if (timer_check())
			{
			PORTB ^= LED_PIN;   // toggle led
//			timer_start(TIMER_COUNT, TIMER_UNIT, TIMER_REPEAT_FALSE);
			}

		sleep_mode(); // sleep until interrupt
		}
	}
