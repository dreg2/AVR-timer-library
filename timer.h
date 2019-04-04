#ifndef TIMER_H_
#define TIMER_H_

extern uint16_t timer_count;

// timer prescaler bit values for bits CSn2-CSn0 in TCCRnB register (valid for counters 0 and 1)
#define TIMER_PRS_MASK  (uint8_t)0x07  // prescaler bits mask
#define TIMER_PRS_0     (uint8_t)0x00  // Timer prescaler = 0 (timer stopped)
#define TIMER_PRS_1     (uint8_t)0x01  // Timer prescaler = 1
#define TIMER_PRS_8     (uint8_t)0x02  // Timer prescaler = 8
#define TIMER_PRS_64    (uint8_t)0x03  // Timer prescaler = 64
#define TIMER_PRS_256   (uint8_t)0x04  // Timer prescaler = 256
#define TIMER_PRS_1024  (uint8_t)0x05  // Timer prescaler = 1024
#define TIMER_EXT_FE    (uint8_t)0x06  // Timer on Tn falling edge
#define TIMER_EXT_RE    (uint8_t)0x07  // Timer on Tn rising edge

// timer prescaler bit values for bits CS22-CS20 in TCCR2B register (valid for counter 2)
#define TIMER2_PRS_MASK (uint8_t)0x07  // prescaler bits mask
#define TIMER2_PRS_0    (uint8_t)0x00  // Timer prescaler = 0 (timer stopped)
#define TIMER2_PRS_1    (uint8_t)0x01  // Timer prescaler = 1
#define TIMER2_PRS_8    (uint8_t)0x02  // Timer prescaler = 8
#define TIMER2_PRS_32   (uint8_t)0x03  // Timer prescaler = 32
#define TIMER2_PRS_64   (uint8_t)0x04  // Timer prescaler = 64
#define TIMER2_PRS_128  (uint8_t)0x05  // Timer prescaler = 128
#define TIMER2_PRS_256  (uint8_t)0x06  // Timer prescaler = 256
#define TIMER2_PRS_1024 (uint8_t)0x07  // Timer prescaler = 1024


// compare and prescaler values (compare = ((F_CPU / prescaler) / freq) - 1)
// seconds
#define TIMER_UNIT_SEC  0
#define TIMER_CMP_SEC   62499
#define TIMER_PRS_SEC   TIMER_PRS_256
// milliseconds
#define TIMER_UNIT_MSEC 1
#define TIMER_CMP_MSEC  249
#define TIMER_PRS_MSEC  TIMER_PRS_64
// microseconds
#define TIMER_UNIT_USEC 2
#define TIMER_CMP_USEC  15
#define TIMER_PRS_USEC  TIMER_PRS_1

// flag values
#define TIMER_REPEAT_FALSE 0
#define TIMER_REPEAT_TRUE  1

// functions
ISR(TIMER1_COMPA_vect);
int8_t  timer_start(uint16_t count, uint8_t unit, uint8_t repeat_flag);
uint8_t timer_check(void);

#endif // TIMER_H_
