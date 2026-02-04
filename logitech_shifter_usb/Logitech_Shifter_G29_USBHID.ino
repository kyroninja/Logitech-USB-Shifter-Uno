/*
 * Logitech Driving Force Shifter – ATmega16U2 / USB HID side
 * HoodLoader2 + HID-Project
 *
 * Gamepad with exactly 8 buttons:
 *   1–6  = gears
 *   7    = reverse
 *   8    = neutral
 *
 * Uses Gamepad.begin() + Gamepad.write() for reliable reports
 */

#include "HID-Project.h"

void setup() 
{
  // Fast communication from 328P
  Serial1.begin(115200);

  // Initialize gamepad
  Gamepad.begin();

  // Reinit to zero
  Gamepad.rxAxis(0);
  Gamepad.ryAxis(0);
  Gamepad.rzAxis(0);

  Gamepad.xAxis(0);
  Gamepad.yAxis(0);
  Gamepad.zAxis(0);
  
  Gamepad.dPad1(GAMEPAD_DPAD_CENTERED);
  Gamepad.dPad2(GAMEPAD_DPAD_CENTERED);

  // Optional: initial report to clear state
  Gamepad.write();
}

void loop() 
{
  static uint8_t currentGear = 0;

  if (Serial1.available()) 
  {
    uint8_t gear = Serial1.read();

    if (gear != currentGear) 
    {
      // Release all 8 buttons first
      //for (uint8_t i = 1; i <= 8; i++) 
      //{
      //  Gamepad.release(i);
      //}

      // Release all 8 buttons first
      for (uint8_t i = 1; i <= 7; i++) 
      {
        Gamepad.release(i); //removed the explicit neutral
      }

      // Press the new button (1–8)
      //if (gear >= 1 && gear <= 8) 
      //{
      //  Gamepad.press(gear);
      //}

      // Press the new button (1–7)
      if (gear >= 1 && gear <= 7) 
      {
        Gamepad.press(gear); //removed the explicit neutral
      }

      // Force send the HID report immediately
      Gamepad.write();

      currentGear = gear;
    }
  }
}
