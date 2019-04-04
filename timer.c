#include <avr/io.h>
#include <avr/interrupt.h>

#include "common.h"
#include "timer.h"

uint16_t timer_count;
uint16_t timer_count_save;
uint8_t  timer_repeat_flag;
uint8_t  timer_expire_flag;

//----------------------------------------------------------------------------------------------------
// timer interrupt handler
//----------------------------------------------------------------------------------------------------
ISR(TIMER1_COMPA_vect)
	{
	PROVIDE_ENTRY(TIMER1_COMPA_vect);

	// timer not expired
	if (timer_count > 0)
		timer_count--;

	// timer expired
	else
		{
		// set expire flag
		timer_expire_flag = 1;

		// timer expired - no repeat
		if (timer_repeat_flag == TIMER_REPEAT_FALSE)
			TCCR1B |= TIMER_PRS_0;           // turn off timer

		// timer expired - repeat
		else
			timer_count = timer_count_save;  // reload counter
		}
	}

//----------------------------------------------------------------------------------------------------
// start timer
//----------------------------------------------------------------------------------------------------
int8_t timer_start(uint16_t count, uint8_t unit, uint8_t repeat_flag)
	{
	// set timer variables
	timer_count_save  = count;
	timer_count       = timer_count_save;
	timer_repeat_flag = repeat_flag;
	timer_expire_flag = 0;

        // set up timer
        TCCR1A  = 0;               // clear timer 1 control register A
        TCCR1B  = 0;               // clear timer 1 control register B
        TCNT1   = 0;               // reset timer 1 counter value
        TCCR1B |= (1 << WGM12);    // turn on CTC mode (clear timer on compare match)
        TIMSK1 |= (1 << OCIE1A);   // enable timer compare interrupt

	// set frequency
	switch (unit)
		{
		// seconds
		case TIMER_UNIT_SEC:
			OCR1A   = TIMER_CMP_SEC;
			TCCR1B |= TIMER_PRS_SEC;
			break;

		// milliseconds
		case TIMER_UNIT_MSEC:
			OCR1A   = TIMER_CMP_MSEC;
			TCCR1B |= TIMER_PRS_MSEC;
			break;

		// microseconds
		case TIMER_UNIT_USEC:
			OCR1A   = TIMER_CMP_USEC;
			TCCR1B |= TIMER_PRS_USEC;
			break;

		default:
			return -1;
		}

	return 0;
	}

//----------------------------------------------------------------------------------------------------
// timer check
//----------------------------------------------------------------------------------------------------
uint8_t timer_check(void)
	{
	// if timer expired clear flag
	if (timer_expire_flag)
		{
		timer_expire_flag = 0;
		return 1;
		}

	// timer not expired
	return 0;
	}
