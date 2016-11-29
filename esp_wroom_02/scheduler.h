#ifndef scheduler_h
#define scheduler_h
#include "Arduino.h"

typedef void (*Function) ();

void set_tasks(Function task_a, Function task_b, Function task_c);
void scheduler_loop();

#endif
