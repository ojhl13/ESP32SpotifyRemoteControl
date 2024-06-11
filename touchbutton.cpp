#include "touchbutton.h"
#include <Arduino.h>



void isr(void* param) 
{
  struct Button *button = (struct Button*) param;
  button->button_time =millis();
  if (((button->button_time) - (button->last_button_time)) > BOUNCE_TIME)
  {
      button->numberKeyPresses += 1;
      button->pressed = 1;
      button->last_button_time = button->button_time;
  }
}

void checkPressed(struct Button* button) 
{
  if(button->pressed) {
    Serial.printf("Button on pin %u has been pressed %u times\n", button->PIN, button->numberKeyPresses);
    button->pressed = 0;
  }
}

;

void setup_buttons()
 {
  pinMode(button1.PIN, INPUT_PULLUP);
  pinMode(button2.PIN, INPUT_PULLUP);
  pinMode(button3.PIN, INPUT_PULLUP);
  pinMode(button4.PIN, INPUT_PULLUP);
  attachInterruptArg(button1.PIN, isr, (void*)&button1, FALLING);
  attachInterruptArg(button2.PIN, isr, (void*)&button2, FALLING);
  attachInterruptArg(button3.PIN, isr, (void*)&button1, FALLING);
  attachInterruptArg(button4.PIN, isr, (void*)&button2, FALLING);

}
