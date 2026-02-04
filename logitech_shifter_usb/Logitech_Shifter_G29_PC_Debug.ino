/*
 * Your Logitech Driving Force Shifter Pinout (as wired on your breakout board)
 * ========================================================================
 * DB9 Male breakout board plugged into shifter's female DB9
 * Uno + HoodLoader2 setup
 *
 * Your confirmed connections:
 *   DB9 Pin 2  → Uno D2     → Reverse switch (INPUT_PULLUP, LOW when handle DOWN)
 *   DB9 Pin 4  → Uno A0     → X-axis (horizontal pot, left/right)
 *   DB9 Pin 6  → Uno GND    → Ground
 *   DB9 Pin 8  → Uno A2     → Y-axis (vertical pot, forward/back)
 *   DB9 Pin 9  → Uno 5V     → +5V power for pots
 *   DB9 Pin 3  → Uno 5V     → Additional power (added to make reverse button work)
 *   DB9 Pin 7  → Uno 5V
 *
 * Calibration ranges (from your measurements):
 *   X: left ≈ 257, right ≈ 700
 *   Y: up/forward ≈ 850 (high), down/back ≈ 70 (low)
 *   Rev: raw 0 = DOWN pressed, 1 = UP released (logic inverted from typical)
 */

const int xPin   = A0;
const int yPin   = A2;  // change to A2 if Y is on A2
const int revPin = 2;

// Thresholds (midpoints with margin)
#define X_LEFT_MAX   380
#define X_RIGHT_MIN  580
#define Y_TOP_MIN    540   // high Y = top/forward row (1/3/5)
#define Y_BOTTOM_MAX 380   // low Y = bottom/back row (2/4/6 + R)

void setup() {
  Serial.begin(115200);
  pinMode(revPin, INPUT_PULLUP);
  
  Serial.println("=== SIMPLE DEBUG: RAW + GEAR ===");
  Serial.println("Format: X | Y | Rev (1=UP released, 0=DOWN pressed) | Detected Gear");
  Serial.println("Top-left = Gear 1 (high Y + left X)");
  Serial.println("Bottom-right UP = Gear 6 (low Y + right X)");
  Serial.println("Bottom-right DOWN = Reverse (low Y + right X + down)");
  Serial.println("=================================");
}

void loop() {
  int x = analogRead(xPin);
  int y = analogRead(yPin);
  int revRaw = digitalRead(revPin) == LOW;  // 1 = UP/released, 0 = DOWN/pressed
  
  bool revPressed = (revRaw == 0);   // 0 = pressed/down (adjust if inverted)

  String gear = "Neutral";

  if (y >= Y_TOP_MIN) {  // Top/forward row (high Y: 1/3/5)
    if (x <= X_LEFT_MAX) gear = "1";
    else if (x >= X_RIGHT_MIN) gear = "5";
    else gear = "3";
  } 
  else if (y <= Y_BOTTOM_MAX) {  // Bottom/back row (low Y: 2/4/6/R)
    if (x <= X_LEFT_MAX) gear = "2";
    else if (x >= X_RIGHT_MIN) {
      gear = revPressed ? "R" : "6";
    } else gear = "4";
  }

  Serial.print("X: "); Serial.print(x);
  Serial.print(" | Y: "); Serial.print(y);
  Serial.print(" | Rev raw: "); Serial.print(revRaw);
  Serial.print(" ("); Serial.print(revPressed ? "DOWN pressed" : "UP released"); Serial.print(")");
  Serial.print(" | Gear: "); Serial.println(gear);

  delay(300);
}