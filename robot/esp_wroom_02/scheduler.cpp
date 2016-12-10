#include "Arduino.h"
#include "scheduler.h"

// task scheduller

// null tasks
void null_task_a() {};
void null_task_b() {};
void null_task_c() {};

// default tasks
Function t_a = null_task_a;
Function t_b = null_task_b;
Function t_c = null_task_c;

// schduling timers
unsigned long now = millis();
unsigned long prev_a = now;
unsigned long prev_b = now;
unsigned long prev_c = now;

// set tasks to be scheuled
void set_tasks(Function task_a, Function task_b, Function task_c) {
  if (task_a != NULL) {
    t_a = task_a;
  }
  if (task_b != NULL) {
    t_b = task_b;
  }
  if (task_c != NULL) {
    t_c = task_c;
  }
}

// call this function from loop() to execute periodic tasks
void scheduler_loop() {
  // Periodic tasks
  now = millis();
  // TIMER_A
  if (now - prev_a >= TIMER_A) {
    t_a();
    prev_a = prev_a + TIMER_A;
  }
  // TIMER_B
  if (now - prev_b >= TIMER_B) {
    t_b();
    prev_b = prev_b + TIMER_B;
  }
  // TIMER_C
  if (now - prev_c >= TIMER_C) {
    t_c();
    prev_c = prev_c + TIMER_C;
  }
}

