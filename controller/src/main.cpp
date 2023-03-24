#include <Arduino.h>
#include <Wire.h>
#include "i2c.h"
#include "clock_state.h"

const int I2C_ADDR[3]  = {0x08, 0x09, 0x10};
const t_clock default_clock = {0, 0, 0, 0, 0, 0, 0, 0};
t_full_clock clocks;

uint16_t counter = 1;
int clock_addr_index = 0;


void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  Wire.begin();

  clocks = {{default_clock, default_clock, default_clock, default_clock}};
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i < 4; i++)
  {
      clocks.clocks[i].speed_h = 2000;
      clocks.clocks[i].speed_m = 2000;
      clocks.clocks[i].accel_h = 500;
      clocks.clocks[i].accel_m = 500;
      clocks.clocks[i].direction_h = 0;
      clocks.clocks[i].direction_m = 1;
  }
}


// the loop function runs over and over again forever
void loop()
{
  // Read serial, and have 3 commands to send to the arduino

      for (int i = 0; i < 4; i++)
      {
        clocks.clocks[i].angle_h = 0;
        clocks.clocks[i].angle_m = 0;
        clocks.clocks[i].direction_h = random(1);
        clocks.clocks[i].direction_m = random(1);
      }

      for (int i = 0; i < 2; i++)
        {
         t_half_clock to_send;
          to_send.clocks[0] = clocks.clocks[0 + i];
          to_send.clocks[1] = clocks.clocks[1 + i];
          to_send.change_counter[0] = counter;
          to_send.change_counter[1] = counter;


          Wire.beginTransmission(I2C_ADDR[clock_addr_index]);
          I2C_writeAnything(to_send);
          Wire.endTransmission();
      }
      

     
      clock_addr_index++;
      counter++;

      if (clock_addr_index > 2)
          clock_addr_index = 0;

      delay(2000);
  
}