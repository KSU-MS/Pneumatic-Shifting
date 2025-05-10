#include "main.hpp"
PS3 pneumaticMain;

void setup() {
  Serial.begin(9600);

  pinMode(UP_PIN, OUTPUT);
  pinMode(NO_LIFT_SHIFT, OUTPUT);
  pinMode(LAUNCH_CONTROL, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(CLUTCH_PIN, OUTPUT);

  pinMode(PADDLE_SIGNAL, INPUT);
  pinMode(LAUNCH_BUTTON_SIGNAL, INPUT);

  pneumaticMain.pinReset(); // Sets all pins to low

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  digitalToggle(LED_BUILTIN);

  // Button Reads
  Paddle_Value = analogRead(PADDLE_SIGNAL);
  Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);

  Serial.printf("Paddle_Value: %i\n", Paddle_Value);
  Serial.printf("Launch_Value: %i\n", Launch_Value);

  // Give the circuit time to settle to avoid resistor bounce
  if (Paddle_Value < 900 || Launch_Value < 900) {
    delay(5);
    Paddle_Value = analogRead(PADDLE_SIGNAL);
    Serial.printf("Paddle_Value evil: %i\n", Paddle_Value);
    Serial.printf("Launch_Value evil: %i\n", Launch_Value);
  }

  // Launch case
  if (Launch_Value > 820 && Launch_Value < 860) {
    pneumaticMain.launchStateActive();

    // Wait for the driver to release the button
    while (Launch_Value > 820 && Launch_Value < 860) {
      delay(5);
      Launch_Value = analogRead(LAUNCH_BUTTON_SIGNAL);
      Serial.println("Launch Button is being held");
    }
    Serial.println("Launch Button Released");

    pneumaticMain.launchStateDisengage();
  }

  // Upshift case
  else if (Paddle_Value > 770 && Paddle_Value < 790) {
    pneumaticMain.upShift();

    // Reset the pins again to prevent constant up shifting
    pneumaticMain.pinReset();

    // Prevent multiple shifts from holding the paddle
    while (Paddle_Value < 900) {
      delay(5);
      Paddle_Value = analogRead(PADDLE_SIGNAL);
      Serial.println("Right Paddle is being held");
    }
    Serial.println("Right Paddle Released");
  }

  // Downshift case
  else if (Paddle_Value > 690 && Paddle_Value < 710) {
    pneumaticMain.downShift();

    // Reset the pins again to prevent constant down shifting
    pneumaticMain.pinReset();

    // Prevent multiple shifts from holding the paddle
    while (Paddle_Value < 900) {
      delay(5);
      Paddle_Value = analogRead(PADDLE_SIGNAL);
      Serial.println("Left Paddle is being held");
    }
    Serial.println("Left Paddle Released");
  }

  // Catch case
  pneumaticMain.pinReset();
}
