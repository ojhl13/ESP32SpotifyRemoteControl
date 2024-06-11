#ifndef TOUCHBUTTON
#define TOUCHBUTTON
#include <Arduino.h>
#define BUTTON1 16
#define BUTTON2 17
#define BUTTON3 16
#define BUTTON4 17
#define BOUNCE_TIME 250
struct Button {
  uint8_t PIN;
  volatile uint32_t numberKeyPresses;
  volatile int pressed;
  unsigned long button_time;  
  unsigned long last_button_time; 
};

extern struct Button button1;// = {BUTTON1, 0, 0,0,0};
extern struct Button button2;// = {BUTTON2, 0, 0,0,0}
extern struct Button button3;// = {BUTTON1, 0, 0,0,0};
extern struct Button button4;// = {BUTTON2, 0, 0,0,0}
void setup_buttons();
void checkPressed(struct Button* button);
void isr(void* param);

#endif
