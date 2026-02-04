/*
 * Logitech Driving Force Shifter – ATmega328P side
 * HoodLoader2 + HID-Project compatible
 *
 * Pinout (your wiring):
 *   DB9 Pin 2 → A0     X-axis
 *   DB9 Pin 4 → D2     Reverse switch
 *   DB9 Pin 6 → GND    Ground
 *   DB9 Pin 8 → A2     Y-axis
 *   DB9 Pin 9 → 5V     Power
 *   DB9 Pin 3 → 5V     Power
 *   DB9 Pin 7 → 5V     Power
 *
 * Calibration ranges:
 *   X: left ≈ 257, right ≈ 700
 *   Y: forward/up/high ≈ 850 (top row 1-3-5)
 *   Y: back/down/low  ≈  70 (bottom row 2-4-6 + R)
 *
 * Mapping:
 *   1–6  = gears
 *   7    = reverse
 *   8    = neutral (explicit button when no gear engaged)
 */

#define X_PIN     A0
#define Y_PIN     A2
#define REV_PIN   2

// Thresholds tuned to your min/max
#define X_LEFT_MAX    380
#define X_RIGHT_MIN   580
#define Y_TOP_MIN     540    // high Y = top/forward row (1,3,5)
#define Y_BOTTOM_MAX  380    // low Y  = bottom/back row (2,4,6,R)

void setup() {
  pinMode(REV_PIN, INPUT_PULLUP);
  Serial.begin(115200);         // fast to 16U2
}

void loop() {
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  bool revPressed = (digitalRead(REV_PIN) == LOW);   // LOW = pressed/down

  uint8_t gear = 0;   // 0 = neutral, 1–6 = gears, 7 = reverse, 8 = neutral (explicit)

  // Top/forward row (high Y)
  if (y >= Y_TOP_MIN) 
  {
    if (x <= X_LEFT_MAX)
    {
      gear = 1;
    } 
    else if (x >= X_RIGHT_MIN) 
    {
      gear = 5;
    }
    else                       
    {
      gear = 3;
    }
  }

  // Bottom/back row (low Y)
  else if (y <= Y_BOTTOM_MAX) 
  {
    if      (x <= X_LEFT_MAX)  
    {
      gear = 2;
    }
    else if (x >= X_RIGHT_MIN) 
    {
      if (!revPressed)          
      { 
        gear = 7;   // reverse
      }
      else                     
      {
        gear = 6;   // gear 6
      }
    }
    else                       
    {
      gear = 4;
    }
  }
  // Middle / no row match → neutral
  else {
    gear = 8;   // explicit neutral button
  }

  static uint8_t lastGear = 255;
  if (gear != lastGear) {
    Serial.write(gear);
    lastGear = gear;
  }

  delay(10);   // fast polling
}