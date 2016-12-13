#ifndef scheduler_h
#define scheduler_h
#include "Arduino.h"

// timers
const unsigned long TIMER_A = 100; // 100 msec
const unsigned long TIMER_B = 1000; // 1sec
const unsigned long TIMER_C = 5000; // 5sec

// function pointer
typedef void (*Function) ();

void set_tasks(Function task_a, Function task_b, Function task_c);
void scheduler_loop();

#endif
